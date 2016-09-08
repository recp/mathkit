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
#include "../mk-mem.h"
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
     if (!hint.runtime) {                                                     \
       m = hint.count[0];                                                     \
       n = hint.count[1];                                                     \
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
     if (!hint.runtime) {                                                     \
       m = hint.count[0];                                                     \
       n = hint.count[1];                                                     \
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
                  const MkHint hint) {
   switch (hint.type) {
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
                    const MkHint hint) {
   switch (hint.type) {
      case MK_FLOAT:  MK__MAT_TMPL_TRANSPOSE_TO(float)   break;
      case MK_DOUBLE: MK__MAT_TMPL_TRANSPOSE_TO(double)  break;
      case MK_INT32:  MK__MAT_TMPL_TRANSPOSE_TO(int32_t) break;
      case MK_INT64:  MK__MAT_TMPL_TRANSPOSE_TO(int64_t) break;
   }
}

#define mkMatrixMatrixMul_impl(T)                                             \
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
                                                                              \
   pL = (T *)matrixL->value;                                                  \
   pR = (T *)matrixR->value;                                                  \
   pD = (T *)dest->value;                                                     \
                                                                              \
   /* max allowed size is 4x4 for manual computation */                       \
   if (mk_builtin_expect(!hint[0].runtime                                     \
                         && hint[0].count[0] < 5                              \
                         && hint[0].count[1] < 5                              \
                         && hint[1].count[0] < 5                              \
                         && hint[1].count[1] < 5, 1)) {                       \
                                                                              \
      mkRawMatrixMult(pL, pR, pD, hint);                                      \
   } else {                                                                   \
      if (hint[0].runtime) {                                                  \
         rowsL = matrixL->rows;                                               \
         colsL = matrixL->cols;                                               \
         colsR = matrixR->cols;                                               \
      } else {                                                                \
         rowsL = hint[0].count[0];                                            \
         colsL = hint[0].count[1];                                            \
         colsR = hint[0].count[1];                                            \
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
  } while (0)

#define mkMatrixMatrixMulN_impl(T)                                            \
  do {                                                                        \
	  T *pL;                                                                    \
	  T *pR;                                                                    \
	  T *pD;                                                                    \
	  T *bufs[2];                                                               \
	  mkVLANew(T, matrices[0]->rows * matrices[len - 1]->cols);                 \
                                                                              \
	  bufs[0] = (T *)dest->value;                                               \
	  bufs[1] = tmp;                                                            \
                                                                              \
	  matrixR = matrices[--len];                                                \
	  pR = (T *)matrixR->value;                                                 \
                                                                              \
	  do {                                                                      \
	     matrixL = matrices[--len];                                             \
                                                                              \
	     pL = (T *)matrixL->value;                                              \
	     pD = bufs[bufidx];                                                     \
                                                                              \
	     /* max allowed size is 4x4 for manual computation */                   \
	     if (mk_builtin_expect(!hint[0].runtime                                 \
	                           && hint[0].count[0] < 5                          \
	                           && hint[0].count[1] < 5                          \
	                           && hint[1].count[0] < 5                          \
	                           && hint[1].count[1] < 5, 1)) {                   \
	        mkRawMatrixMult(pL, pR, pD, hint);                                  \
	     } else {                                                               \
	        T  tmpSum;                                                          \
	        size_t rowsL;                                                       \
	        size_t colsR;                                                       \
	        size_t colsL;                                                       \
	        size_t i;                                                           \
	        size_t j;                                                           \
	        size_t iR;                                                          \
                                                                              \
	        if (hint[0].runtime) {                                              \
	           rowsL = matrixL->rows;                                           \
	           colsL = matrixL->cols;                                           \
	           colsR = matrixR->cols;                                           \
	        } else {                                                            \
	           rowsL = hint[0].count[0];                                        \
	           colsL = hint[0].count[1];                                        \
	           colsR = hint[0].count[1];                                        \
	        }                                                                   \
                                                                              \
	        for (i = 0; i < rowsL; i++)                                         \
	           for (j = 0; j < colsR; j++) {                                    \
	              tmpSum = 0;                                                   \
	              for (iR = 0; iR < colsL; iR ++)                               \
	                 tmpSum += *(pL + i * colsR + iR) * *(pR + iR * colsR + j); \
                                                                              \
	              *pD++ = tmpSum;                                               \
	           }                                                                \
	     }                                                                      \
                                                                              \
	     pR     = pD;                                                           \
	     bufidx = !bufidx;                                                      \
	  } while (len);                                                            \
                                                                              \
	  if (!bufidx)                                                              \
	     mk__memcpy(dest->value, pR, sizeof(tmp));                              \
                                                                              \
    mkVLAFree(tmp);                                                           \
  } while (0)

MK_INLINE
void
mkMatrixMatrixMul(MkMatrix * __restrict matrixL,
                  MkMatrix * __restrict matrixR,
                  MkMatrix * __restrict dest,
                  const MkHint hint[2]) {
   switch (hint[0].type) {
      case MK_FLOAT:  mkMatrixMatrixMul_impl(float);   break;
      case MK_DOUBLE: mkMatrixMatrixMul_impl(double);  break;
      case MK_INT32:  mkMatrixMatrixMul_impl(int32_t); break;
      case MK_INT64:  mkMatrixMatrixMul_impl(int64_t); break;
   }
}

MK_INLINE
void
mkMatrixMatrixMulN(MkMatrix * __restrict matrices[],
                   MkMatrix * __restrict dest,
                   size_t len,
                   const MkHint hint[]) {
   MkMatrix *matrixL;
   MkMatrix *matrixR;
   int       bufidx;

   bufidx = 0;

   switch (hint[0].type) {
      case MK_FLOAT:  mkMatrixMatrixMulN_impl(float);   break;
      case MK_DOUBLE: mkMatrixMatrixMulN_impl(double);  break;
      case MK_INT32:  mkMatrixMatrixMulN_impl(int32_t); break;
      case MK_INT64:  mkMatrixMatrixMulN_impl(int64_t); break;
   }
}

#define mkMatrixFillIdentity_impl(T)                                          \
  do {                                                                        \
    T     *val;                                                               \
    size_t cols;                                                              \
    size_t rows;                                                              \
    int    i;                                                                 \
    int    j;                                                                 \
                                                                              \
    if (!hint.runtime) {                                                      \
      rows = hint.count[0];                                                   \
      cols = hint.count[1];                                                   \
    } else {                                                                  \
      rows = matrix->rows;                                                    \
      cols = matrix->cols;                                                    \
    }                                                                         \
                                                                              \
    val = matrix->value;                                                      \
    for (i = 0; i < rows; i++)                                                \
      for (j = 0; j < cols; j++)                                              \
        val[i * rows + j] = i == j;                                           \
  } while (0)

MK_INLINE
void
mkMatrixFillIdentity(MkMatrix * __restrict matrix,
                     const MkHint hint) {
   switch (hint.type) {
      case MK_FLOAT:  mkMatrixFillIdentity_impl(float);   break;
      case MK_DOUBLE: mkMatrixFillIdentity_impl(double);  break;
      case MK_INT32:  mkMatrixFillIdentity_impl(int32_t); break;
      case MK_INT64:  mkMatrixFillIdentity_impl(int64_t); break;
   }
}

#define mkMatrixIsIdentity_impl(T)                                            \
  do {                                                                        \
    T *pVal;                                                                  \
    T  tVal;                                                                  \
    size_t i;                                                                 \
    size_t j;                                                                 \
    size_t cols;                                                              \
    size_t rows;                                                              \
                                                                              \
    pVal = (T *)matrix->value;                                                \
                                                                              \
    if (!hint.runtime) {                                                      \
      rows = hint.count[0];                                                   \
      cols = hint.count[1];                                                   \
    } else {                                                                  \
      rows = matrix->rows;                                                    \
      cols = matrix->cols;                                                    \
    }                                                                         \
                                                                              \
    for (i = 0; i < rows; i++) {                                              \
      for (j = 0; j < cols; j++) {                                            \
         tVal = pVal[i * rows + j];                                           \
         if (i != j) {                                                        \
            if (tVal != 0)                                                    \
               goto ret;                                                      \
                                                                              \
            continue;                                                         \
         }                                                                    \
                                                                              \
         if (tVal != 1)                                                       \
            goto ret;                                                         \
      }                                                                       \
    }                                                                         \
  } while (0)

MK_INLINE
bool
mkMatrixIsIdentity(MkMatrix * matrix,
                   const MkHint hint) {
   bool isIdentity;

   isIdentity = false;

   switch (hint.type) {
      case MK_FLOAT:  mkMatrixIsIdentity_impl(float);   break;
      case MK_DOUBLE: mkMatrixIsIdentity_impl(double);  break;
      case MK_INT32:  mkMatrixIsIdentity_impl(int32_t); break;
      case MK_INT64:  mkMatrixIsIdentity_impl(int64_t); break;
   }

   isIdentity = true;

ret:
   return isIdentity;
}

#ifdef __cplusplus
}
#endif
#endif /* mk_matrix_impl_mat_h */
