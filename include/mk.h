/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mathkit_h
#  define mathkit_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "mk-common.h"
#include "mk-mem.h"
#include "mk-vector.h"
#include "mk-matrix.h"

/* buit-in printers */

MK_EXPORT
MK_EXTERN
MkPrintFn mkFloatPrinter;

MK_EXPORT
MK_EXTERN
MkPrintFn mkDoublePrinter;

MK_EXPORT
MK_EXTERN
MkPrintFn mkInt32Printer;

MK_EXPORT
MK_EXTERN
MkPrintFn mkInt64Printer;

#ifdef __cplusplus
}
#endif
#endif /* mathkit_h */
