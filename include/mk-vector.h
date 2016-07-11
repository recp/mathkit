/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mk_vector_h
#define mk_vector_h

#include <stddef.h>

typedef struct MkVector {
  size_t itemSize;
  size_t itemCount;
  void   *value;
} MkVector;

#endif /* mk_vector_h */
