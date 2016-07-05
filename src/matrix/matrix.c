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

    value = matrix->base.value;
    for (i = 0; i < matrix->rows; i++)
      *(value + n - i) = 1.0f;
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

    value = matrix->base.value;
    for (i = 0; i < matrix->rows; i++)
      *(value + n - i) = 1.0;
  }

#undef n

  return matrix;
}

