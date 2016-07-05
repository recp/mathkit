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
            size_t columns) {
  MkMatrix *matrix;

  matrix = calloc(sizeof(*matrix), 1);
  matrix->base.itemSize  = itemSize;
  matrix->base.itemCount = rows * columns;
  matrix->base.value     = calloc(itemSize, matrix->base.itemCount);
  matrix->rows           = rows;
  matrix->columns        = columns;

  return matrix;
}

MkMatrix *
mkMatrixNew4x4f(bool identity) {
  MkMatrix *matrix;

#define n 4

  matrix = mkMatrixNew(sizeof(float), n, n);

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

#define n 4

  matrix = mkMatrixNew(sizeof(double), n, n);

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
  newValue = malloc(matrix->base.itemSize * matrix->base.itemCount);

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

