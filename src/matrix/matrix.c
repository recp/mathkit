/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../../include/mk.h"
#include "../../include/mk-matrix.h"

#include <assert.h>
#include <string.h>

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
  cols     = matrix->cols;
  pos      = matrix->value;
  itemSize = matrix->isize;

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
