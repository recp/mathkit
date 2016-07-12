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

#define MkMatrixGet(_matrix, _i, _j)                                          \
  ((char *)_matrix->base.value                                                \
        + (_i * _matrix->columns + _j) * (_matrix->base.itemSize))

#define MkMatrixSet(_matrix, _i, _j, _val)                                    \
  memcpy(MkMatrixGet(_matrix, _i, _j),                                        \
         _val,                                                                \
         _matrix->base.itemSize)

#define MkMatrixSet2(_matrix, _matrixPos, _val)                               \
  memcpy(_matrixPos,                                                          \
         _val,                                                                \
         _matrix->base.itemSize)

#define MkMatrixVal(_matrix) (_matrix->base.value)

typedef struct MkMatrix {
  MkVector base;
  size_t   rows;
  size_t   columns;
} MkMatrix;

MK_EXPORT
MkMatrix *
mkMatrixNew(size_t itemSize,
            size_t rows,
            size_t columns,
            void  *zeroVal,
            void  *oneVal);

MK_EXPORT
void
mkMatrixFill(MkMatrix * __restrict matrix,
             void * value);

MK_EXPORT
MkMatrix *
mkMatrixNew4x4f(bool identity);

MK_EXPORT
MkMatrix *
mkMatrixNew4x4d(bool identity);

MK_EXPORT
MkMatrix *
mkMatrixNewFromf(size_t rows,
                 size_t columns,
                 float * data);

MK_EXPORT
MkMatrix *
mkMatrixNewFromd(size_t rows,
                 size_t columns,
                 double * data);

MK_EXPORT
MkMatrix *
mkMatrixNewFrom4x4f(float * data);

MK_EXPORT
MkMatrix *
mkMatrixNewFrom4x4d(double * data);

MK_EXPORT
void
mkMatrixPrint(MkMatrix * __restrict matrix,
              MkPrintFn itemPrinter,
              FILE * __restrict ostream);

MK_EXPORT
void
mkMatrixTranspose(MkMatrix * __restrict matrix);

MK_EXPORT
bool
mkMatrixIsIdentity(MkMatrix * __restrict matrix);

MK_EXPORT
void
mkMatrixScale(MkMatrix * __restrict matrix,
              void * __restrict other,
              MkOp * __restrict op);

MK_EXPORT
void
mkMatrixMatrixL(MkMatrix * __restrict destMatrix,
                MkMatrix * __restrict matrixL,
                MkOp * __restrict op);

MK_EXPORT
void
mkMatrixMatrixR(MkMatrix * __restrict destMatrix,
                MkMatrix * __restrict matrixR,
                MkOp * __restrict op);

MK_EXPORT
MkMatrix *
mkMatrixMatrix(MkMatrix * __restrict matrixL,
               MkMatrix * __restrict matrixR,
               MkOp * __restrict op);

#ifdef __cplusplus
}
#endif
#endif /* mk_matrix_h */
