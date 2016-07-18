/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../../include/mk.h"
#include "../../include/mk-matrix.h"

#include "../mk__mem.h"

#include <assert.h>
#include <string.h>

static
void
mk__matrixMultMatrixL(MkMatrix * __restrict destMatrix,
                      MkMatrix * __restrict matrixL,
                      MkOp * __restrict op);

static
void
mk__matrixMultMatrixR(MkMatrix * __restrict destMatrix,
                      MkMatrix * __restrict matrixR,
                      MkOp * __restrict op);

static
MkMatrix *
mk__matrixMultMatrix(MkMatrix * __restrict matrixL,
                     MkMatrix * __restrict matrixR,
                     MkOp * __restrict op);

static
void
mk__matrixAddMatrixL(MkMatrix * __restrict destMatrix,
                     MkMatrix * __restrict matrixL,
                     MkOp * __restrict op);

static
MkMatrix *
mk__matrixAddMatrix(MkMatrix * __restrict matrixL,
                    MkMatrix * __restrict matrixR,
                    MkOp * __restrict op);

MK_EXPORT
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

MK_EXPORT
void
mkMatrixFill(MkMatrix * __restrict matrix,
             void * value) {
  mk__memcpy(MkMatrixVal(matrix),
             value,
             matrix->base.itemCount * matrix->base.itemSize);
}

MK_EXPORT
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

    value = (float *)matrix->base.value;
    for (; i < matrix->rows; i++)
      *(value + i * n + j++) = 1.0f;
  }

#undef n

  return matrix;
}

MK_EXPORT
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

    value = (double *)matrix->base.value;
    for (; i < matrix->rows; i++)
      *(value + i * n + j++) = 1.0;
  }

#undef n

  return matrix;
}

MK_EXPORT
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

MK_EXPORT
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

MK_EXPORT
MkMatrix *
mkMatrixNewFrom4x4f(float * data) {
  return mkMatrixNewFromf(4, 4, data);
}

MK_EXPORT
MkMatrix *
mkMatrixNewFrom4x4d(double * data) {
  return mkMatrixNewFromd(4, 4, data);
}

MK_EXPORT
void
mkMatrixPrint(MkMatrix * __restrict matrix,
              MkPrintFn itemPrinter,
              FILE * __restrict ostream) {
  char  *pos;
  size_t rows;
  size_t cols;
  size_t itemSize;
  size_t i;
  size_t j;

  rows     = matrix->rows;
  cols     = matrix->columns;
  pos      = matrix->base.value;
  itemSize = matrix->base.itemSize;

  fprintf(ostream, "Matrix (%zux%zu):\n", rows, cols);

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      itemPrinter(ostream, pos);
      pos += itemSize;
    }

    fprintf(ostream, "\n");
  }

  fprintf(ostream, "\n");
}

MK_EXPORT
void
mkMatrixTranspose(MkMatrix * __restrict matrix) {
  char  *value;
  char  *posA;
  char  *posB;
  char  *posA_row;
  char  *posB_row;
  size_t itemSize;
  size_t rows;
  size_t cols;
  size_t rowsOff;
  size_t i;
  size_t j;
  size_t itemCount;

  itemSize  = matrix->base.itemSize;
  itemCount = matrix->base.itemCount;
  rows      = matrix->rows;
  cols      = matrix->columns;
  value     = matrix->base.value;

  rowsOff   = rows * itemSize;

  matrix->rows    = cols;
  matrix->columns = rows;

  /* Transpose square matrix */
  if (rows == cols) {
    char tmp[itemSize];

    posA_row  = value;
    posB_row  = value;

    for (i = 0; i < rows; i++) {
      posA = posA_row;
      posB = posB_row;

      for (j = 0; j < i && j < rows; j++) {
        mk__memcpy(tmp,
                   posB,
                   itemSize);

        mk__memcpy(posB,
                   posA,
                   itemSize);

        mk__memcpy(posA,
                   tmp,
                   itemSize);

        posA += itemSize;
        posB += rowsOff;
      }

      posA_row += rowsOff;
      posB_row += itemSize;
    }
    
    return;
  }

  /* Transpose non-square matrix */
  {
    char trans[itemSize * itemCount];

    posB_row  = trans;
    posA      = value;

    for (i = 0; i < rows; i++) {
      posB = posB_row;

MK_PRAGMA_UNROLL_4
      for (j = 0; j < cols; j++) {
        mk__memcpy(posB,
                   posA,
                   itemSize);

        posA += itemSize;
        posB += rowsOff;
      }

      posB_row += itemSize;
    }

    mk__memcpy(value,
               trans,
               sizeof(trans));
  }
}

MK_EXPORT
bool
mkMatrixIsIdentity(MkMatrix * __restrict matrix) {
  char  *itemPos;
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

MK_EXPORT
void
mkMatrixScale(MkMatrix * __restrict matrix,
              void * __restrict other,
              MkOp * __restrict op) {
  char  *itemPos;
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

MK_EXPORT
void
mkMatrixMatrixL(MkMatrix * __restrict destMatrix,
                MkMatrix * __restrict matrixL,
                MkOp * __restrict op) {
  if (op->type == MK_OP_TYPE_MULTIPLY) {
    assert(destMatrix->columns == matrixL->rows
           && "matrix's columns must match to R's rows");

    mk__matrixMultMatrixL(destMatrix, matrixL, op);
  } else if (op->type == MK_OP_TYPE_ADDITION) {
    assert(matrixL->rows == destMatrix->rows
           && matrixL->columns == destMatrix->columns
           && "to addition, matrix dimensions must be same");

    mk__matrixAddMatrixL(destMatrix, matrixL, op);
  }
}

MK_EXPORT
void
mkMatrixMatrixR(MkMatrix * __restrict destMatrix,
                MkMatrix * __restrict matrixR,
                MkOp * __restrict op) {
  if (op->type == MK_OP_TYPE_MULTIPLY) {
    assert(matrixR->columns == destMatrix->rows
           && "L's columns must match to matrix's rows");


    mk__matrixMultMatrixR(destMatrix, matrixR, op);
  } else if (op->type == MK_OP_TYPE_ADDITION) {
    assert(destMatrix->rows == matrixR->rows
           && destMatrix->columns == matrixR->columns
           && "to addition, matrix dimensions must be same");

    mk__matrixAddMatrixL(destMatrix, matrixR, op);
  }
}

MK_EXPORT
MkMatrix *
mkMatrixMatrix(MkMatrix * __restrict matrixL,
               MkMatrix * __restrict matrixR,
               MkOp * __restrict op) {
  if (op->type == MK_OP_TYPE_MULTIPLY) {
    assert(matrixR->columns == matrixL->rows
           && "L's columns must match to matrix's rows");

    return mk__matrixMultMatrix(matrixL, matrixR, op);
  } else if (op->type == MK_OP_TYPE_ADDITION) {
    assert(matrixL->rows == matrixR->rows
           && matrixL->columns == matrixR->columns
           && "to addition, matrix dimensions must be same");

    return mk__matrixAddMatrix(matrixL, matrixR, op);
  }

  return NULL;
}

static
void
mk__matrixMultMatrixL(MkMatrix * __restrict destMatrix,
                      MkMatrix * __restrict matrixL,
                      MkOp * __restrict op) {
  char  *newValue;
  char  *tmpSum;
  char  *tmpMult;
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

  newValue += itemSize * 2;

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
mk__matrixMultMatrixR(MkMatrix * __restrict destMatrix,
                      MkMatrix * __restrict matrixR,
                      MkOp * __restrict op) {
  char  *newValue;
  char  *tmpSum;
  char  *tmpMult;
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

  newValue += itemSize * 2;

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
mk__matrixMultMatrix(MkMatrix * __restrict matrixL,
                     MkMatrix * __restrict matrixR,
                     MkOp * __restrict op) {
  MkMatrix *newMatrix;
  char     *newValue;
  char     *tmpSum;
  char     *tmpMult;
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

  newValue += itemSize * 2;

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
mk__matrixAddMatrixL(MkMatrix * __restrict destMatrix,
                     MkMatrix * __restrict matrixL,
                     MkOp * __restrict op) {
  char    *itemPosA;
  char    *itemPosA_end;
  char    *itemPosB;
  size_t   itemSize;
  MkOpFn   opFn;

  itemSize     = destMatrix->base.itemSize;
  itemPosA     = destMatrix->base.value;
  itemPosB     = matrixL->base.value;
  itemPosA_end = itemPosA + itemSize * matrixL->base.itemCount;
  opFn         = op->op;

MK_PRAGMA_UNROLL_4
  while (itemPosA != itemPosA_end) {
    opFn(itemPosA, itemPosB);

    itemPosA += itemSize;
    itemPosB += itemSize;
  }
}

static
MkMatrix *
mk__matrixAddMatrix(MkMatrix * __restrict matrixL,
                    MkMatrix * __restrict matrixR,
                    MkOp * __restrict op) {
  MkMatrix *newMatrix;
  char     *itemPosA;
  char     *itemPosA_end;
  char     *itemPosB;
  char     *itemPosC;
  size_t    itemSize;
  MkOpFn    opFn;

  itemSize     = matrixL->base.itemSize;
  itemPosB     = matrixL->base.value;
  itemPosC     = matrixR->base.value;

  newMatrix = mkMatrixNew(itemSize,
                          matrixL->rows,
                          matrixL->columns,
                          itemPosB - itemSize * 2,
                          itemPosB - itemSize);

  itemPosA     = newMatrix->base.value;
  itemPosA_end = itemPosA + itemSize * matrixL->base.itemCount;
  opFn         = op->op;

MK_PRAGMA_UNROLL_4
  while (itemPosA != itemPosA_end) {
    opFn(itemPosA, itemPosB);
    opFn(itemPosA, itemPosC);

    itemPosA += itemSize;
    itemPosB += itemSize;
    itemPosC += itemSize;
  }

  return newMatrix;
}
