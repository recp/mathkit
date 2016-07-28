/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mk_matrix_h
#define mk_matrix_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "mk-common.h"
#include "mk-vector.h"

typedef struct MkMatrix {
   void        *value;
   MkBufLayout *layout;
   size_t       rows;
   size_t       cols;
   size_t       isize;
   size_t       count;
   int          bufindex;
} MkMatrix;

#include "impl/mk-matrix-impl-sc.h"
#include "impl/mk-matrix-impl-mat.h"

MK_EXPORT
void
mkMatrixPrint(MkMatrix * __restrict matrix,
              MkPrintFn itemPrinter,
              FILE * __restrict ostream);

MK_EXPORT
MK_INLINE
void
mkMatrixInit(MkMatrix * __restrict matrix,
             const MkBufLayout layout) {

   matrix->count    = layout.count[0] * layout.count[1];
   matrix->rows     = layout.count[0];
   matrix->cols     = layout.count[1];
   matrix->isize    = mkItemSize(layout);
   matrix->bufindex = 0;
}

MK_EXPORT
MK_INLINE
MkMatrix *
mkMatrixNew(void * __restrict value,
            const MkBufLayout layout) {
   MkMatrix *matrix;

   matrix = (MkMatrix *)malloc(sizeof(*matrix));
   mkMatrixInit(matrix, layout);

   return matrix;
}

inline
void
mkMatrixScale(MkMatrix * __restrict matrix,
              void * __restrict other,
              const MkBufLayout layout);


inline
void
mkMatrixAdd(MkMatrix * __restrict matrix,
            void * __restrict other,
            const MkBufLayout layout);

inline
void
mkMatrixSub(MkMatrix * __restrict matrix,
            void * __restrict other,
            const MkBufLayout layout);

inline
void
mkMatrixDiv(MkMatrix * __restrict matrix,
            void * __restrict other,
            const MkBufLayout layout);

#ifdef __cplusplus
}
#endif
#endif /* mk_matrix_h */
