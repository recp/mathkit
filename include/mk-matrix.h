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

MK_EXPORT
void
mkMatrixPrint(MkMatrix * __restrict matrix,
              MkPrintFn itemPrinter,
              FILE * __restrict ostream);

MK_INLINE
void
mkMatrixInit(MkMatrix * __restrict matrix,
             void * __restrict value,
             const MkBufLayout layout) {

   matrix->count    = layout.count[0] * layout.count[1];
   matrix->rows     = layout.count[0];
   matrix->cols     = layout.count[1];
   matrix->isize    = mkItemSize(layout);
   matrix->bufindex = 0;
   matrix->value    = value;
}

MK_INLINE
MkMatrix *
mkMatrixNew(void * __restrict value,
            const MkBufLayout layout) {
   MkMatrix *matrix;

   matrix = (MkMatrix *)malloc(sizeof(*matrix));
   mkMatrixInit(matrix, value, layout);

   return matrix;
}

MK_INLINE
void
mkMatrixScale(MkMatrix * __restrict matrix,
              void * __restrict other,
              const MkBufLayout layout);

MK_INLINE
void
mkMatrixAdd(MkMatrix * __restrict matrix,
            void * __restrict other,
            const MkBufLayout layout);

MK_INLINE
void
mkMatrixSub(MkMatrix * __restrict matrix,
            void * __restrict other,
            const MkBufLayout layout);

MK_INLINE
void
mkMatrixDiv(MkMatrix * __restrict matrix,
            void * __restrict other,
            const MkBufLayout layout);

MK_INLINE
void
mkMatrixTranspose(MkMatrix * __restrict matrix,
                  void * __restrict bufs[2],
                  const MkBufLayout lay);

MK_INLINE
void
mkMatrixTransposeTo(MkMatrix * __restrict matrix,
                    void * __restrict dest,
                    const MkBufLayout lay);

MK_INLINE
void
mkMatrixMatrixMul(MkMatrix * __restrict matrixL,
                  MkMatrix * __restrict matrixR,
                  MkMatrix * __restrict dest,
                  const MkBufLayout lay[2]);

MK_INLINE
void
mkMatrixMatrixMulN(MkMatrix * __restrict matrices[],
                   MkMatrix * __restrict dest,
                   size_t len,
                   const MkBufLayout lay[]);

#include "impl/mki-matrix-sc.h"
#include "impl/mki-matrix-mat.h"

#ifdef __cplusplus
}
#endif
#endif /* mk_matrix_h */
