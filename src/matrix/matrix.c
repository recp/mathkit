/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */


#include "../../include/mk-matrix.h"
#include <assert.h>

static
void
mk__matrixMultiplyMatrixL(MkMatrix * __restrict destMatrix,
                          MkMatrix * __restrict matrixL,
                          MkOp * __restrict op);

static
void
mk__matrixMultiplyMatrixR(MkMatrix * __restrict destMatrix,
                          MkMatrix * __restrict matrixR,
                          MkOp * __restrict op);

static
MkMatrix *
mk__matrixMultiplyMatrix(MkMatrix * __restrict matrixL,
                         MkMatrix * __restrict matrixR,
                         MkOp * __restrict op);

static
void
mk__matrixAdditionMatrixL(MkMatrix * __restrict destMatrix,
                          MkMatrix * __restrict matrixL,
                          MkOp * __restrict op);

static
MkMatrix *
mk__matrixAdditionMatrix(MkMatrix * __restrict matrixL,
                         MkMatrix * __restrict matrixR,
                         MkOp * __restrict op);

MkMatrix *
mkMatrixNew(size_t itemSize,
            size_t rows,
            size_t columns,
            void  *zeroVal,
            void  *oneVal) {
  MkMatrix *matrix;
  char     *value;
  size_t    itemCount;

  itemCount = rows * columns;

  matrix = calloc(sizeof(*matrix), 1);
  matrix->base.itemSize  = itemSize;
  matrix->base.itemCount = itemCount;
  matrix->rows           = rows;
  matrix->columns        = columns;

  /* +1 for zeroVal, +1 for oneVal */
  value = calloc(itemSize, matrix->base.itemCount + 2);

  memcpy(value, zeroVal, itemSize);
  memcpy(value + itemSize, oneVal, itemSize);

  matrix->base.value = value + itemSize * 2;

  return matrix;
}

MkMatrix *
mkMatrixNew4x4f(bool identity) {
  MkMatrix *matrix;
  float     oneVal;
  float     zeroVal;

#define n 4

  oneVal  = 1.0f;
  zeroVal = 0.0f;

  matrix = mkMatrixNew(sizeof(float),
                       n,
                       n,
                       &zeroVal,
                       &oneVal);

  if (identity) {
    float *value;
    int    i;
    int    j;

    i = 0;
    j = 0;

    value = matrix->base.value;
    for (; i < matrix->rows; i++)
      *(value + i * n + j++) = 1.0f;
  }

#undef n

  return matrix;
}

MkMatrix *
mkMatrixNew4x4d(bool identity) {
  MkMatrix *matrix;
  double    oneVal;
  double    zeroVal;

#define n 4

  oneVal  = 1.0;
  zeroVal = 0.0;

  matrix = mkMatrixNew(sizeof(double),
                       n,
                       n,
                       &zeroVal,
                       &oneVal);

  if (identity) {
    double *value;
    int     i;
    int     j;

    i = 0;
    j = 0;

    value = matrix->base.value;
    for (; i < matrix->rows; i++)
      *(value + i * n + j++) = 1.0;
  }

#undef n

  return matrix;
}

MkMatrix *
mkMatrixNewFromf(size_t rows,
                 size_t columns,
                 float * data) {
  MkMatrix *matrix;
  float     oneVal;
  float     zeroVal;

  oneVal  = 1.0f;
  zeroVal = 0.0f;

  matrix = mkMatrixNew(sizeof(float),
                       rows,
                       columns,
                       &zeroVal,
                       &oneVal);

  memcpy(matrix->base.value,
         data,
         sizeof(float) * matrix->base.itemCount);

  return matrix;
}

MkMatrix *
mkMatrixNewFromd(size_t rows,
                 size_t columns,
                 double * data) {
  MkMatrix *matrix;
  double    oneVal;
  double    zeroVal;

  oneVal  = 1.0;
  zeroVal = 0.0;

  matrix = mkMatrixNew(sizeof(double),
                       rows,
                       columns,
                       &zeroVal,
                       &oneVal);

  memcpy(matrix->base.value,
         data,
         sizeof(double) * rows * columns);

  return matrix;
}

MkMatrix *
mkMatrixNewFrom4x4f(float * data) {
  return mkMatrixNewFromf(4, 4, data);
}

MkMatrix *
mkMatrixNewFrom4x4d(double * data) {
  return mkMatrixNewFromd(4, 4, data);
}

void
mkMatrixPrint(MkMatrix * __restrict matrix,
              MkPrintFn itemPrinter,
              FILE * __restrict ostream) {
  size_t i;
  size_t j;

  fprintf(ostream, "Matrix (%ldx%ld):\n",
          matrix->rows, matrix->columns);

  for (i = 0; i < matrix->rows; i++) {
    for (j = 0; j < matrix->columns; j++)
      itemPrinter(ostream, MkMatrixGet(matrix, i, j));

    fprintf(ostream, "\n");
  }

  fprintf(ostream, "\n");
}

void
mkMatrixTranspose(MkMatrix * __restrict matrix) {
  char  *newValue;
  size_t itemSize;
  size_t rows;
  size_t cols;
  size_t i;
  size_t j;

  itemSize = matrix->base.itemSize;
  rows     = matrix->rows;
  cols     = matrix->columns;
  newValue = malloc(itemSize * (matrix->base.itemCount + 2));

  /* save zeroVal and oneVal */
  memcpy(newValue,
         matrix->base.value - itemSize * 2,
         itemSize * 2);

  for (i = 0; i < matrix->rows; i++) {
    for (j = 0; j < matrix->columns; j++)
      memcpy((newValue + (j * rows + i) * itemSize),
             MkMatrixGet(matrix, i, j),
             itemSize);
  }

  free(matrix->base.value - itemSize * 2);

  matrix->rows       = cols;
  matrix->columns    = rows;
  matrix->base.value = newValue;
}

bool
mkMatrixIsIdentity(MkMatrix * __restrict matrix) {
  void  *itemPos;
  char  *value;
  char  *zeroVal;
  char  *oneVal;
  size_t i;
  size_t j;
  size_t itemSize;
  bool   isIdentity;

  isIdentity = false;
  itemSize   = matrix->base.itemSize;
  value      = matrix->base.value;
  zeroVal    = matrix->base.value - itemSize * 2;
  oneVal     = zeroVal + itemSize;

  for (i = 0; i < matrix->rows; i++) {
    for (j = 0; j < matrix->columns; j++) {
      itemPos = (value + (i * matrix->columns + j) * itemSize);

      if (i != j) {
        if (memcmp(itemPos, zeroVal, itemSize) != 0)
          goto ret;

        continue;
      }

      if (memcmp(itemPos, oneVal, itemSize) != 0)
        goto ret;
    }
  }

  isIdentity = true;

ret:
  return isIdentity;
}

void
mkMatrixApplyScalarL(void * __restrict other,
                     MkMatrix * __restrict matrix,
                     MkOp * __restrict op) {
  void  *itemPos;
  char  *value;
  size_t i;
  size_t j;
  size_t itemSize;

  itemSize   = matrix->base.itemSize;
  value      = matrix->base.value;

  for (i = 0; i < matrix->rows; i++) {
    for (j = 0; j < matrix->columns; j++) {
      itemPos = (value + (i * matrix->columns + j) * itemSize);
      op->op(itemPos, other);
    }
  }
}

void
mkMatrixApplyMatrixL(MkMatrix * __restrict destMatrix,
                     MkMatrix * __restrict matrixL,
                     MkOp * __restrict op) {
  if (op->type == MK_OP_TYPE_MULTIPLY) {
    assert(destMatrix->columns == matrixL->rows
           && "matrix's columns must match to R's rows");

    mk__matrixMultiplyMatrixL(destMatrix, matrixL, op);
  } else if (op->type == MK_OP_TYPE_ADDITION) {
    assert(matrixL->rows == destMatrix->rows
           && matrixL->columns == destMatrix->columns
           && "to addition, matrix dimensions must be same");

    mk__matrixAdditionMatrixL(destMatrix, matrixL, op);
  }
}

void
mkMatrixApplyMatrixR(MkMatrix * __restrict destMatrix,
                     MkMatrix * __restrict matrixR,
                     MkOp * __restrict op) {
  if (op->type == MK_OP_TYPE_MULTIPLY) {
    assert(matrixR->columns == destMatrix->rows
           && "L's columns must match to matrix's rows");


    mk__matrixMultiplyMatrixR(destMatrix, matrixR, op);
  } else if (op->type == MK_OP_TYPE_ADDITION) {
    assert(destMatrix->rows == matrixR->rows
           && destMatrix->columns == matrixR->columns
           && "to addition, matrix dimensions must be same");

    mk__matrixAdditionMatrixL(destMatrix, matrixR, op);
  }
}

MkMatrix *
mkMatrixApplyMatrix(MkMatrix * __restrict matrixL,
                    MkMatrix * __restrict matrixR,
                    MkOp * __restrict op) {
  if (op->type == MK_OP_TYPE_MULTIPLY) {
    assert(matrixR->columns == matrixL->rows
           && "L's columns must match to matrix's rows");

    return mk__matrixMultiplyMatrix(matrixL, matrixR, op);
  } else if (op->type == MK_OP_TYPE_ADDITION) {
    assert(matrixL->rows == matrixR->rows
           && matrixL->columns == matrixR->columns
           && "to addition, matrix dimensions must be same");

    return mk__matrixAdditionMatrix(matrixL, matrixR, op);
  }

  return NULL;
}

static
void
mk__matrixMultiplyMatrixL(MkMatrix * __restrict destMatrix,
                          MkMatrix * __restrict matrixL,
                          MkOp * __restrict op) {
  char  *newValue;
  void  *tmpSum;
  void  *tmpMult;
  size_t itemSize;
  size_t newItemCount;
  size_t rowsL;
  size_t colsR;
  size_t i;
  size_t j;
  size_t jL;
  size_t iR;

  rowsL        = matrixL->rows;
  colsR        = destMatrix->columns;

  newItemCount = rowsL * colsR;
  itemSize     = destMatrix->base.itemSize;
  newValue     = malloc(itemSize * (newItemCount + 2));

  tmpSum       = malloc(itemSize);
  tmpMult      = malloc(itemSize);

  /* save zeroVal and oneVal */
  memcpy(newValue,
         destMatrix->base.value - itemSize * 2,
         itemSize * 2);

  for (i = 0; i < rowsL; i++) {
    for (j = 0; j < colsR; j++) {
      memset(tmpSum, '\0', itemSize);

      for (iR = 0, jL = 0;
           iR < matrixL->columns;
           iR++, jL++) {
        memcpy(tmpMult,
               MkMatrixGet(matrixL, i, jL),
               itemSize);

        op->op(tmpMult, MkMatrixGet(destMatrix, iR, j));
        op->addop(tmpSum, tmpMult);
      }

      memcpy((newValue + (i * colsR + j) * itemSize),
             tmpSum,
             itemSize);
    }
  }

  free(tmpSum);
  free(tmpMult);

  free(destMatrix->base.value - itemSize * 2);

  destMatrix->rows       = rowsL;
  destMatrix->base.value = newValue;
}

static
void
mk__matrixMultiplyMatrixR(MkMatrix * __restrict destMatrix,
                          MkMatrix * __restrict matrixR,
                          MkOp * __restrict op) {
  char  *newValue;
  void  *tmpSum;
  void  *tmpMult;
  size_t itemSize;
  size_t newItemCount;
  size_t rowsL;
  size_t colsR;
  size_t i;
  size_t j;
  size_t jL;
  size_t iR;

  rowsL        = destMatrix->rows;
  colsR        = matrixR->columns;

  newItemCount = rowsL * colsR;
  itemSize     = matrixR->base.itemSize;
  newValue     = malloc(itemSize * (newItemCount + 2));

  tmpSum       = malloc(itemSize);
  tmpMult      = malloc(itemSize);

  /* save zeroVal and oneVal */
  memcpy(newValue,
         matrixR->base.value - itemSize * 2,
         itemSize * 2);

  for (i = 0; i < rowsL; i++) {
    for (j = 0; j < colsR; j++) {
      memset(tmpSum, '\0', itemSize);

      for (iR = 0, jL = 0;
           iR < destMatrix->columns;
           iR++, jL++) {
        memcpy(tmpMult,
               MkMatrixGet(destMatrix, i, jL),
               itemSize);

        op->op(tmpMult, MkMatrixGet(matrixR, iR, j));
        op->addop(tmpSum, tmpMult);
      }

      memcpy((newValue + (i * colsR + j) * itemSize),
             tmpSum,
             itemSize);
    }
  }

  free(tmpSum);
  free(tmpMult);

  free(destMatrix->base.value - itemSize * 2);

  destMatrix->columns    = colsR;
  destMatrix->base.value = newValue;
}

static
MkMatrix *
mk__matrixMultiplyMatrix(MkMatrix * __restrict matrixL,
                         MkMatrix * __restrict matrixR,
                         MkOp * __restrict op) {
  MkMatrix *newMatrix;
  char     *newValue;
  void     *tmpSum;
  void     *tmpMult;
  size_t itemSize;
  size_t rowsL;
  size_t colsR;
  size_t i;
  size_t j;
  size_t jL;
  size_t iR;

  rowsL = matrixL->rows;
  colsR = matrixR->columns;

  newMatrix = mkMatrixNew(matrixL->base.itemSize,
                          rowsL,
                          colsR,
                          matrixL->base.value - matrixL->base.itemSize * 2,
                          matrixL->base.value - matrixL->base.itemSize);

  itemSize     = matrixR->base.itemSize;
  newValue     = newMatrix->base.value;

  tmpSum       = malloc(itemSize);
  tmpMult      = malloc(itemSize);

  /* save zeroVal and oneVal */
  memcpy(newValue,
         matrixR->base.value - itemSize * 2,
         itemSize * 2);

  for (i = 0; i < rowsL; i++) {
    for (j = 0; j < colsR; j++) {
      memset(tmpSum, '\0', itemSize);

      for (iR = 0, jL = 0;
           iR < matrixL->columns;
           iR++, jL++) {
        memcpy(tmpMult,
               MkMatrixGet(matrixL, i, jL),
               itemSize);

        op->op(tmpMult, MkMatrixGet(matrixR, iR, j));
        op->addop(tmpSum, tmpMult);
      }

      memcpy((newValue + (i * colsR + j) * itemSize),
             tmpSum,
             itemSize);
    }
  }

  free(tmpSum);
  free(tmpMult);

  return newMatrix;
}

static
void
mk__matrixAdditionMatrixL(MkMatrix * __restrict destMatrix,
                          MkMatrix * __restrict matrixL,
                          MkOp * __restrict op) {
  char  *valueA;
  char  *valueB;
  void  *itemPosA;
  void  *itemPosB;
  size_t itemSize;
  size_t cols;
  size_t i;
  size_t j;

  cols     = destMatrix->columns;
  itemSize = destMatrix->base.itemSize;
  valueA   = destMatrix->base.value;
  valueB   = matrixL->base.value;

  for (i = 0; i < destMatrix->rows; i++) {
    for (j = 0; j < cols; j++) {
      itemPosA = (valueA + (i * cols + j) * itemSize);
      itemPosB = (valueB + (i * cols + j) * itemSize);

      op->op(itemPosA, itemPosB);
    }
  }
}

static
MkMatrix *
mk__matrixAdditionMatrix(MkMatrix * __restrict matrixL,
                         MkMatrix * __restrict matrixR,
                         MkOp * __restrict op) {
  MkMatrix *newMatrix;
  char     *valueA;
  char     *valueB;
  char     *valueC;
  void     *itemPosA;
  void     *itemPosB;
  void     *itemPosC;
  size_t itemSize;
  size_t cols;
  size_t i;
  size_t j;

  cols      = matrixL->columns;
  itemSize  = matrixL->base.itemSize;

  newMatrix = mkMatrixNew(itemSize,
                          matrixL->rows,
                          cols,
                          matrixL->base.value - itemSize * 2,
                          matrixL->base.value - itemSize);

  valueA    = newMatrix->base.value;
  valueB    = matrixL->base.value;
  valueC    = matrixR->base.value;

  for (i = 0; i < matrixL->rows; i++) {
    for (j = 0; j < cols; j++) {
      itemPosA = (valueA + (i * cols + j) * itemSize);
      itemPosB = (valueB + (i * cols + j) * itemSize);
      itemPosC = (valueC + (i * cols + j) * itemSize);

      op->op(itemPosA, itemPosB);
      op->op(itemPosA, itemPosC);
    }
  }

  return newMatrix;
}
