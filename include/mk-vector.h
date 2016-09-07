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
#include <math.h>

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

#define mkVectorCross_impl(T)                                                 \
  do {                                                                        \
   T *pA;                                                                     \
   T *pB;                                                                     \
   T *pD;                                                                     \
                                                                              \
   pA = (T *)a->value;                                                        \
   pB = (T *)b->value;                                                        \
   pD = (T *)dest->value;                                                     \
                                                                              \
   /* (u2.v3 - u3.v2, u3.v1 - u1.v3, u1.v2 - u2.v1) */                        \
   pD[0] = pA[1] * pB[2] - pA[2] * pB[1];                                     \
   pD[1] = pA[2] * pB[0] - pA[0] * pB[2];                                     \
   pD[2] = pA[0] * pB[1] - pA[1] * pB[0];                                     \
  } while (0)

MK_INLINE
void
mkVectorCross(MkVector * __restrict a,
              MkVector * __restrict b,
              MkVector * __restrict dest,
              const MkHint hint) {
   switch (hint.type) {
      case MK_FLOAT:  mkVectorCross_impl(float);   break;
      case MK_DOUBLE: mkVectorCross_impl(double);  break;
      case MK_INT32:  mkVectorCross_impl(int32_t); break;
      case MK_INT64:  mkVectorCross_impl(int64_t); break;
   }
}

#define mkVectorNorm_impl(T)                                                  \
  do {                                                                        \
    T *pA;                                                                    \
                                                                              \
    pA = (T *)a->value;                                                       \
                                                                              \
    if (!hint.runtime)                                                        \
      count = hint.count[0];                                                  \
    else                                                                      \
      count = a->count;                                                       \
                                                                              \
    for (i = 0; i < count; i++)                                               \
      norm += pA[i] * pA[i];                                                  \
  } while (0)

/* Euclidean norm */
MK_INLINE
double
mkVectorNorm(MkVector * __restrict a,
             const MkHint hint) {
   size_t count;
   size_t i;
   double norm;

   norm = 0.0;

   switch (hint.type) {
      case MK_FLOAT:  mkVectorNorm_impl(float);   break;
      case MK_DOUBLE: mkVectorNorm_impl(double);  break;
      case MK_INT32:  mkVectorNorm_impl(int32_t); break;
      case MK_INT64:  mkVectorNorm_impl(int64_t); break;
   }

   return sqrt(norm);
}

MK_INLINE
double
mkVectorMagnitude(MkVector * __restrict a,
                  const MkHint hint) {
   return mkVectorNorm(a, hint);
}

#ifdef __cplusplus
}
#endif
#endif /* mk_vector_h */
