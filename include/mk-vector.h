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

MK_EXPORT
void
mkVectorPrint(MkVector * __restrict vec,
              MkPrintFn itemPrinter,
              FILE * __restrict ostream);

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

#define mkVectorDot_impl(T)                                                   \
  do {                                                                        \
    T *pA;                                                                    \
    T *pB;                                                                    \
                                                                              \
    pA = (T *)a->value;                                                       \
    pB = (T *)b->value;                                                       \
                                                                              \
    if (!hint.runtime)                                                        \
       count = hint.count[0];                                                 \
    else                                                                      \
       count = a->count;                                                      \
                                                                              \
    for (i = 0; i < count; i++)                                               \
       dot += pA[i] * pB[i];                                                  \
  } while (0)

MK_INLINE
double
mkVectorDot(MkVector * __restrict a,
            MkVector * __restrict b,
            const MkHint hint) {
   size_t count;
   size_t i;
   double dot;

   dot = 0.0;

   switch (hint.type) {
      case MK_FLOAT:  mkVectorDot_impl(float);   break;
      case MK_DOUBLE: mkVectorDot_impl(double);  break;
      case MK_INT32:  mkVectorDot_impl(int32_t); break;
      case MK_INT64:  mkVectorDot_impl(int64_t); break;
   }

   return dot;
}

#ifdef __cplusplus
}
#endif
#endif /* mk_vector_h */
