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
   size_t       rows;
   size_t       cols;
   size_t       isize;
   size_t       count;
   int          bufindex;
} MkMatrix;

MK_EXPORT
void
mkMatrixPrint(MkMatrix * __restrict matrix,
              MkPrintFn itemPrinter,
              FILE * __restrict ostream);

MK_INLINE
void
mkMatrixInit(MkMatrix * __restrict matrix,
             void * __restrict value,
             const MkHint hint) {

   matrix->count    = hint.count[0] * hint.count[1];
   matrix->rows     = hint.count[0];
   matrix->cols     = hint.count[1];
   matrix->isize    = mkItemSize(hint);
   matrix->bufindex = 0;
   matrix->value    = value;
}

MK_INLINE
MkMatrix *
mkMatrixNew(void * __restrict value,
            const MkHint hint) {
   MkMatrix *matrix;

   matrix = (MkMatrix *)malloc(sizeof(*matrix));
   mkMatrixInit(matrix, value, hint);

   return matrix;
}

MK_INLINE
void
mkMatrixScale(MkMatrix * __restrict matrix,
              void * __restrict other,
              const MkHint hint);

MK_INLINE
void
mkMatrixAdd(MkMatrix * __restrict matrix,
            void * __restrict other,
            const MkHint hint);

MK_INLINE
void
mkMatrixSub(MkMatrix * __restrict matrix,
            void * __restrict other,
            const MkHint hint);

MK_INLINE
void
mkMatrixDiv(MkMatrix * __restrict matrix,
            void * __restrict other,
            const MkHint hint);

MK_INLINE
void
mkMatrixTranspose(MkMatrix * __restrict matrix,
                  void * __restrict bufs[2],
                  const MkHint hint);

MK_INLINE
void
mkMatrixTransposeTo(MkMatrix * __restrict matrix,
                    void * __restrict dest,
                    const MkHint hint);

MK_INLINE
void
mkMatrixMatrixMul(MkMatrix * __restrict matrixL,
                  MkMatrix * __restrict matrixR,
                  MkMatrix * __restrict dest,
                  const MkHint hint[2]);

MK_INLINE
void
mkMatrixMatrixMulN(MkMatrix * __restrict matrices[],
                   MkMatrix * __restrict dest,
                   size_t len,
                   const MkHint hint[]);

#include "impl/mki-matrix-sc.h"
#include "impl/mki-matrix-mat.h"

#ifdef __cplusplus
}
#endif
#endif /* mk_matrix_h */
