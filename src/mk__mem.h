/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mk__mem_h
#define mk__mem_h

#include <stdint.h>
#include <string.h>

#define mk__memcpy(dest, src, size)                                           \
  do {                                                                        \
    int32_t *srci;                                                            \
    int32_t *srci_end;                                                        \
    int32_t *desti;                                                           \
                                                                              \
    srci     = (int32_t *)src;                                                \
    srci_end = (int32_t *)((char *)srci + size);                              \
    desti    = (int32_t *)dest;                                               \
                                                                              \
    while (srci != srci_end)                                                  \
      *desti++ = *srci++;                                                     \
  } while (0)

#define mk__memzero(dest, size)                                               \
  do {                                                                        \
    int32_t *desti;                                                           \
    int32_t *desti_end;                                                       \
                                                                              \
    desti     = (int32_t *)dest;                                              \
    desti_end = (int32_t *)((char *)desti + size);                            \
                                                                              \
    while (desti != desti_end)                                                \
      *desti++ = 0;                                                           \
  } while (0)

#endif /* mk__mem_h */
