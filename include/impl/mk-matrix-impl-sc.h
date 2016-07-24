/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mk_matrix_impl_sc_h
#define mk_matrix_impl_sc_h
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../mk-common.h"
#include "../mk-vector.h"

#define MK__MAT_TMPL_SCALAR(MK__OP, MK__TYPE)                                 \
   {                                                                          \
     MK__TYPE *itemPos;                                                       \
     MK__TYPE * __restrict itemPos_end;                                       \
     MK__TYPE  otherVal;                                                      \
                                                                              \
     otherVal    = *(MK__TYPE *)other;                                        \
     itemPos     = (MK__TYPE *)matrix->value;                                 \
     itemPos_end = itemPos + layout.count[0] * layout.count[1];               \
                                                                              \
     do {                                                                     \
        *itemPos++ MK__OP##= otherVal;                                        \
        *itemPos++ MK__OP##= otherVal;                                        \
        *itemPos++ MK__OP##= otherVal;                                        \
        *itemPos++ MK__OP##= otherVal;                                        \
     } while (itemPos != itemPos_end);                                        \
     break;                                                                   \
  }

inline
void
mkMatrixScale(MkMatrix * __restrict matrix,
              void * __restrict other,
              const MkBufLayout layout) {
   switch (layout.type) {
      case MK_FLOAT:  MK__MAT_TMPL_SCALAR(*, float)
      case MK_DOUBLE: MK__MAT_TMPL_SCALAR(*, double)
      case MK_INT32:  MK__MAT_TMPL_SCALAR(*, int32_t)
      case MK_INT64:  MK__MAT_TMPL_SCALAR(*, int64_t)
      default: break;
   }
}

inline
void
mkMatrixAdd(MkMatrix * __restrict matrix,
            void * __restrict other,
            const MkBufLayout layout) {
   switch (layout.type) {
      case MK_FLOAT:  MK__MAT_TMPL_SCALAR(+, float)
      case MK_DOUBLE: MK__MAT_TMPL_SCALAR(+, double)
      case MK_INT32:  MK__MAT_TMPL_SCALAR(+, int32_t)
      case MK_INT64:  MK__MAT_TMPL_SCALAR(+, int64_t)
      default: break;
   }
}

inline
void
mkMatrixSub(MkMatrix * __restrict matrix,
            void * __restrict other,
            const MkBufLayout layout) {
   switch (layout.type) {
      case MK_FLOAT:  MK__MAT_TMPL_SCALAR(-, float)
      case MK_DOUBLE: MK__MAT_TMPL_SCALAR(-, double)
      case MK_INT32:  MK__MAT_TMPL_SCALAR(-, int32_t)
      case MK_INT64:  MK__MAT_TMPL_SCALAR(-, int64_t)
      default: break;
   }
}

inline
void
mkMatrixDiv(MkMatrix * __restrict matrix,
            void * __restrict other,
            const MkBufLayout layout) {
   switch (layout.type) {
      case MK_FLOAT:  MK__MAT_TMPL_SCALAR(/, float)
      case MK_DOUBLE: MK__MAT_TMPL_SCALAR(/, double)
      case MK_INT32:  MK__MAT_TMPL_SCALAR(/, int32_t)
      case MK_INT64:  MK__MAT_TMPL_SCALAR(/, int64_t)
      default: break;
   }
}

#ifdef __cplusplus
}
#endif
#endif /* mk_matrix_impl_sc_h */
