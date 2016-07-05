/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mathkit_h
#define mathkit_h

#include <stdlib.h>
#include <string.h>

#include "mk-common.h"

#define MkMatrixSet(_matrix, _i, _j, _val)                                    \
  memcpy(_matrix->base.value + i * j,                                         \
         _val,                                                                \
         sizeof(_matrix->base.itemSize))

#define MkMatrixSet2(_matrix, _matrixPos, _val)                               \
  memcpy(_matrixPos,                                                          \
         _val,                                                                \
         sizeof(_matrix->base.itemSize))

#define MkMatrixGet(_matrix, _i, _j)                                          \
   (_matrix->base.value + i * j)

typedef struct MkVector {
  size_t itemSize;
  size_t itemCount;
  void * value;
} MkVector;

typedef struct MkMatrix {
  MkVector base;
  size_t   m; /* rows */
  size_t   n; /* columns */
} MkMatrix;

MkMatrix *
mkMatrixNew(size_t itemSize,
            size_t m,
            size_t n);

#endif /* mathkit_h */
