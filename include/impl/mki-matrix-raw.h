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

#include <stdlib.h>

#define mkRawMatrixMult4x4x4(l, r, d)                                         \
 do {                                                                         \
    d[0]  = l[0]  * r[0] + l[1]  * r[4] + l[2]  * r[8]  + l[3]  * r[12];      \
    d[1]  = l[0]  * r[1] + l[1]  * r[5] + l[2]  * r[9]  + l[3]  * r[13];      \
    d[2]  = l[0]  * r[2] + l[1]  * r[6] + l[2]  * r[10] + l[3]  * r[14];      \
    d[3]  = l[0]  * r[3] + l[1]  * r[7] + l[2]  * r[11] + l[3]  * r[15];      \
    d[4]  = l[4]  * r[0] + l[5]  * r[4] + l[6]  * r[8]  + l[7]  * r[12];      \
    d[5]  = l[4]  * r[1] + l[5]  * r[5] + l[6]  * r[9]  + l[7]  * r[13];      \
    d[6]  = l[4]  * r[2] + l[5]  * r[6] + l[6]  * r[10] + l[7]  * r[14];      \
    d[7]  = l[4]  * r[3] + l[5]  * r[7] + l[6]  * r[11] + l[7]  * r[15];      \
    d[8]  = l[8]  * r[0] + l[9]  * r[4] + l[10] * r[8]  + l[11] * r[12];      \
    d[9]  = l[8]  * r[1] + l[9]  * r[5] + l[10] * r[9]  + l[11] * r[13];      \
    d[10] = l[8]  * r[2] + l[9]  * r[6] + l[10] * r[10] + l[11] * r[14];      \
    d[11] = l[8]  * r[3] + l[9]  * r[7] + l[10] * r[11] + l[11] * r[15];      \
    d[12] = l[12] * r[0] + l[13] * r[4] + l[14] * r[8]  + l[15] * r[12];      \
    d[13] = l[12] * r[1] + l[13] * r[5] + l[14] * r[9]  + l[15] * r[13];      \
    d[14] = l[12] * r[2] + l[13] * r[6] + l[14] * r[10] + l[15] * r[14];      \
    d[15] = l[12] * r[3] + l[13] * r[7] + l[14] * r[11] + l[15] * r[15];      \
  } while (0)

#define mkRawMatrixMult4x4x3(l, r, d)                                         \
  do {                                                                        \
    d[0]  = l[0]  * r[0] + l[1]  * r[3] + l[2]  * r[6] + l[3]  * r[9];        \
    d[1]  = l[0]  * r[1] + l[1]  * r[4] + l[2]  * r[7] + l[3]  * r[10];       \
    d[2]  = l[0]  * r[2] + l[1]  * r[5] + l[2]  * r[8] + l[3]  * r[11];       \
    d[3]  = l[4]  * r[0] + l[5]  * r[3] + l[6]  * r[6] + l[7]  * r[9];        \
    d[4]  = l[4]  * r[1] + l[5]  * r[4] + l[6]  * r[7] + l[7]  * r[10];       \
    d[5]  = l[4]  * r[2] + l[5]  * r[5] + l[6]  * r[8] + l[7]  * r[11];       \
    d[6]  = l[8]  * r[0] + l[9]  * r[3] + l[10] * r[6] + l[11] * r[9];        \
    d[7]  = l[8]  * r[1] + l[9]  * r[4] + l[10] * r[7] + l[11] * r[10];       \
    d[8]  = l[8]  * r[2] + l[9]  * r[5] + l[10] * r[8] + l[11] * r[11];       \
    d[9]  = l[12] * r[0] + l[13] * r[3] + l[14] * r[6] + l[15] * r[9];        \
    d[10] = l[12] * r[1] + l[13] * r[4] + l[14] * r[7] + l[15] * r[10];       \
    d[11] = l[12] * r[2] + l[13] * r[5] + l[14] * r[8] + l[15] * r[11];       \
  } while (0)
    
#define mkRawMatrixMult4x4x2(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0]  * r[0] + l[1]  * r[2] + l[2]  * r[4] + l[3]  * r[6];         \
    d[1] = l[0]  * r[1] + l[1]  * r[3] + l[2]  * r[5] + l[3]  * r[7];         \
    d[2] = l[4]  * r[0] + l[5]  * r[2] + l[6]  * r[4] + l[7]  * r[6];         \
    d[3] = l[4]  * r[1] + l[5]  * r[3] + l[6]  * r[5] + l[7]  * r[7];         \
    d[4] = l[8]  * r[0] + l[8]  * r[2] + l[9]  * r[4] + l[10] * r[6];         \
    d[5] = l[8]  * r[1] + l[8]  * r[3] + l[9]  * r[5] + l[10] * r[7];         \
    d[6] = l[12] * r[0] + l[13] * r[2] + l[14] * r[4] + l[15] * r[6];         \
    d[7] = l[12] * r[1] + l[13] * r[3] + l[14] * r[5] + l[15] * r[7];         \
  } while (0)
  
#define mkRawMatrixMult3x4x4(l, r, d)                                         \
  do {                                                                        \
    d[0]  = l[0] * r[0] + l[1]  * r[4] + l[2]  * r[8]  + l[3]  * r[12];       \
    d[1]  = l[0] * r[1] + l[1]  * r[5] + l[2]  * r[9]  + l[3]  * r[13];       \
    d[2]  = l[0] * r[2] + l[1]  * r[6] + l[2]  * r[10] + l[3]  * r[14];       \
    d[3]  = l[0] * r[3] + l[1]  * r[7] + l[2]  * r[11] + l[3]  * r[15];       \
    d[4]  = l[4] * r[0] + l[5]  * r[4] + l[6]  * r[8]  + l[7]  * r[12];       \
    d[5]  = l[4] * r[1] + l[5]  * r[5] + l[6]  * r[9]  + l[7]  * r[13];       \
    d[6]  = l[4] * r[2] + l[5]  * r[6] + l[6]  * r[10] + l[7]  * r[14];       \
    d[7]  = l[4] * r[3] + l[5]  * r[7] + l[6]  * r[11] + l[7]  * r[15];       \
    d[8]  = l[8] * r[0] + l[9]  * r[4] + l[10] * r[8]  + l[11] * r[12];       \
    d[9]  = l[8] * r[1] + l[9]  * r[5] + l[10] * r[9]  + l[11] * r[13];       \
    d[10] = l[8] * r[2] + l[9]  * r[6] + l[10] * r[10] + l[11] * r[14];       \
    d[11] = l[8] * r[3] + l[9]  * r[7] + l[10] * r[11] + l[11] * r[15];       \
  } while (0)

#define mkRawMatrixMult3x4x3(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0] * r[0] + l[1] * r[3] + l[2]  * r[6] + l[3]  * r[9];           \
    d[1] = l[0] * r[1] + l[1] * r[4] + l[2]  * r[7] + l[3]  * r[10];          \
    d[2] = l[0] * r[2] + l[1] * r[5] + l[2]  * r[8] + l[3]  * r[11];          \
    d[3] = l[4] * r[0] + l[5] * r[3] + l[6]  * r[6] + l[7]  * r[9];           \
    d[4] = l[4] * r[1] + l[5] * r[4] + l[6]  * r[7] + l[7]  * r[10];          \
    d[5] = l[4] * r[2] + l[5] * r[5] + l[6]  * r[8] + l[7]  * r[11];          \
    d[6] = l[8] * r[0] + l[9] * r[3] + l[10] * r[6] + l[11] * r[9];           \
    d[7] = l[8] * r[1] + l[9] * r[4] + l[10] * r[7] + l[11] * r[10];          \
    d[8] = l[8] * r[2] + l[9] * r[5] + l[10] * r[8] + l[11] * r[11];          \
  } while (0)

#define mkRawMatrixMult3x4x2(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0] * r[0] + l[1] * r[2] + l[2] * r[4] + l[3]  * r[6];            \
    d[1] = l[0] * r[1] + l[1] * r[3] + l[2] * r[5] + l[3]  * r[7];            \
    d[2] = l[4] * r[0] + l[5] * r[2] + l[6] * r[4] + l[7]  * r[6];            \
    d[3] = l[4] * r[1] + l[5] * r[3] + l[6] * r[5] + l[7]  * r[7];            \
    d[4] = l[8] * r[0] + l[8] * r[2] + l[9] * r[4] + l[10] * r[6];            \
    d[5] = l[8] * r[1] + l[8] * r[3] + l[9] * r[5] + l[10] * r[7];            \
  } while (0)

#define mkRawMatrixMult2x4x4(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0] * r[0] + l[1] * r[4] + l[2] * r[8]  + l[3] * r[12];           \
    d[1] = l[0] * r[1] + l[1] * r[5] + l[2] * r[9]  + l[3] * r[13];           \
    d[2] = l[0] * r[2] + l[1] * r[6] + l[2] * r[10] + l[3] * r[14];           \
    d[3] = l[0] * r[3] + l[1] * r[7] + l[2] * r[11] + l[3] * r[15];           \
    d[4] = l[4] * r[0] + l[5] * r[4] + l[6] * r[8]  + l[7] * r[12];           \
    d[5] = l[4] * r[1] + l[5] * r[5] + l[6] * r[9]  + l[7] * r[13];           \
    d[6] = l[4] * r[2] + l[5] * r[6] + l[6] * r[10] + l[7] * r[14];           \
    d[7] = l[4] * r[3] + l[5] * r[7] + l[6] * r[11] + l[7] * r[15];           \
  } while (0)

#define mkRawMatrixMult2x4x3(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0] * r[0] + l[1] * r[3] + l[2] * r[6] + l[3] * r[9];             \
    d[1] = l[0] * r[1] + l[1] * r[4] + l[2] * r[7] + l[3] * r[10];            \
    d[2] = l[0] * r[2] + l[1] * r[5] + l[2] * r[8] + l[3] * r[11];            \
    d[3] = l[4] * r[0] + l[5] * r[3] + l[6] * r[6] + l[7] * r[9];             \
    d[4] = l[4] * r[1] + l[5] * r[4] + l[6] * r[7] + l[7] * r[10];            \
    d[5] = l[4] * r[2] + l[5] * r[5] + l[6] * r[8] + l[7] * r[11];            \
  } while (0)

#define mkRawMatrixMult2x4x2(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0] * r[0] + l[1] * r[2] + l[2] * r[4] + l[3] * r[6];             \
    d[1] = l[0] * r[1] + l[1] * r[3] + l[2] * r[5] + l[3] * r[7];             \
    d[2] = l[4] * r[0] + l[5] * r[2] + l[6] * r[4] + l[7] * r[6];             \
    d[3] = l[4] * r[1] + l[5] * r[3] + l[6] * r[5] + l[7] * r[7];             \
  } while (0)

#define mkRawMatrixMult4x3x4(l, r, d)                                         \
  do {                                                                        \
    d[0]  = l[0]  * r[0] + l[1]  * r[4] + l[2]  * r[8];                       \
    d[1]  = l[0]  * r[1] + l[1]  * r[5] + l[2]  * r[9];                       \
    d[2]  = l[0]  * r[2] + l[1]  * r[6] + l[2]  * r[10];                      \
    d[3]  = l[0]  * r[3] + l[1]  * r[7] + l[2]  * r[11];                      \
    d[4]  = l[4]  * r[0] + l[5]  * r[4] + l[6]  * r[8];                       \
    d[5]  = l[4]  * r[1] + l[5]  * r[5] + l[6]  * r[9];                       \
    d[6]  = l[4]  * r[2] + l[5]  * r[6] + l[6]  * r[10];                      \
    d[7]  = l[4]  * r[3] + l[5]  * r[7] + l[6]  * r[11];                      \
    d[8]  = l[8]  * r[0] + l[9]  * r[4] + l[10] * r[8];                       \
    d[9]  = l[8]  * r[1] + l[9]  * r[5] + l[10] * r[9];                       \
    d[10] = l[8]  * r[2] + l[9]  * r[6] + l[10] * r[10];                      \
    d[11] = l[8]  * r[3] + l[9]  * r[7] + l[10] * r[11];                      \
    d[12] = l[12] * r[0] + l[13] * r[4] + l[14] * r[8];                       \
    d[13] = l[12] * r[1] + l[13] * r[5] + l[14] * r[9];                       \
    d[14] = l[12] * r[2] + l[13] * r[6] + l[14] * r[10];                      \
    d[15] = l[12] * r[3] + l[13] * r[7] + l[14] * r[11];                      \
  } while (0)

#define mkRawMatrixMult4x3x3(l, r, d)                                         \
  do {                                                                        \
    d[0]  = l[0]  * r[0] + l[1]  * r[3] + l[2]  * r[6];                       \
    d[1]  = l[0]  * r[1] + l[1]  * r[4] + l[2]  * r[7];                       \
    d[2]  = l[0]  * r[2] + l[1]  * r[5] + l[2]  * r[8];                       \
    d[3]  = l[4]  * r[0] + l[5]  * r[3] + l[6]  * r[6];                       \
    d[4]  = l[4]  * r[1] + l[5]  * r[4] + l[6]  * r[7];                       \
    d[5]  = l[4]  * r[2] + l[5]  * r[5] + l[6]  * r[8];                       \
    d[6]  = l[8]  * r[0] + l[9]  * r[3] + l[10] * r[6];                       \
    d[7]  = l[8]  * r[1] + l[9]  * r[4] + l[10] * r[7];                       \
    d[8]  = l[8]  * r[2] + l[9]  * r[5] + l[10] * r[8];                       \
    d[9]  = l[12] * r[0] + l[13] * r[3] + l[14] * r[6];                       \
    d[10] = l[12] * r[1] + l[13] * r[4] + l[14] * r[7];                       \
    d[11] = l[12] * r[2] + l[13] * r[5] + l[14] * r[8];                       \
  } while (0)
    
#define mkRawMatrixMult4x3x2(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0]  * r[0] + l[1]  * r[2] + l[2]  * r[4];                        \
    d[1] = l[0]  * r[1] + l[1]  * r[3] + l[2]  * r[5];                        \
    d[2] = l[4]  * r[0] + l[5]  * r[2] + l[6]  * r[4];                        \
    d[3] = l[4]  * r[1] + l[5]  * r[3] + l[6]  * r[5];                        \
    d[4] = l[8]  * r[0] + l[8]  * r[2] + l[9]  * r[4];                        \
    d[5] = l[8]  * r[1] + l[8]  * r[3] + l[9]  * r[5];                        \
    d[6] = l[12] * r[0] + l[13] * r[2] + l[14] * r[4];                        \
    d[7] = l[12] * r[1] + l[13] * r[3] + l[14] * r[5];                        \
  } while (0)

#define mkRawMatrixMult3x3x4(l, r, d)                                         \
  do {                                                                        \
    d[0]  = l[0] * r[0] + l[1] * r[4] + l[2]  * r[8];                         \
    d[1]  = l[0] * r[1] + l[1] * r[5] + l[2]  * r[9];                         \
    d[2]  = l[0] * r[2] + l[1] * r[6] + l[2]  * r[10];                        \
    d[3]  = l[0] * r[3] + l[1] * r[7] + l[2]  * r[11];                        \
    d[4]  = l[4] * r[0] + l[5] * r[4] + l[6]  * r[8];                         \
    d[5]  = l[4] * r[1] + l[5] * r[5] + l[6]  * r[9];                         \
    d[6]  = l[4] * r[2] + l[5] * r[6] + l[6]  * r[10];                        \
    d[7]  = l[4] * r[3] + l[5] * r[7] + l[6]  * r[11];                        \
    d[8]  = l[8] * r[0] + l[9] * r[4] + l[10] * r[8];                         \
    d[9]  = l[8] * r[1] + l[9] * r[5] + l[10] * r[9];                         \
    d[10] = l[8] * r[2] + l[9] * r[6] + l[10] * r[10];                        \
    d[11] = l[8] * r[3] + l[9] * r[7] + l[10] * r[11];                        \
  } while (0)

#define mkRawMatrixMult3x3x3(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0] * r[0] + l[1] * r[3] + l[2]  * r[6];                          \
    d[1] = l[0] * r[1] + l[1] * r[4] + l[2]  * r[7];                          \
    d[2] = l[0] * r[2] + l[1] * r[5] + l[2]  * r[8];                          \
    d[3] = l[4] * r[0] + l[5] * r[3] + l[6]  * r[6];                          \
    d[4] = l[4] * r[1] + l[5] * r[4] + l[6]  * r[7];                          \
    d[5] = l[4] * r[2] + l[5] * r[5] + l[6]  * r[8];                          \
    d[6] = l[8] * r[0] + l[9] * r[3] + l[10] * r[6];                          \
    d[7] = l[8] * r[1] + l[9] * r[4] + l[10] * r[7];                          \
    d[8] = l[8] * r[2] + l[9] * r[5] + l[10] * r[8];                          \
  } while (0)
    
#define mkRawMatrixMult3x3x2(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0] * r[0] + l[1] * r[2] + l[2] * r[4];                           \
    d[1] = l[0] * r[1] + l[1] * r[3] + l[2] * r[5];                           \
    d[2] = l[4] * r[0] + l[5] * r[2] + l[6] * r[4];                           \
    d[3] = l[4] * r[1] + l[5] * r[3] + l[6] * r[5];                           \
    d[4] = l[8] * r[0] + l[8] * r[2] + l[9] * r[4];                           \
    d[5] = l[8] * r[1] + l[8] * r[3] + l[9] * r[5];                           \
  } while (0)
    
#define mkRawMatrixMult2x3x4(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0] * r[0] + l[1] * r[4] + l[2] * r[8];                           \
    d[1] = l[0] * r[1] + l[1] * r[5] + l[2] * r[9];                           \
    d[2] = l[0] * r[2] + l[1] * r[6] + l[2] * r[10];                          \
    d[3] = l[0] * r[3] + l[1] * r[7] + l[2] * r[11];                          \
    d[4] = l[4] * r[0] + l[5] * r[4] + l[6] * r[8];                           \
    d[5] = l[4] * r[1] + l[5] * r[5] + l[6] * r[9];                           \
    d[6] = l[4] * r[2] + l[5] * r[6] + l[6] * r[10];                          \
    d[7] = l[4] * r[3] + l[5] * r[7] + l[6] * r[11];                          \
  } while (0)
    
#define mkRawMatrixMult2x3x3(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0] * r[0] + l[1] * r[3] + l[2] * r[6];                           \
    d[1] = l[0] * r[1] + l[1] * r[4] + l[2] * r[7];                           \
    d[2] = l[0] * r[2] + l[1] * r[5] + l[2] * r[8];                           \
    d[3] = l[4] * r[0] + l[5] * r[3] + l[6] * r[6];                           \
    d[4] = l[4] * r[1] + l[5] * r[4] + l[6] * r[7];                           \
    d[5] = l[4] * r[2] + l[5] * r[5] + l[6] * r[8];                           \
  } while (0)
    
#define mkRawMatrixMult2x3x2(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0] * r[0] + l[1] * r[2] + l[2] * r[4];                           \
    d[1] = l[0] * r[1] + l[1] * r[3] + l[2] * r[5];                           \
    d[2] = l[4] * r[0] + l[5] * r[2] + l[6] * r[4];                           \
    d[3] = l[4] * r[1] + l[5] * r[3] + l[6] * r[5];                           \
  } while (0)
    
#define mkRawMatrixMult4x2x4(l, r, d)                                         \
  do {                                                                        \
    d[0]  = l[0]  * r[0] + l[1]  * r[4];                                      \
    d[1]  = l[0]  * r[1] + l[1]  * r[5];                                      \
    d[2]  = l[0]  * r[2] + l[1]  * r[6];                                      \
    d[3]  = l[0]  * r[3] + l[1]  * r[7];                                      \
    d[4]  = l[4]  * r[0] + l[5]  * r[4];                                      \
    d[5]  = l[4]  * r[1] + l[5]  * r[5];                                      \
    d[6]  = l[4]  * r[2] + l[5]  * r[6];                                      \
    d[7]  = l[4]  * r[3] + l[5]  * r[7];                                      \
    d[8]  = l[8]  * r[0] + l[9]  * r[4];                                      \
    d[9]  = l[8]  * r[1] + l[9]  * r[5];                                      \
    d[10] = l[8]  * r[2] + l[9]  * r[6];                                      \
    d[11] = l[8]  * r[3] + l[9]  * r[7];                                      \
    d[12] = l[12] * r[0] + l[13] * r[4];                                      \
    d[13] = l[12] * r[1] + l[13] * r[5];                                      \
    d[14] = l[12] * r[2] + l[13] * r[6];                                      \
    d[15] = l[12] * r[3] + l[13] * r[7];                                      \
  } while (0)
    
#define mkRawMatrixMult4x2x3(l, r, d)                                         \
  do {                                                                        \
    d[0]  = l[0]  * r[0] + l[1]  * r[3];                                      \
    d[1]  = l[0]  * r[1] + l[1]  * r[4];                                      \
    d[2]  = l[0]  * r[2] + l[1]  * r[5];                                      \
    d[3]  = l[4]  * r[0] + l[5]  * r[3];                                      \
    d[4]  = l[4]  * r[1] + l[5]  * r[4];                                      \
    d[5]  = l[4]  * r[2] + l[5]  * r[5];                                      \
    d[6]  = l[8]  * r[0] + l[9]  * r[3];                                      \
    d[7]  = l[8]  * r[1] + l[9]  * r[4];                                      \
    d[8]  = l[8]  * r[2] + l[9]  * r[5];                                      \
    d[9]  = l[12] * r[0] + l[13] * r[3];                                      \
    d[10] = l[12] * r[1] + l[13] * r[4];                                      \
    d[11] = l[12] * r[2] + l[13] * r[5];                                      \
  } while (0)
    
#define mkRawMatrixMult4x2x2(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0]  * r[0] + l[1]  * r[2];                                       \
    d[1] = l[0]  * r[1] + l[1]  * r[3];                                       \
    d[2] = l[4]  * r[0] + l[5]  * r[2];                                       \
    d[3] = l[4]  * r[1] + l[5]  * r[3];                                       \
    d[4] = l[8]  * r[0] + l[8]  * r[2];                                       \
    d[5] = l[8]  * r[1] + l[8]  * r[3];                                       \
    d[6] = l[12] * r[0] + l[13] * r[2];                                       \
    d[7] = l[12] * r[1] + l[13] * r[3];                                       \
  } while (0)
    
#define mkRawMatrixMult3x2x4(l, r, d)                                         \
  do {                                                                        \
    d[0]  = l[0] * r[0] + l[1] * r[4];                                        \
    d[1]  = l[0] * r[1] + l[1] * r[5];                                        \
    d[2]  = l[0] * r[2] + l[1] * r[6];                                        \
    d[3]  = l[0] * r[3] + l[1] * r[7];                                        \
    d[4]  = l[4] * r[0] + l[5] * r[4];                                        \
    d[5]  = l[4] * r[1] + l[5] * r[5];                                        \
    d[6]  = l[4] * r[2] + l[5] * r[6];                                        \
    d[7]  = l[4] * r[3] + l[5] * r[7];                                        \
    d[8]  = l[8] * r[0] + l[9] * r[4];                                        \
    d[9]  = l[8] * r[1] + l[9] * r[5];                                        \
    d[10] = l[8] * r[2] + l[9] * r[6];                                        \
    d[11] = l[8] * r[3] + l[9] * r[7];                                        \
  } while (0)
    
    
#define mkRawMatrixMult3x2x3(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0] * r[0] + l[1] * r[3];                                         \
    d[1] = l[0] * r[1] + l[1] * r[4];                                         \
    d[2] = l[0] * r[2] + l[1] * r[5];                                         \
    d[3] = l[4] * r[0] + l[5] * r[3];                                         \
    d[4] = l[4] * r[1] + l[5] * r[4];                                         \
    d[5] = l[4] * r[2] + l[5] * r[5];                                         \
    d[6] = l[8] * r[0] + l[9] * r[3];                                         \
    d[7] = l[8] * r[1] + l[9] * r[4];                                         \
    d[8] = l[8] * r[2] + l[9] * r[5];                                         \
  } while (0)
    
#define mkRawMatrixMult3x2x2(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0] * r[0] + l[1] * r[2];                                         \
    d[1] = l[0] * r[1] + l[1] * r[3];                                         \
    d[2] = l[4] * r[0] + l[5] * r[2];                                         \
    d[3] = l[4] * r[1] + l[5] * r[3];                                         \
    d[4] = l[8] * r[0] + l[8] * r[2];                                         \
    d[5] = l[8] * r[1] + l[8] * r[3];                                         \
  } while (0)
    
#define mkRawMatrixMult2x2x4(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0] * r[0] + l[1] * r[4];                                         \
    d[1] = l[0] * r[1] + l[1] * r[5];                                         \
    d[2] = l[0] * r[2] + l[1] * r[6];                                         \
    d[3] = l[0] * r[3] + l[1] * r[7];                                         \
    d[4] = l[4] * r[0] + l[5] * r[4];                                         \
    d[5] = l[4] * r[1] + l[5] * r[5];                                         \
    d[6] = l[4] * r[2] + l[5] * r[6];                                         \
    d[7] = l[4] * r[3] + l[5] * r[7];                                         \
  } while (0)
    
#define mkRawMatrixMult2x2x3(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0] * r[0] + l[1] * r[3];                                         \
    d[1] = l[0] * r[1] + l[1] * r[4];                                         \
    d[2] = l[0] * r[2] + l[1] * r[5];                                         \
    d[3] = l[4] * r[0] + l[5] * r[3];                                         \
    d[4] = l[4] * r[1] + l[5] * r[4];                                         \
    d[5] = l[4] * r[2] + l[5] * r[5];                                         \
  } while (0)
    
#define mkRawMatrixMult2x2x2(l, r, d)                                         \
  do {                                                                        \
    d[0] = l[0] * r[0] + l[1] * r[2];                                         \
    d[1] = l[0] * r[1] + l[1] * r[3];                                         \
    d[2] = l[4] * r[0] + l[5] * r[2];                                         \
    d[3] = l[4] * r[1] + l[5] * r[3];                                         \
  } while (0)

#define mkRawMatrixScalar4x4(m, val, op)                                      \
  do {                                                                        \
    m[0]  op val; m[1]  op val; m[2]  op val; m[3]  op val;                   \
    m[4]  op val; m[5]  op val; m[6]  op val; m[7]  op val;                   \
    m[8]  op val; m[9]  op val; m[10] op val; m[11] op val;                   \
    m[12] op val; m[13] op val; m[14] op val; m[15] op val;                   \
  } while (0)

#define mkRawMatrixScalar3x4(m, val, op) mkRawMatrixScalar4x3(m, val, op)
#define mkRawMatrixScalar4x3(m, val, op)                                      \
  do {                                                                        \
    m[0]  op val; m[1]  op val; m[2]  op val; m[3]  op val;                   \
    m[4]  op val; m[5]  op val; m[6]  op val; m[7]  op val;                   \
    m[8]  op val; m[9]  op val; m[10] op val; m[11] op val;                   \
  } while (0)

#define mkRawMatrixScalar2x4(m, val, op) mkRawMatrixScalar4x2(m, val, op)
#define mkRawMatrixScalar4x2(m, val, op)                                      \
  do {                                                                        \
    m[0] op val; m[1] op val; m[2] op val; m[3] op val;                       \
    m[4] op val; m[5] op val; m[6] op val; m[7] op val;                       \
  } while (0)

#define mkRawMatrixScalar3x3(m, val, op)                                      \
  do {                                                                        \
    m[0] op val; m[1] op val; m[2] op val; m[3] op val;                       \
    m[4] op val; m[5] op val; m[6] op val; m[7] op val; m[8] op val;          \
  } while (0)

#define mkRawMatrixScalar2x3(m, val, op) mkRawMatrixScalar3x2(m, val, op)
#define mkRawMatrixScalar3x2(m, val, op)                                      \
  do {                                                                        \
    m[0] op val; m[1] op val; m[2] op val;                                    \
    m[3] op val; m[4] op val; m[5] op val;                                    \
  } while (0)

#define mkRawMatrixScalar2x2(m, val, op)                                      \
  do {                                                                        \
    m[0] op val; m[1] op val; m[2] op val; m[3] op val;                       \
  } while (0)

#define MK__rawMatrixScT(R0, C0, op, T)                                       \
  do {                                                                        \
    T * __restrict d;                                                         \
    T val_;                                                                   \
                                                                              \
    d    = (T *)m;                                                            \
    val_ = *(T *)val;                                                         \
                                                                              \
    mkRawMatrixScalar ## R0 ## x ## C0(d, val_, op);                          \
  } while (0)

#define MK__rawMatrixSc(R0, C0, op)                                           \
   switch (lay.type) {                                                        \
      case MK_FLOAT:  MK__rawMatrixScT(R0, C0, op, float);   break;           \
      case MK_DOUBLE: MK__rawMatrixScT(R0, C0, op, double);  break;           \
      case MK_INT32:  MK__rawMatrixScT(R0, C0, op, int32_t); break;           \
      case MK_INT64:  MK__rawMatrixScT(R0, C0, op, int64_t); break;           \
   }

#define MK__rawMatrixScImpl(op)                                               \
   switch (lay.count[1]) {                                                    \
      case 4:                                                                 \
         switch (lay.count[1]) {                                              \
            case 4: MK__rawMatrixSc(4, 4, op); break;                         \
            case 3: MK__rawMatrixSc(4, 3, op); break;                         \
            case 2: MK__rawMatrixSc(4, 2, op); break;                         \
         } break;                                                             \
      case 3:                                                                 \
         switch (lay.count[1]) {                                              \
            case 4: MK__rawMatrixSc(3, 4, op); break;                         \
            case 3: MK__rawMatrixSc(3, 3, op); break;                         \
            case 2: MK__rawMatrixSc(3, 2, op); break;                         \
         } break;                                                             \
      case 2:                                                                 \
         switch (lay.count[1]) {                                              \
            case 4: MK__rawMatrixSc(2, 4, op); break;                         \
            case 3: MK__rawMatrixSc(2, 3, op); break;                         \
            case 2: MK__rawMatrixSc(2, 2, op); break;                         \
         } break;                                                             \
   }

#define mkRawMatrixTranspose4x4(m, d)                                         \
  do {                                                                        \
    d[0]  = m[0]; d[1]  = m[4]; d[2]  = m[8];  d[3]  = m[12];                 \
    d[4]  = m[1]; d[5]  = m[5]; d[6]  = m[9];  d[7]  = m[13];                 \
    d[8]  = m[2]; d[9]  = m[6]; d[10] = m[10]; d[11] = m[14];                 \
    d[12] = m[3]; d[13] = m[7]; d[14] = m[11]; d[15] = m[15];                 \
  } while (0)

#define mkRawMatrixTranspose4x3(m, d)                                         \
  do {                                                                        \
    d[0] = m[0]; d[1] = m[3]; d[2]  = m[6]; d[3]  = m[9];                     \
    d[4] = m[1]; d[5] = m[4]; d[6]  = m[7]; d[7]  = m[10];                    \
    d[8] = m[2]; d[9] = m[5]; d[10] = m[8]; d[11] = m[11];                    \
  } while (0)

#define mkRawMatrixTranspose4x2(m, d)                                         \
  do {                                                                        \
    d[0] = m[0]; d[1] = m[2]; d[2] = m[4]; d[3] = m[6];                       \
    d[4] = m[1]; d[5] = m[3]; d[6] = m[5]; d[7] = m[7];                       \
  } while (0)

#define mkRawMatrixTranspose3x4(m, d)                                         \
  do {                                                                        \
    d[0] = m[0]; d[1]  = m[4]; d[2]  = m[8];                                  \
    d[3] = m[1]; d[4]  = m[5]; d[5]  = m[9];                                  \
    d[6] = m[2]; d[7]  = m[6]; d[8]  = m[10];                                 \
    d[9] = m[3]; d[10] = m[7]; d[11] = m[11];                                 \
  } while (0)

#define mkRawMatrixTranspose3x3(m, d)                                         \
  do {                                                                        \
    d[0] = m[0]; d[1] = m[3]; d[2] = m[6];                                    \
    d[3] = m[1]; d[4] = m[4]; d[5] = m[7];                                    \
    d[6] = m[2]; d[7] = m[5]; d[8] = m[8];                                    \
  } while (0)

#define mkRawMatrixTranspose3x2(m, d)                                         \
  do {                                                                        \
    d[0] = m[0]; d[1] = m[2]; d[2] = m[4];                                    \
    d[3] = m[1]; d[4] = m[3]; d[5] = m[5];                                    \
  } while (0)

#define mkRawMatrixTranspose2x4(m, d)                                         \
  do {                                                                        \
    d[0] = m[0]; d[1] = m[4];                                                 \
    d[2] = m[1]; d[3] = m[5];                                                 \
    d[4] = m[2]; d[5] = m[6];                                                 \
    d[6] = m[3]; d[7] = m[7];                                                 \
  } while (0)

#define mkRawMatrixTranspose2x3(m, d)                                         \
  do {                                                                        \
    d[0] = m[0]; d[1] = m[3];                                                 \
    d[2] = m[1]; d[3] = m[4];                                                 \
    d[4] = m[2]; d[5] = m[5];                                                 \
  } while (0)

#define mkRawMatrixTranspose2x2(m, d)                                         \
  do {                                                                        \
    d[0] = m[0]; d[1] = m[2];                                                 \
    d[2] = m[1]; d[3] = m[3];                                                 \
  } while (0)

MK_INLINE
void
mkRawMatrixAdd(void * __restrict m,
               void * __restrict val,
               const MkBufLayout lay) {
  MK__rawMatrixScImpl(+=);
}

MK_INLINE
void
mkRawMatrixSub(void * __restrict m,
               void * __restrict val,
               const MkBufLayout lay) {
  MK__rawMatrixScImpl(-=);
}

MK_INLINE
void
mkRawMatrixScale(void * __restrict m,
                 void * __restrict val,
                 const MkBufLayout lay) {
  MK__rawMatrixScImpl(*=);
}

MK_INLINE
void
mkRawMatrixMult(void * __restrict mL,
                void * __restrict mR,
                void * __restrict mDest,
                const MkBufLayout lay[2]) {
   /* step 5: call mult macro */
#define MK__rawMatrixMulT(R0, C0, C1, T)                                      \
  do {                                                                        \
    T * __restrict l;                                                         \
    T * __restrict r;                                                         \
    T * __restrict d;                                                         \
                                                                              \
    l = (T *)mL;                                                              \
    r = (T *)mR;                                                              \
    d = (T *)mDest;                                                           \
                                                                              \
    mkRawMatrixMult ## R0 ## x ## C0 ## x ## C1(l, r, d);                     \
  } while (0)

   /* step 4: select macro by type */
#define MK__rawMatrixMulC(R0, C0, C1)                                         \
   switch (lay[0].type) {                                                     \
      case MK_FLOAT:  MK__rawMatrixMulT(R0, C0, C1, float);   break;          \
      case MK_DOUBLE: MK__rawMatrixMulT(R0, C0, C1, double);  break;          \
      case MK_INT32:  MK__rawMatrixMulT(R0, C0, C1, int32_t); break;          \
      case MK_INT64:  MK__rawMatrixMulT(R0, C0, C1, int64_t); break;          \
   }

   /* step 3: select macro by column R (mR's column) */
#define MK__rawMatrixMulByColR(a, b)                                          \
   switch (lay[1].count[1]) {                                                 \
      case 4: MK__rawMatrixMulC(a, b, 4); break;                              \
      case 3: MK__rawMatrixMulC(a, b, 3); break;                              \
      case 2: MK__rawMatrixMulC(a, b, 2); break;                              \
   }

   /* step 2: select macro by row L (mL's row) */
#define MK__rawMatrixMulByRowL(a)                                             \
   switch (lay[0].count[0]) {                                                 \
      case 4: MK__rawMatrixMulByColR(4, a); break;                            \
      case 3: MK__rawMatrixMulByColR(3, a); break;                            \
      case 2: MK__rawMatrixMulByColR(2, a); break;                            \
   }

   /* step 1: select macro by column L | row R */
   switch (lay[0].count[1]) {
      case 4: MK__rawMatrixMulByRowL(4); break;
      case 3: MK__rawMatrixMulByRowL(3); break;
      case 2: MK__rawMatrixMulByRowL(2); break;
   }

#undef MK__rawMatrixMulC
#undef MK__rawMatrixMulByColR
#undef MK__rawMatrixMulByRowL
#undef MK__rawMatrixScT
#undef MK__rawMatrixSc
#undef MK__rawMatrixScImpl
#undef MK__rawMatrixMul
#undef MK__rawMatrixMulT
}

MK_INLINE
void
mkRawMatrixTranspose(void * __restrict m,
                     void * __restrict d,
                     const MkBufLayout lay) {
#define MK__rawMatrixTransT(R0, C0, T)                                        \
  do {                                                                        \
    T * __restrict s;                                                         \
    T * __restrict t;                                                         \
                                                                              \
    s = (T *)m;                                                               \
    t = (T *)d;                                                               \
                                                                              \
    mkRawMatrixTranspose ## R0 ## x ## C0(s, t);                              \
  } while (0)

#define MK__rawMatrixTrans(R0, C0)                                            \
   switch (lay.type) {                                                        \
      case MK_FLOAT:  MK__rawMatrixTransT(R0, C0, float);   break;            \
      case MK_DOUBLE: MK__rawMatrixTransT(R0, C0, double);  break;            \
      case MK_INT32:  MK__rawMatrixTransT(R0, C0, int32_t); break;            \
      case MK_INT64:  MK__rawMatrixTransT(R0, C0, int64_t); break;            \
   }

   switch (lay.count[1]) {
      case 4:
         switch (lay.count[1]) {
            case 4: MK__rawMatrixTrans(4, 4); break;
            case 3: MK__rawMatrixTrans(4, 3); break;
            case 2: MK__rawMatrixTrans(4, 2); break;
         } break;
      case 3:
         switch (lay.count[1]) {
            case 4: MK__rawMatrixTrans(3, 4); break;
            case 3: MK__rawMatrixTrans(3, 3); break;
            case 2: MK__rawMatrixTrans(3, 2); break;
         } break;
      case 2:
         switch (lay.count[1]) {
            case 4: MK__rawMatrixTrans(2, 4); break;
            case 3: MK__rawMatrixTrans(2, 3); break;
            case 2: MK__rawMatrixTrans(2, 2); break;
         } break;
   }

#undef MK__rawMatrixTrans
#undef MK__rawMatrixTransT
}

#ifdef __cplusplus
}
#endif
#endif /* mk_matrix_impl_mat_raw_h */
