/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../../include/mathkit.h"

MkMatrix *
mkMatrixNew(size_t itemSize,
            size_t m,
            size_t n) {
  MkMatrix *matrix;

  matrix = calloc(sizeof(*matrix), 1);
  matrix->base.itemSize  = itemSize;
  matrix->base.itemCount = m * n;
  matrix->base.value     = calloc(itemSize, matrix->base.itemCount);
  matrix->m = m;
  matrix->n = n;

  return matrix;
}
