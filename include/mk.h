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
#include "mk-vector.h"
#include "mk-matrix.h"

/* buit-in operators
 *
 * mkOp [OpType][Param1 Type][Param2 Type]
 * mkOp [OpType][Param1 and Param2 Type]
 */

/* multiplication operators */
MK_EXPORT
MK_EXTERN
MkOp * const mkOpMultF;

MK_EXPORT
MK_EXTERN
MkOp * const mkOpMultD;

MK_EXPORT
MK_EXTERN
MkOp * const mkOpMultInt32;

MK_EXPORT
MK_EXTERN
MkOp * const mkOpMultInt64;

/* addition operators */

MK_EXPORT
MK_EXTERN
MkOp * const mkOpAddF;

MK_EXPORT
MK_EXTERN
MkOp * const mkOpAddD;

MK_EXPORT
MK_EXTERN
MkOp * const mkOpAddInt32;

MK_EXPORT
MK_EXTERN
MkOp * const mkOpAddInt64;

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

MK_EXPORT MK_EXTERN void * const MkFloatZero;
MK_EXPORT MK_EXTERN void * const MkDoubleZero;
MK_EXPORT MK_EXTERN void * const MkInt32Zero;
MK_EXPORT MK_EXTERN void * const MkInt64Zero;

MK_EXPORT MK_EXTERN void * const MkFloatOne;
MK_EXPORT MK_EXTERN void * const MkDoubleOne;
MK_EXPORT MK_EXTERN void * const MkInt32One;
MK_EXPORT MK_EXTERN void * const MkInt64One;

#ifdef __cplusplus
}
#endif
#endif /* mathkit_h */
