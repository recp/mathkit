/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mathkit_h
#  define mathkit_h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "mk-common.h"

#define MkMatrixGet(_matrix, _i, _j)                                          \
  ((char *)_matrix->base.value                                                \
        + (_i * _matrix->rows + _j) * (_matrix->base.itemSize))

#define MkMatrixSet(_matrix, _i, _j, _val)                                    \
  memcpy(MkMatrixGet(_matrix, _i, _j),                                        \
         _val,                                                                \
         sizeof(_matrix->base.itemSize))

#define MkMatrixSet2(_matrix, _matrixPos, _val)                               \
  memcpy(_matrixPos,                                                          \
         _val,                                                                \
         sizeof(_matrix->base.itemSize))


typedef void (*MkPrintFn)(FILE * __restrict ostream,
                          void * __restrict item);

typedef void (*MkOp)(void * __restrict a, void * __restrict b);

typedef struct MkVector {
  size_t itemSize;
  size_t itemCount;
  void   *value;
} MkVector;

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
mkMatrixPrint(MkMatrix * matrix,
              MkPrintFn itemPrinter,
              FILE * __restrict ostream);

void
mkMatrixTranspose(MkMatrix * matrix);

bool
mkMatrixIsIdentity(MkMatrix * matrix);

void
mkMatrixApplyScalarL(void * __restrict other,
                     MkMatrix * matrix,
                     MkOp op);


/* buit-in operators */

/* scalar multiplication operators
 *
 * mkOp [OpType][Param1 Type][Param2 Type]
 * mkOp [OpType][Param1 and Param2 Type]
 *
 * Op Types:
 *   M: multiplication
 */

MK_EXTERN
MkOp mkOpMFlt;

MK_EXTERN
MkOp mkOpMDbl;

MK_EXTERN
MkOp mkOpMInt32;

MK_EXTERN
MkOp mkOpMInt64;

/* buit-in printers */

MK_EXTERN
MkPrintFn mkFloatPrinter;

MK_EXTERN
MkPrintFn mkDoublePrinter;

#endif /* mathkit_h */
