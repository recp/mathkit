/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mk_matrix_impl_mat_h
#define mk_matrix_impl_mat_h

#include <stdlib.h>
#include <stdbool.h>

#include "../mk-common.h"
#include "../mk-vector.h"
#include "mk-matrix-impl-mat-raw.h"

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

inline
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

inline
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

__attribute((always_inline))
inline
void
mkMatrixMatrixMultL(MkMatrix * __restrict matrix,
                    MkMatrix * __restrict matrixL,
                    void * __restrict bufs[3],
                    const MkBufLayout lay[2]) {
   switch (lay[0].type) {
      case MK_FLOAT: {
         float  *posA;
         float  *posB;
         float  *posC;
         float  tmpSum;
         size_t rowsL;
         size_t colsR;
         size_t colsL;
         size_t i;
         size_t j;
         size_t iR;
         int    bufindex;

         bufindex = matrix->bufindex;

         posA = (float *)bufs[bufindex];
         posC = (float *)bufs[!bufindex];
         posB = (float *)bufs[2];

         if (!lay[0].runtime) {
            mkRawMatrixMult((float *)posA,
                            (float *)posB,
                            (float *)posC,
                            lay);
         } else {
            rowsL = matrixL->rows;
            colsL = matrixL->cols;
            colsR = matrix->cols;

            for (i = 0; i < rowsL; i++)
               for (j = 0; j < colsR; j++) {
                  for (tmpSum = iR = 0; iR < colsL; iR ++)
                     tmpSum += *(posA + i * colsR + iR)
                                   * *(posB + iR * colsR + j);

                  *posC++ = tmpSum;
               }
         }

         matrix->bufindex = !bufindex;
         matrix->value    = bufs[!bufindex];

         if (bufs[bufindex] == bufs[2])
            bufs[2] = bufs[!bufindex];

         break;
      }
   }
}

#endif /* mk_matrix_impl_mat_h */
