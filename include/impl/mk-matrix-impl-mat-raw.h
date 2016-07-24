/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mk_matrix_impl_mat_raw_h
#define mk_matrix_impl_mat_raw_h
#ifdef __cplusplus
extern "C" {
#endif

#include "mk-matrix-impl-raw.h"
#include <stdlib.h>

__attribute__((always_inline))
inline
void
mkGlmMatrixAdd4x4(float * __restrict m,
                  float val) {
   m[0]  += val; m[1]  += val;
   m[2]  += val; m[3]  += val;
   m[4]  += val; m[5]  += val;
   m[6]  += val; m[7]  += val;
   m[8]  += val; m[9]  += val;
   m[10] += val; m[11] += val;
   m[12] += val; m[13] += val;
   m[14] += val; m[15] += val;
}

__attribute__((always_inline))
inline
void
mkGlmMatrixAdd4x4d(double * __restrict m,
                   double val) {
   m[0]  += val; m[1]  += val;
   m[2]  += val; m[3]  += val;
   m[4]  += val; m[5]  += val;
   m[6]  += val; m[7]  += val;
   m[8]  += val; m[9]  += val;
   m[10] += val; m[11] += val;
   m[12] += val; m[13] += val;
   m[14] += val; m[15] += val;
}

__attribute__((always_inline))
inline
void
mkGlmMatrixScale4x4(float * __restrict m,
                    float val) {
   m[0]  *= val; m[1]  *= val;
   m[2]  *= val; m[3]  *= val;
   m[4]  *= val; m[5]  *= val;
   m[6]  *= val; m[7]  *= val;
   m[8]  *= val; m[9]  *= val;
   m[10] *= val; m[11] *= val;
   m[12] *= val; m[13] *= val;
   m[14] *= val; m[15] *= val;
}

__attribute__((always_inline))
inline
void
mkGlmMatrixScale4x4d(double * __restrict m,
                     double val) {
   m[0]  *= val; m[1]  *= val;
   m[2]  *= val; m[3]  *= val;
   m[4]  *= val; m[5]  *= val;
   m[6]  *= val; m[7]  *= val;
   m[8]  *= val; m[9]  *= val;
   m[10] *= val; m[11] *= val;
   m[12] *= val; m[13] *= val;
   m[14] *= val; m[15] *= val;
}

__attribute__((always_inline))
inline
void
mkGlmMatrixMatrixAdd4x4(float * __restrict m,
                        float * __restrict m2) {
   m[0]  += m2[0];  m[1]  += m2[1];
   m[2]  += m2[2];  m[3]  += m2[3];
   m[4]  += m2[4];  m[5]  += m2[5];
   m[6]  += m2[6];  m[7]  += m2[7];
   m[8]  += m2[8];  m[9]  += m2[9];
   m[10] += m2[10]; m[11] += m2[11];
   m[12] += m2[12]; m[13] += m2[13];
   m[14] += m2[14]; m[15] += m2[15];
}

__attribute__((always_inline))
inline
void
mkGlmMatrixMatrixAdd4x4d(double * __restrict m,
                         double * __restrict m2) {
   m[0]  += m2[0];  m[1]  += m2[1];
   m[2]  += m2[2];  m[3]  += m2[3];
   m[4]  += m2[4];  m[5]  += m2[5];
   m[6]  += m2[6];  m[7]  += m2[7];
   m[8]  += m2[8];  m[9]  += m2[9];
   m[10] += m2[10]; m[11] += m2[11];
   m[12] += m2[12]; m[13] += m2[13];
   m[14] += m2[14]; m[15] += m2[15];
}

__attribute__((always_inline))
inline
void
mkRawMatrixMult4f(float * __restrict l,
                  float * __restrict r,
                  float * __restrict d) {
   d[0]  = l[0]  * r[0] + l[1]  * r[4] + l[2]  * r[8]  + l[3]  * r[12];
   d[1]  = l[0]  * r[1] + l[1]  * r[5] + l[2]  * r[9]  + l[3]  * r[13];
   d[2]  = l[0]  * r[2] + l[1]  * r[6] + l[2]  * r[10] + l[3]  * r[14];
   d[3]  = l[0]  * r[3] + l[1]  * r[7] + l[2]  * r[11] + l[3]  * r[15];
   d[4]  = l[4]  * r[0] + l[5]  * r[4] + l[6]  * r[8]  + l[7]  * r[12];
   d[5]  = l[4]  * r[1] + l[5]  * r[5] + l[6]  * r[9]  + l[7]  * r[13];
   d[6]  = l[4]  * r[2] + l[5]  * r[6] + l[6]  * r[10] + l[7]  * r[14];
   d[7]  = l[4]  * r[3] + l[5]  * r[7] + l[6]  * r[11] + l[7]  * r[15];
   d[8]  = l[8]  * r[0] + l[9]  * r[4] + l[10] * r[8]  + l[11] * r[12];
   d[9]  = l[8]  * r[1] + l[9]  * r[5] + l[10] * r[9]  + l[11] * r[13];
   d[10] = l[8]  * r[2] + l[9]  * r[6] + l[10] * r[10] + l[11] * r[14];
   d[11] = l[8]  * r[3] + l[9]  * r[7] + l[10] * r[11] + l[11] * r[15];
   d[12] = l[12] * r[0] + l[13] * r[4] + l[14] * r[8]  + l[15] * r[12];
   d[13] = l[12] * r[1] + l[13] * r[5] + l[14] * r[9]  + l[15] * r[13];
   d[14] = l[12] * r[2] + l[13] * r[6] + l[14] * r[10] + l[15] * r[14];
   d[15] = l[12] * r[3] + l[13] * r[7] + l[14] * r[11] + l[15] * r[15];
}

__attribute__((always_inline))
inline
void
mkRawMatrixMult4x4x3f(float * __restrict l,
                      float * __restrict r,
                      float * __restrict d) {
   d[0]  = l[0]  * r[0] + l[1]  * r[4] + l[2]  * r[8]  + l[3]  * r[12];
   d[1]  = l[0]  * r[1] + l[1]  * r[5] + l[2]  * r[9]  + l[3]  * r[13];
   d[2]  = l[0]  * r[2] + l[1]  * r[6] + l[2]  * r[10] + l[3]  * r[14];
   d[3]  = l[0]  * r[3] + l[1]  * r[7] + l[2]  * r[11] + l[3]  * r[15];
   d[4]  = l[4]  * r[0] + l[5]  * r[4] + l[6]  * r[8]  + l[7]  * r[12];
   d[5]  = l[4]  * r[1] + l[5]  * r[5] + l[6]  * r[9]  + l[7]  * r[13];
   d[6]  = l[4]  * r[2] + l[5]  * r[6] + l[6]  * r[10] + l[7]  * r[14];
   d[7]  = l[4]  * r[3] + l[5]  * r[7] + l[6]  * r[11] + l[7]  * r[15];
   d[8]  = l[8]  * r[0] + l[9]  * r[4] + l[10] * r[8]  + l[11] * r[12];
   d[9]  = l[8]  * r[1] + l[9]  * r[5] + l[10] * r[9]  + l[11] * r[13];
   d[10] = l[8]  * r[2] + l[9]  * r[6] + l[10] * r[10] + l[11] * r[14];
   d[11] = l[8]  * r[3] + l[9]  * r[7] + l[10] * r[11] + l[11] * r[15];
}

__attribute__((always_inline))
inline
void
mkRawMatrixTranspose4f(float * __restrict m,
                       float * __restrict d) {
   d[0]  = m[0]; d[1]  = m[4]; d[2]  = m[8];  d[3]  = m[12];
   d[4]  = m[1]; d[5]  = m[5]; d[6]  = m[9];  d[7]  = m[13];
   d[8]  = m[2]; d[9]  = m[6]; d[10] = m[10]; d[11] = m[14];
   d[12] = m[3]; d[13] = m[7]; d[14] = m[11]; d[15] = m[15];
}

__attribute__((always_inline))
inline
void
mkRawMatrixMult(void * __restrict mL,
                void * __restrict mR,
                void * __restrict mDest,
                const MkBufLayout lay[2]) {
   switch (lay[0].count[0]) {
      case 4:
         switch (lay[1].count[1]) {
            case 4:
               switch (lay[1].count[1]) {
                  /* 4x4 4x4 */
                  case 4: mkRawMatrixMult4f((float *)mL,
                                            (float *)mR,
                                            (float *)mDest); break;

                  /* 4x4 4x3 */
                  case 3: break;

                  /* 4x4 4x2 */
                  case 2: break;

                  default:
                     break;
               }
               break;
            default:
               break;
         }
         break;
      default:
         break;
   }
}

#ifdef __cplusplus
}
#endif
#endif /* mk_matrix_impl_mat_raw_h */
