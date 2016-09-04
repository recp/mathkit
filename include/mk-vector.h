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

typedef struct MkVector {
  void   *value;
  size_t  isize;
  size_t  count;
  bool    columnv;
} MkVector;

MK_INLINE
void
mkVectorInit(MkVector * __restrict vec,
             void * __restrict value,
             const MkHint hint) {
   vec->count = hint.count[0];
   vec->isize = mkItemSize(hint);
   vec->value = value;
}

MK_INLINE
MkVector *
mkVectorNew(void * __restrict value,
            const MkHint hint) {
   MkVector *vec;

   vec = (MkVector *)malloc(sizeof(*vec));
   mkVectorInit(vec, value, hint);

   return vec;
}

#ifdef __cplusplus
}
#endif
#endif /* mk_vector_h */
