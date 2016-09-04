/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../../include/mk.h"
#include "../../include/mk-vector.h"
#include <assert.h>

MK_EXPORT
void
mkVectorPrint(MkVector * __restrict vec,
              MkPrintFn itemPrinter,
              FILE * __restrict ostream) {
   char  *pos;
   size_t len;
   size_t itemSize;
   size_t i;

   len      = vec->count;
   itemSize = vec->isize;
   pos      = vec->value;

   fprintf(ostream, "Vector (%zu):\n", len);

   for (i = 0; i < len; i++) {
      itemPrinter(ostream, pos);
      pos += itemSize;
   }

   fprintf(ostream, "\n");
}
