/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mk_matrix_impl_mat_h
#define mk_matrix_impl_mat_h
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>

#include "../mk-common.h"
#include "../mk-vector.h"
#include "mki-matrix-raw.h"

#define MK__MAT_TMPL_TRANSPOSE(MK__TYPE)                                      \
  {                                                                           \
     MK__TYPE *posA;                                                          \
     MK__TYPE *posB;                                                          \
     size_t i;                                                                \
     size_t j;                                                                \
     size_t n;                                                                \
     size_t m;                                                                \
     size_t colMaxOff;                                                        \
     int    bufindex;                                                         \
                                                                              \
     if (!lay.runtime) {                                                      \
       m = lay.count[0];                                                      \
       n = lay.count[1];                                                      \
     } else {                                                                 \
       m = matrix->rows;                                                      \
       n = matrix->cols;                                                      \
     }                                                                        \
                                                                              \
     posA      = (MK__TYPE *)bufs[0];                                         \
     posB      = (MK__TYPE *)bufs[1];                                         \
     colMaxOff = n * n;                                                       \
                                                                              \
     for (i = 0; i < m; i++)                                                  \
        for (j = 0; j < colMaxOff; j += n)                                    \
           *(posB + j + i) = *posA++;                                         \
                                                                              \
      bufindex           = !matrix->bufindex;                                 \
      matrix->bufindex   = bufindex;                                          \
      matrix->value = bufs[bufindex];                                         \
  }

#define MK__MAT_TMPL_TRANSPOSE_TO(MK__TYPE)                                   \
  {                                                                           \
     MK__TYPE *posA;                                                          \
     MK__TYPE *posB;                                                          \
     size_t i;                                                                \
     size_t j;                                                                \
     size_t n;                                                                \
     size_t m;                                                                \
     size_t colMaxOff;                                                        \
                                                                              \
     if (!lay.runtime) {                                                      \
       m = lay.count[0];                                                      \
       n = lay.count[1];                                                      \
     } else {                                                                 \
       m = matrix->rows;                                                      \
       n = matrix->cols;                                                      \
     }                                                                        \
                                                                              \
     posA      = (MK__TYPE *)matrix->value;                                   \
     posB      = (MK__TYPE *)dest;                                            \
     colMaxOff = n * n;                                                       \
                                                                              \
     for (i = 0; i < m; i++)                                                  \
        for (j = 0; j < colMaxOff; j += n)                                    \
           *(posB + j + i) = *posA++;                                         \
  }

MK_INLINE
void
mkMatrixTranspose(MkMatrix * __restrict matrix,
                  void * __restrict bufs[2],
                  const MkBufLayout lay) {
   switch (lay.type) {
      case MK_FLOAT:  MK__MAT_TMPL_TRANSPOSE(float)   break;
      case MK_DOUBLE: MK__MAT_TMPL_TRANSPOSE(double)  break;
      case MK_INT32:  MK__MAT_TMPL_TRANSPOSE(int32_t) break;
      case MK_INT64:  MK__MAT_TMPL_TRANSPOSE(int64_t) break;
   }
}

MK_INLINE
void
mkMatrixTransposeTo(MkMatrix * __restrict matrix,
                    void * __restrict dest,
                    const MkBufLayout lay) {
   switch (lay.type) {
      case MK_FLOAT:  MK__MAT_TMPL_TRANSPOSE_TO(float)   break;
      case MK_DOUBLE: MK__MAT_TMPL_TRANSPOSE_TO(double)  break;
      case MK_INT32:  MK__MAT_TMPL_TRANSPOSE_TO(int32_t) break;
      case MK_INT64:  MK__MAT_TMPL_TRANSPOSE_TO(int64_t) break;
   }
}

#define mk_mmultl(MK__M, MK__ML, MK__BUFS, MK__LAY)                           \
   mkMatrixMatrixMultL(MK__M, MK__ML, MK__BUFS, MK__LAY)

#define mkMatrixMatrixMultL_impl(T)                                           \
  do {                                                                        \
   T     *pL;                                                                 \
   T     *pR;                                                                 \
   T     *pD;                                                                 \
   T      tmpSum;                                                             \
   size_t rowsL;                                                              \
   size_t colsR;                                                              \
   size_t colsL;                                                              \
   size_t i;                                                                  \
   size_t j;                                                                  \
   size_t iR;                                                                 \
   int    bufindex;                                                           \
                                                                              \
   bufindex = matrix->bufindex;                                               \
                                                                              \
   pL = (T *)bufs[bufindex];                                                  \
   pD = (T *)bufs[!bufindex];                                                 \
   pR = (T *)bufs[2];                                                         \
                                                                              \
   /* max allowed size is 4x4 for manual computation */                       \
   if (mk_builtin_expect(!lay[0].runtime                                      \
                         && lay[0].count[0] < 5                               \
                         && lay[0].count[1] < 5                               \
                         && lay[1].count[0] < 5                               \
                         && lay[1].count[1] < 5, 1)) {                        \
                                                                              \
      mkRawMatrixMult(pL, pR, pD, lay);                                       \
   } else {                                                                   \
      if (lay[0].runtime) {                                                   \
         rowsL = matrixL->rows;                                               \
         colsL = matrixL->cols;                                               \
         colsR = matrix->cols;                                                \
      } else {                                                                \
         rowsL = lay[0].count[0];                                             \
         colsL = lay[0].count[1];                                             \
         colsR = lay[0].count[1];                                             \
      }                                                                       \
                                                                              \
      for (i = 0; i < rowsL; i++)                                             \
         for (j = 0; j < colsR; j++) {                                        \
            tmpSum = 0;                                                       \
            for (iR = 0; iR < colsL; iR ++)                                   \
               tmpSum += *(pL + i * colsR + iR) * *(pR + iR * colsR + j);     \
                                                                              \
            *pD++ = tmpSum;                                                   \
         }                                                                    \
   }                                                                          \
                                                                              \
   matrix->bufindex = !bufindex;                                              \
   matrix->value    = bufs[!bufindex];                                        \
                                                                              \
   if (bufs[bufindex] == bufs[2])                                             \
      bufs[2] = bufs[!bufindex];                                              \
  } while (0)

MK_INLINE
void
mkMatrixMatrixMultL(MkMatrix * __restrict matrix,
                    MkMatrix * __restrict matrixL,
                    void * __restrict bufs[3],
                    const MkBufLayout lay[2]) {
   switch (lay[0].type) {
      case MK_FLOAT:  mkMatrixMatrixMultL_impl(float);   break;
      case MK_DOUBLE: mkMatrixMatrixMultL_impl(double);  break;
      case MK_INT32:  mkMatrixMatrixMultL_impl(int32_t); break;
      case MK_INT64:  mkMatrixMatrixMultL_impl(int64_t); break;
   }
}

#ifdef __cplusplus
}
#endif
#endif /* mk_matrix_impl_mat_h */
