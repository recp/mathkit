/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mk_intrin_avx_h
#define mk_intrin_avx_h
#ifdef __cplusplus
extern "C" {
#endif

#include <immintrin.h>

#define _mm256_m128s(hi, lo)     _mm256_set_m128(hi, lo)
#define _mm_brcst_s(P, V)        _mm_broadcast_s##P(V)
#define _mm256_extr_ps(YMM, IMM) _mm256_extractf128_ps(YMM, IMM)
#define _mm256_extr_pd(YMM, IMM) _mm256_extractf128_pd(YMM, IMM)
#define _mm256_extr_pi(YMM, IMM) _mm256_extractf128_si256(YMM, IMM)

#define _mm_madd8(P, L, R0, R1)                                               \
  _mm256_add_p##P(_mm256_mul_p##P(_mm256_m128##P(_mm_brcst_s(P, L + 1),       \
                                                 _mm_brcst_s(P, L)), R0),     \
                  _mm256_mul_p##P(_mm256_m128##P(_mm_brcst_s(P, L + 3),       \
                                                 _mm_brcst_s(P, L + 2)), R1))


#define _mm256_mmul4(P, D, L, R)                                              \
   do {                                                                       \
      __m256 ymm0;                                                            \
      __m256 ymm1;                                                            \
      __m256 ymm2;                                                            \
                                                                              \
      ymm0 = _mm256_load_ps(R);                                               \
      ymm1 = _mm256_load_ps(R + 8);                                           \
                                                                              \
      ymm2 = _mm_madd8(P, L, ymm0, ymm1);                                     \
      _mm_store_p##P(D, _mm_add_p##P(_mm256_extr_p##P(ymm2, 0),               \
                                     _mm256_extr_p##P(ymm2, 1)));             \
                                                                              \
      ymm2 = _mm_madd8(P, L + 4, ymm0, ymm1);                                 \
      _mm_store_p##P(D + 4, _mm_add_p##P(_mm256_extr_p##P(ymm2, 0),           \
                                         _mm256_extr_p##P(ymm2, 1)));         \
                                                                              \
      ymm2 = _mm_madd8(P, L + 8, ymm0, ymm1);                                 \
      _mm_store_p##P(D + 8, _mm_add_p##P(_mm256_extr_p##P(ymm2, 0),           \
                                         _mm256_extr_p##P(ymm2, 1)));         \
                                                                              \
      ymm2 = _mm_madd8(P, L + 12, ymm0, ymm1);                                \
      _mm_store_p##P(D + 12, _mm_add_p##P(_mm256_extr_p##P(ymm2, 0),          \
                                          _mm256_extr_p##P(ymm2, 1)));        \
                                                                              \
   } while (0)

#ifdef __cplusplus
}
#endif
#endif /* mk_intrin_avx_h */
