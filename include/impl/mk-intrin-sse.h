/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mk_intrin_sse_h
#define mk_intrin_sse_h

#include <xmmintrin.h>

#define _mm_madd4(P, L0, R0, R1, R2, R3)                                      \
   _mm_add_##P(_mm_add_##P(_mm_mul_##P(_mm_set1_##P(*L0), R0),                \
                           _mm_mul_##P(_mm_set1_##P(*(L0 + 1)), R1)),         \
               _mm_add_##P(_mm_mul_##P(_mm_set1_##P(*(L0 + 2)), R2),          \
                           _mm_mul_##P(_mm_set1_##P(*(L0 + 3)), R3)))

#define _mm_mmul4(P, D, L, R)                                                 \
   do {                                                                       \
      __m128 r0;                                                              \
      __m128 r1;                                                              \
      __m128 r2;                                                              \
      __m128 r3;                                                              \
                                                                              \
      r0 = _mm_load_##P(R);                                                   \
      r1 = _mm_load_##P(R + 4);                                               \
      r2 = _mm_load_##P(R + 8);                                               \
      r3 = _mm_load_##P(R + 12);                                              \
                                                                              \
      _mm_store_##P(D,      _mm_madd4(P, L,      r0, r1, r2, r3));            \
      _mm_store_##P(D + 4,  _mm_madd4(P, L + 4,  r0, r1, r2, r3));            \
      _mm_store_##P(D + 8,  _mm_madd4(P, L + 8,  r0, r1, r2, r3));            \
      _mm_store_##P(D + 12, _mm_madd4(P, L + 12, r0, r1, r2, r3));            \
   } while (0)

#endif /* mk_intrin_sse_h */
