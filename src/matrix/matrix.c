/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../../include/mathkit.h"

MkMatrix *
mkMatrixNew(size_t itemSize,
            size_t rows,
            size_t columns,
            void  *zeroVal,
            void  *oneVal) {
  MkMatrix *matrix;
  char     *value;
  char     *zeroPos;
  size_t    itemCount;

  itemCount = rows * columns;

  matrix = calloc(sizeof(*matrix), 1);
  matrix->base.itemSize  = itemSize;
  matrix->base.itemCount = itemCount;
  matrix->rows           = rows;
  matrix->columns        = columns;

  /* +1 for zeroVal, +1 for oneVal */
  value = calloc(itemSize, matrix->base.itemCount + 2);

  zeroPos = value + itemSize * itemCount;

  memcpy(zeroPos, zeroVal, itemSize);
  memcpy(zeroPos + itemSize, oneVal, itemSize);

  matrix->base.value = value;

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

void
mkMatrixPrint(MkMatrix * matrix,
              MkPrintFn itemPrinter,
              FILE * __restrict ostream) {
  size_t i;
  size_t j;

  fprintf(ostream, "\nMatrix (%ldx%ld):\n",
          matrix->rows, matrix->columns);

  for (i = 0; i < matrix->rows; i++) {
    for (j = 0; j < matrix->columns; j++)
      itemPrinter(ostream, MkMatrixGet(matrix, i, j));
  
    fprintf(ostream, "\n");
  }

  fprintf(ostream, "\n\n");
}

void
mkMatrixTranspose(MkMatrix * matrix) {
  char  *newValue;
  size_t itemSize;
  size_t rows;
  size_t i;
  size_t j;

  itemSize = matrix->base.itemSize;
  rows     = matrix->rows;
  newValue = malloc(matrix->base.itemSize * (matrix->base.itemCount + 2));

  /* save zeroVal and oneVal */
  memcpy(newValue + matrix->base.itemSize * matrix->base.itemCount,
         matrix->base.value + matrix->base.itemSize * matrix->base.itemCount,
         itemSize * 2);

  for (i = 0; i < matrix->rows; i++) {
    for (j = 0; j < matrix->columns; j++)
      memcpy((newValue + (j * rows + i) * itemSize),
             MkMatrixGet(matrix, i, j),
             itemSize);
  }

  free(matrix->base.value);

  matrix->rows       = matrix->rows;
  matrix->columns    = rows;
  matrix->base.value = newValue;
}

bool
mkMatrixIsIdentity(MkMatrix * matrix) {
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
  zeroVal    = matrix->base.value + matrix->base.itemCount;
  oneVal     = zeroVal + matrix->base.itemSize;

  for (i = 0; i < matrix->rows; i++) {
    for (j = 0; j < matrix->columns; j++) {
      itemPos = (value + (i * matrix->rows + j) * itemSize);

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
