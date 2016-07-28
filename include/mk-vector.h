/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mk_vector_h
#define mk_vector_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "mk-common.h"
#include "mk-vector.h"

typedef enum MkVecFlags {
  MK_VEC_FLAGS_COLUMN = 0,
  MK_VEC_FLAGS_ROW    = 1
} MkVecFlags;

typedef struct MkVector {
  size_t     itemSize;
  size_t     itemCount;
  char      *value;
  MkVecFlags flags;
} MkVector;

#ifdef __cplusplus
}
#endif
#endif /* mk_vector_h */
