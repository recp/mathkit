/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mk_matrix_impl_mat_raw_sse_h
#define mk_matrix_impl_mat_raw_sse_h

#include "mk-intrin-sse.h"

#define mkRawMatrixMult4x4x4_sse_s(L, R, D)                                   \
   do {                                                                       \
      __m128 r0;                                                              \
      __m128 r1;                                                              \
      __m128 r2;                                                              \
      __m128 r3;                                                              \
                                                                              \
      r0 = _mm_load_ps(R);                                                    \
      r1 = _mm_load_ps(R + 4);                                                \
      r2 = _mm_load_ps(R + 8);                                                \
      r3 = _mm_load_ps(R + 12);                                               \
                                                                              \
      _mm_store_ps(D,      _mm_madd4_ps(L,      r0, r1, r2, r3));             \
      _mm_store_ps(D + 4,  _mm_madd4_ps(L + 4,  r0, r1, r2, r3));             \
      _mm_store_ps(D + 8,  _mm_madd4_ps(L + 8,  r0, r1, r2, r3));             \
      _mm_store_ps(D + 12, _mm_madd4_ps(L + 12, r0, r1, r2, r3));             \
   } while (0)

#define mkRawMatrixMult4x4x4_sse_d(L, R, D)                                   \
   do {                                                                       \
      __m128d r0;                                                             \
      __m128d r1;                                                             \
      __m128d r2;                                                             \
      __m128d r3;                                                             \
                                                                              \
      r0 = _mm_load_pd(R);                                                    \
      r1 = _mm_load_pd(R + 4);                                                \
      r2 = _mm_load_pd(R + 8);                                                \
      r3 = _mm_load_pd(R + 12);                                               \
                                                                              \
      _mm_store_pd(D,      _mm_madd4_pd(L,      r0, r1, r2, r3));             \
      _mm_store_pd(D + 4,  _mm_madd4_pd(L + 4,  r0, r1, r2, r3));             \
      _mm_store_pd(D + 8,  _mm_madd4_pd(L + 8,  r0, r1, r2, r3));             \
      _mm_store_pd(D + 12, _mm_madd4_pd(L + 12, r0, r1, r2, r3));             \
                                                                              \
      r0 = _mm_load_pd(R + 2);                                                \
      r1 = _mm_load_pd(R + 6);                                                \
      r2 = _mm_load_pd(R + 10);                                               \
      r3 = _mm_load_pd(R + 14);                                               \
                                                                              \
      _mm_store_pd(D + 2,  _mm_madd4_pd(L,      r0, r1, r2, r3));             \
      _mm_store_pd(D + 6,  _mm_madd4_pd(L + 4,  r0, r1, r2, r3));             \
      _mm_store_pd(D + 10, _mm_madd4_pd(L + 8,  r0, r1, r2, r3));             \
      _mm_store_pd(D + 14, _mm_madd4_pd(L + 12, r0, r1, r2, r3));             \
   } while (0)

#define mkRawMatrixMult3x4x4_sse_s(L, R, D)                                   \
   do {                                                                       \
      __m128 r0;                                                              \
      __m128 r1;                                                              \
      __m128 r2;                                                              \
      __m128 r3;                                                              \
                                                                              \
      r0 = _mm_load_ps(R);                                                    \
      r1 = _mm_load_ps(R + 4);                                                \
      r2 = _mm_load_ps(R + 8);                                                \
      r3 = _mm_load_ps(R + 12);                                               \
                                                                              \
      _mm_store_ps(D,     _mm_madd4_ps(L,     r0, r1, r2, r3));               \
      _mm_store_ps(D + 4, _mm_madd4_ps(L + 4, r0, r1, r2, r3));               \
      _mm_store_ps(D + 8, _mm_madd4_ps(L + 8, r0, r1, r2, r3));               \
   } while (0)

#define mkRawMatrixMult3x4x4_sse_d(L, R, D)                                   \
   do {                                                                       \
      __m128d r0;                                                             \
      __m128d r1;                                                             \
      __m128d r2;                                                             \
      __m128d r3;                                                             \
                                                                              \
      r0 = _mm_load_pd(R);                                                    \
      r1 = _mm_load_pd(R + 4);                                                \
      r2 = _mm_load_pd(R + 8);                                                \
      r3 = _mm_load_pd(R + 12);                                               \
                                                                              \
      _mm_store_pd(D,     _mm_madd4_pd(L,     r0, r1, r2, r3));               \
      _mm_store_pd(D + 4, _mm_madd4_pd(L + 4, r0, r1, r2, r3));               \
      _mm_store_pd(D + 8, _mm_madd4_pd(L + 8, r0, r1, r2, r3));               \
                                                                              \
      r0 = _mm_load_pd(R + 2);                                                \
      r1 = _mm_load_pd(R + 6);                                                \
      r2 = _mm_load_pd(R + 10);                                               \
      r3 = _mm_load_pd(R + 14);                                               \
                                                                              \
      _mm_store_pd(D + 2,  _mm_madd4_pd(L,     r0, r1, r2, r3));              \
      _mm_store_pd(D + 6,  _mm_madd4_pd(L + 4, r0, r1, r2, r3));              \
      _mm_store_pd(D + 10, _mm_madd4_pd(L + 8, r0, r1, r2, r3));              \
   } while (0)

#define mkRawMatrixMult2x4x4_sse_s(L, R, D)                                   \
   do {                                                                       \
      __m128 r0;                                                              \
      __m128 r1;                                                              \
      __m128 r2;                                                              \
      __m128 r3;                                                              \
                                                                              \
      r0 = _mm_load_ps(R);                                                    \
      r1 = _mm_load_ps(R + 4);                                                \
      r2 = _mm_load_ps(R + 8);                                                \
      r3 = _mm_load_ps(R + 12);                                               \
                                                                              \
      _mm_store_ps(D,     _mm_madd4_ps(L,     r0, r1, r2, r3));               \
      _mm_store_ps(D + 4, _mm_madd4_ps(L + 4, r0, r1, r2, r3));               \
   } while (0)

#define mkRawMatrixMult2x4x4_sse_d(L, R, D)                                   \
   do {                                                                       \
      __m128d r0;                                                             \
      __m128d r1;                                                             \
      __m128d r2;                                                             \
      __m128d r3;                                                             \
                                                                              \
      r0 = _mm_load_pd(R);                                                    \
      r1 = _mm_load_pd(R + 4);                                                \
      r2 = _mm_load_pd(R + 8);                                                \
      r3 = _mm_load_pd(R + 12);                                               \
                                                                              \
      _mm_store_pd(D,     _mm_madd4_pd(L,     r0, r1, r2, r3));               \
      _mm_store_pd(D + 4, _mm_madd4_pd(L + 4, r0, r1, r2, r3));               \
                                                                              \
      r0 = _mm_load_pd(R + 2);                                                \
      r1 = _mm_load_pd(R + 6);                                                \
      r2 = _mm_load_pd(R + 10);                                               \
      r3 = _mm_load_pd(R + 14);                                               \
                                                                              \
      _mm_store_pd(D + 2, _mm_madd4_pd(L,     r0, r1, r2, r3));               \
      _mm_store_pd(D + 6, _mm_madd4_pd(L + 4, r0, r1, r2, r3));               \
   } while (0)

#define mkRawMatrixMult4x3x4_sse_s(L, R, D)                                   \
   do {                                                                       \
      __m128 r0;                                                              \
      __m128 r1;                                                              \
      __m128 r2;                                                              \
                                                                              \
      r0 = _mm_load_ps(R);                                                    \
      r1 = _mm_load_ps(R + 4);                                                \
      r2 = _mm_load_ps(R + 8);                                                \
                                                                              \
      _mm_store_ps(D,      _mm_madd3_ps(L,      r0, r1, r2));                 \
      _mm_store_ps(D + 4,  _mm_madd3_ps(L + 4,  r0, r1, r2));                 \
      _mm_store_ps(D + 8,  _mm_madd3_ps(L + 8,  r0, r1, r2));                 \
      _mm_store_ps(D + 12, _mm_madd3_ps(L + 12, r0, r1, r2));                 \
   } while (0)

#define mkRawMatrixMult4x3x4_sse_d(L, R, D)                                   \
   do {                                                                       \
      __m128d r0;                                                             \
      __m128d r1;                                                             \
      __m128d r2;                                                             \
                                                                              \
      r0 = _mm_load_pd(R);                                                    \
      r1 = _mm_load_pd(R + 4);                                                \
      r2 = _mm_load_pd(R + 8);                                                \
                                                                              \
      _mm_store_pd(D,      _mm_madd3_pd(L,      r0, r1, r2));                 \
      _mm_store_pd(D + 4,  _mm_madd3_pd(L + 4,  r0, r1, r2));                 \
      _mm_store_pd(D + 8,  _mm_madd3_pd(L + 8,  r0, r1, r2));                 \
      _mm_store_pd(D + 12, _mm_madd3_pd(L + 12, r0, r1, r2));                 \
                                                                              \
      r0 = _mm_load_pd(R + 2);                                                \
      r1 = _mm_load_pd(R + 6);                                                \
      r2 = _mm_load_pd(R + 10);                                               \
                                                                              \
      _mm_store_pd(D + 2,  _mm_madd3_pd(L,      r0, r1, r2));                 \
      _mm_store_pd(D + 6,  _mm_madd3_pd(L + 4,  r0, r1, r2));                 \
      _mm_store_pd(D + 10, _mm_madd3_pd(L + 8,  r0, r1, r2));                 \
      _mm_store_pd(D + 14, _mm_madd3_pd(L + 12, r0, r1, r2));                 \
   } while (0)

#define mkRawMatrixMult3x3x4_sse_s(L, R, D)                                   \
   do {                                                                       \
      __m128 r0;                                                              \
      __m128 r1;                                                              \
      __m128 r2;                                                              \
                                                                              \
      r0 = _mm_load_ps(R);                                                    \
      r1 = _mm_load_ps(R + 4);                                                \
      r2 = _mm_load_ps(R + 8);                                                \
                                                                              \
      _mm_store_ps(D,     _mm_madd3_ps(L,     r0, r1, r2));                   \
      _mm_store_ps(D + 4, _mm_madd3_ps(L + 4, r0, r1, r2));                   \
      _mm_store_ps(D + 8, _mm_madd3_ps(L + 8, r0, r1, r2));                   \
   } while (0)

#define mkRawMatrixMult3x3x4_sse_d(L, R, D)                                   \
   do {                                                                       \
      __m128d r0;                                                             \
      __m128d r1;                                                             \
      __m128d r2;                                                             \
                                                                              \
      r0 = _mm_load_pd(R);                                                    \
      r1 = _mm_load_pd(R + 4);                                                \
      r2 = _mm_load_pd(R + 8);                                                \
                                                                              \
      _mm_store_pd(D,     _mm_madd3_pd(L,     r0, r1, r2));                   \
      _mm_store_pd(D + 4, _mm_madd3_pd(L + 4, r0, r1, r2));                   \
      _mm_store_pd(D + 8, _mm_madd3_pd(L + 8, r0, r1, r2));                   \
                                                                              \
      r0 = _mm_load_pd(R + 2);                                                \
      r1 = _mm_load_pd(R + 6);                                                \
      r2 = _mm_load_pd(R + 10);                                               \
                                                                              \
      _mm_store_pd(D + 2,  _mm_madd3_pd(L,     r0, r1, r2));                  \
      _mm_store_pd(D + 6,  _mm_madd3_pd(L + 4, r0, r1, r2));                  \
      _mm_store_pd(D + 10, _mm_madd3_pd(L + 8, r0, r1, r2));                  \
   } while (0)

#define mkRawMatrixMult2x3x4_sse_s(L, R, D)                                   \
   do {                                                                       \
      __m128 r0;                                                              \
      __m128 r1;                                                              \
      __m128 r2;                                                              \
                                                                              \
      r0 = _mm_load_ps(R);                                                    \
      r1 = _mm_load_ps(R + 4);                                                \
      r2 = _mm_load_ps(R + 8);                                                \
                                                                              \
      _mm_store_ps(D,     _mm_madd3_ps(L,     r0, r1, r2));                   \
      _mm_store_ps(D + 4, _mm_madd3_ps(L + 4, r0, r1, r2));                   \
   } while (0)

#define mkRawMatrixMult2x3x4_sse_d(L, R, D)                                   \
   do {                                                                       \
      __m128d r0;                                                             \
      __m128d r1;                                                             \
      __m128d r2;                                                             \
                                                                              \
      r0 = _mm_load_pd(R);                                                    \
      r1 = _mm_load_pd(R + 4);                                                \
      r2 = _mm_load_pd(R + 8);                                                \
                                                                              \
      _mm_store_pd(D,     _mm_madd3_pd(L,     r0, r1, r2));                   \
      _mm_store_pd(D + 4, _mm_madd3_pd(L + 4, r0, r1, r2));                   \
                                                                              \
      r0 = _mm_load_pd(R + 2);                                                \
      r1 = _mm_load_pd(R + 6);                                                \
      r2 = _mm_load_pd(R + 10);                                               \
                                                                              \
      _mm_store_pd(D + 2, _mm_madd3_pd(L,     r0, r1, r2));                   \
      _mm_store_pd(D + 6, _mm_madd3_pd(L + 4, r0, r1, r2));                   \
   } while (0)

#define mkRawMatrixMult4x2x4_sse_s(L, R, D)                                   \
   do {                                                                       \
      __m128 r0;                                                              \
      __m128 r1;                                                              \
                                                                              \
      r0 = _mm_load_ps(R);                                                    \
      r1 = _mm_load_ps(R + 4);                                                \
                                                                              \
      _mm_store_ps(D,      _mm_madd_ps(L,      r0, r1));                      \
      _mm_store_ps(D + 4,  _mm_madd_ps(L + 4,  r0, r1));                      \
      _mm_store_ps(D + 8,  _mm_madd_ps(L + 8,  r0, r1));                      \
      _mm_store_ps(D + 12, _mm_madd_ps(L + 12, r0, r1));                      \
   } while (0)

#define mkRawMatrixMult4x2x4_sse_d(L, R, D)                                   \
   do {                                                                       \
      __m128d r0;                                                             \
      __m128d r1;                                                             \
                                                                              \
      r0 = _mm_load_pd(R);                                                    \
      r1 = _mm_load_pd(R + 4);                                                \
                                                                              \
      _mm_store_pd(D,      _mm_madd_pd(L,      r0, r1));                      \
      _mm_store_pd(D + 4,  _mm_madd_pd(L + 4,  r0, r1));                      \
      _mm_store_pd(D + 8,  _mm_madd_pd(L + 8,  r0, r1));                      \
      _mm_store_pd(D + 12, _mm_madd_pd(L + 12, r0, r1));                      \
                                                                              \
      r0 = _mm_load_pd(R + 2);                                                \
      r1 = _mm_load_pd(R + 6);                                                \
                                                                              \
      _mm_store_pd(D + 2,  _mm_madd_pd(L,      r0, r1));                      \
      _mm_store_pd(D + 6,  _mm_madd_pd(L + 4,  r0, r1));                      \
      _mm_store_pd(D + 10, _mm_madd_pd(L + 8,  r0, r1));                      \
      _mm_store_pd(D + 14, _mm_madd_pd(L + 12, r0, r1));                      \
   } while (0)

#define mkRawMatrixMult3x2x4_sse_s(L, R, D)                                   \
   do {                                                                       \
      __m128 r0;                                                              \
      __m128 r1;                                                              \
                                                                              \
      r0 = _mm_load_ps(R);                                                    \
      r1 = _mm_load_ps(R + 4);                                                \
                                                                              \
      _mm_store_ps(D,     _mm_madd_ps(L,     r0, r1));                        \
      _mm_store_ps(D + 4, _mm_madd_ps(L + 4, r0, r1));                        \
      _mm_store_ps(D + 8, _mm_madd_ps(L + 8, r0, r1));                        \
   } while (0)

#define mkRawMatrixMult3x2x4_sse_d(L, R, D)                                   \
   do {                                                                       \
      __m128d r0;                                                             \
      __m128d r1;                                                             \
                                                                              \
      r0 = _mm_load_pd(R);                                                    \
      r1 = _mm_load_pd(R + 4);                                                \
                                                                              \
      _mm_store_pd(D,     _mm_madd_pd(L,     r0, r1));                        \
      _mm_store_pd(D + 4, _mm_madd_pd(L + 4, r0, r1));                        \
      _mm_store_pd(D + 8, _mm_madd_pd(L + 8, r0, r1));                        \
                                                                              \
      r0 = _mm_load_pd(R + 2);                                                \
      r1 = _mm_load_pd(R + 6);                                                \
                                                                              \
      _mm_store_pd(D + 2,  _mm_madd_pd(L,     r0, r1));                       \
      _mm_store_pd(D + 6,  _mm_madd_pd(L + 4, r0, r1));                       \
      _mm_store_pd(D + 10, _mm_madd_pd(L + 8, r0, r1));                       \
   } while (0)

#define mkRawMatrixMult2x2x4_sse_s(L, R, D)                                   \
   do {                                                                       \
      __m128 r0;                                                              \
      __m128 r1;                                                              \
                                                                              \
      r0 = _mm_load_ps(R);                                                    \
      r1 = _mm_load_ps(R + 4);                                                \
                                                                              \
      _mm_store_ps(D,     _mm_madd_ps(L,     r0, r1));                        \
      _mm_store_ps(D + 4, _mm_madd_ps(L + 4, r0, r1));                        \
   } while (0)

#define mkRawMatrixMult2x2x4_sse_d(L, R, D)                                   \
   do {                                                                       \
      __m128d r0;                                                             \
      __m128d r1;                                                             \
                                                                              \
      r0 = _mm_load_pd(R);                                                    \
      r1 = _mm_load_pd(R + 4);                                                \
                                                                              \
      _mm_store_pd(D,     _mm_madd_pd(L,     r0, r1));                        \
      _mm_store_pd(D + 4, _mm_madd_pd(L + 4, r0, r1));                        \
                                                                              \
      r0 = _mm_load_pd(R + 2);                                                \
      r1 = _mm_load_pd(R + 6);                                                \
                                                                              \
      _mm_store_pd(D + 2, _mm_madd_pd(L,     r0, r1));                        \
      _mm_store_pd(D + 6, _mm_madd_pd(L + 4, r0, r1));                        \
   } while (0)

#endif /* mk_matrix_impl_mat_raw_sse_h */
