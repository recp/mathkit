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
__attribute((always_inline))
inline
MkMatrix *
mkMatrixNew(MkBufLayout * __restrict layout) {
   MkMatrix *matrix;

   matrix = (MkMatrix *)calloc(sizeof(*matrix), 1);
   matrix->count  = layout->count[0] * layout->count[1];
   matrix->rows   = layout->count[0];
   matrix->cols   = layout->count[1];
   matrix->layout = layout;
   matrix->isize  = mkItemSize(layout);

   return matrix;
}

MK_EXPORT
__attribute((always_inline))
inline
void
mkMatrixInit(MkMatrix * __restrict matrix,
             MkBufLayout * __restrict layout) {

   matrix->count    = layout->count[0] * layout->count[1];
   matrix->rows     = layout->count[0];
   matrix->cols     = layout->count[1];
   matrix->layout   = layout;
   matrix->isize    = mkItemSize(layout);
   matrix->bufindex = 0;
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
