/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mk_matrix_h
#define mk_matrix_h

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

MkMatrix *
mkMatrixNew(size_t itemSize,
            size_t rows,
            size_t columns,
            void  *zeroVal,
            void  *oneVal);

void
mkMatrixFill(MkMatrix * __restrict matrix,
             void * value);

MkMatrix *
mkMatrixNew4x4f(bool identity);

MkMatrix *
mkMatrixNew4x4d(bool identity);

MkMatrix *
mkMatrixNewFromf(size_t rows,
                 size_t columns,
                 float * data);

MkMatrix *
mkMatrixNewFromd(size_t rows,
                 size_t columns,
                 double * data);

MkMatrix *
mkMatrixNewFrom4x4f(float * data);

MkMatrix *
mkMatrixNewFrom4x4d(double * data);

void
mkMatrixPrint(MkMatrix * __restrict matrix,
              MkPrintFn itemPrinter,
              FILE * __restrict ostream);

void
mkMatrixTranspose(MkMatrix * __restrict matrix);

bool
mkMatrixIsIdentity(MkMatrix * __restrict matrix);

void
mkMatrixScale(MkMatrix * __restrict matrix,
              void * __restrict other,
              MkOp * __restrict op);

void
mkMatrixMatrixL(MkMatrix * __restrict destMatrix,
                MkMatrix * __restrict matrixL,
                MkOp * __restrict op);

void
mkMatrixMatrixR(MkMatrix * __restrict destMatrix,
                MkMatrix * __restrict matrixR,
                MkOp * __restrict op);

MkMatrix *
mkMatrixMatrix(MkMatrix * __restrict matrixL,
               MkMatrix * __restrict matrixR,
               MkOp * __restrict op);

#endif /* mk_matrix_h */
