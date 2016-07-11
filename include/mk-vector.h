/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mk_vector_h
#define mk_vector_h

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
  void      *value;
  MkVecFlags flags;
} MkVector;

MkVector *
mkVecNew(size_t itemSize,
         size_t itemCount,
         void  *value,
         void  *zeroVal,
         void  *oneVal);

MkVector *
mkVecNewf(size_t itemCount,
          float *value);

MkVector *
mkVecNewd(size_t  itemCount,
          double *value);

MkVector *
mkVecNew3f(float x, float y, float z);

MkVector *
mkVecNew3d(double x, double y, double z);

#endif /* mk_vector_h */
