/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../../include/mk.h"
#include "../../include/mk-vector.h"
#include <assert.h>

MK_EXPORT
MkVector *
mkVecNew(size_t itemSize,
         size_t itemCount,
         void  *value,
         void  *zeroVal,
         void  *oneVal) {
  MkVector *vec;

  vec = calloc(sizeof(*vec), 1);
  vec->itemSize  = itemSize;
  vec->itemCount = itemCount;

  if (value)
    vec->value = value;
  else
    /* +1 for zeroVal, +1 for oneVal */
    value = calloc(itemSize, vec->itemCount + 2);

  memcpy(value, zeroVal, itemSize);
  memcpy((char *)value + itemSize, oneVal, itemSize);

  vec->value = (char *)value + itemSize * 2;

  return vec;
}

MK_EXPORT
MkVector *
mkVecNewf(size_t itemCount,
          float *value) {
  MkVector *vec;

  vec = mkVecNew(sizeof(float),
                 itemCount,
                 value,
                 MkFloatZero,
                 MkFloatOne);

  return vec;
}

MK_EXPORT
MkVector *
mkVecNewd(size_t  itemCount,
          double *value) {
  MkVector *vec;

  vec = mkVecNew(sizeof(double),
                 itemCount,
                 value,
                 MkDoubleZero,
                 MkDoubleOne);

  return vec;
}

MK_EXPORT
MkVector *
mkVecNew3f(float x, float y, float z) {
  MkVector *vec;
  float    *val;

  vec = mkVecNew(sizeof(float),
                 3,
                 NULL,
                 MkFloatZero,
                 MkFloatOne);

  val = (float *)vec->value;

  val[0] = x;
  val[1] = y;
  val[2] = z;

  return vec;
}

MK_EXPORT
MkVector *
mkVecNew3d(double x, double y, double z) {
  MkVector *vec;
  double   *val;

  vec = mkVecNew(sizeof(float),
                 3,
                 NULL,
                 MkFloatZero,
                 MkFloatOne);

  val = (double *)vec->value;

  val[0] = x;
  val[1] = y;
  val[2] = z;

  return vec;
}
