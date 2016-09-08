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

#define MK_INIT_IDENTITY_4x4F {1.0f, 0.0f, 0.0f, 0.0f,                        \
                               0.0f, 1.0f, 0.0f, 0.0f,                        \
                               0.0f, 0.0f, 1.0f, 0.0f,                        \
                               0.0f, 0.0f, 0.0f, 1.0f}

#define MK_INIT_IDENTITY_4x4D {1.0, 0.0, 0.0, 0.0,                            \
                               0.0, 1.0, 0.0, 0.0,                            \
                               0.0, 0.0, 1.0, 0.0,                            \
                               0.0, 0.0, 0.0, 1.0}

#define MK_INIT_IDENTITY_4x4I {1, 0, 0, 0,                                    \
                               0, 1, 0, 0,                                    \
                               0, 0, 1, 0,                                    \
                               0, 0, 0, 1}

#define MK_INIT_IDENTITY_4x4L {1l, 0l, 0l, 0l,                                \
                               0l, 1l, 0l, 0l,                                \
                               0l, 0l, 1l, 0l,                                \
                               0l, 0l, 0l, 1l}

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
mkMatrixFillIdentity(MkMatrix * __restrict matrix,
                     const MkHint hint);

MK_INLINE
bool
mkMatrixIsIdentity(MkMatrix * matrix,
                   const MkHint hint);

MK_INLINE
void
mkMatrixInit(MkMatrix * __restrict matrix,
             void * __restrict value,
             bool isIdentity,
             const MkHint hint) {

   matrix->count    = hint.count[0] * hint.count[1];
   matrix->rows     = hint.count[0];
   matrix->cols     = hint.count[1];
   matrix->isize    = mkItemSize(hint);
   matrix->bufindex = 0;
   matrix->value    = value;

   if (isIdentity)
      mkMatrixFillIdentity(matrix, hint);
}

MK_INLINE
MkMatrix *
mkMatrixNew(void * __restrict value,
            bool isIdentity,
            const MkHint hint) {
   MkMatrix *matrix;

   matrix = (MkMatrix *)malloc(sizeof(*matrix));
   mkMatrixInit(matrix, value, isIdentity, hint);

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
