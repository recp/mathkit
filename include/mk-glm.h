/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mk_glm_h
#define mk_glm_h

#include <stdlib.h>

#include "mk-common.h"
#include "mk-vector.h"
#include "mk-matrix.h"

#define mkLookAt_impl(T)                                                      \
  do {                                                                        \
   T *pD;                                                                     \
   T *pS;                                                                     \
   T *pF;                                                                     \
   T *pU;                                                                     \
   mkVLANew(char, mkItemSize(hint) * 12);                                     \
                                                                              \
   MkVector F;                                                                \
   MkVector f;                                                                \
   MkVector u;                                                                \
   MkVector s;                                                                \
                                                                              \
   mkVectorInit(&F, (void *)tmp, hint);                                       \
   mkVectorInit(&f, (void *)(tmp + 3), hint);                                 \
   mkVectorInit(&u, (void *)(tmp + 6), hint);                                 \
   mkVectorInit(&s, (void *)(tmp + 9), hint);                                 \
                                                                              \
   pS = (T *)s.value;                                                         \
   pU = (T *)u.value;                                                         \
   pF = (T *)f.value;                                                         \
   pD = (T *)dest->value;                                                     \
                                                                              \
   /* f */                                                                    \
   mkVectorVectorSub(center, eye, &F, hint);                                  \
   mkVectorNormalize(&F, &f, hint);                                           \
                                                                              \
   /* s */                                                                    \
   mkVectorCross(&f, up, &F, hint);                                           \
   mkVectorNormalize(&F, &s, hint);                                           \
                                                                              \
   /* u */                                                                    \
   mkVectorCross(&s, &f, &u, hint);                                           \
                                                                              \
   pD[0]  =  pS[0];                                                           \
   pD[4]  =  pS[1];                                                           \
   pD[8]  =  pS[2];                                                           \
   pD[1]  =  pU[0];                                                           \
   pD[5]  =  pU[1];                                                           \
   pD[9]  =  pU[2];                                                           \
   pD[2]  = -pF[0];                                                           \
   pD[6]  = -pF[1];                                                           \
   pD[10] = -pF[2];                                                           \
   pD[12] = -mkVectorDot(&s, eye, hint);                                      \
   pD[13] = -mkVectorDot(&u, eye, hint);                                      \
   pD[14] =  mkVectorDot(&f, eye, hint);                                      \
   pD[3]  =  0;                                                               \
   pD[7]  =  0;                                                               \
   pD[11] =  0;                                                               \
   pD[15] =  1;                                                               \
                                                                              \
   mkVLAFree(tmp);                                                            \
  } while (0)

MK_INLINE
void
mkLookAt(MkVector * __restrict eye,
         MkVector * __restrict center,
         MkVector * __restrict up,
         MkMatrix * __restrict dest,
         const MkHint hint) {
   switch (hint.type) {
      case MK_FLOAT:  mkLookAt_impl(float);   break;
      case MK_DOUBLE: mkLookAt_impl(double);  break;
      case MK_INT32:  mkLookAt_impl(int32_t); break;
      case MK_INT64:  mkLookAt_impl(int64_t); break;
   }
}

#endif /* mk_glm_h */
