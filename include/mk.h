/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mathkit_h
#  define mathkit_h

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

MK_EXTERN
MkOp * const mkOpMultiplyF;

MK_EXTERN
MkOp * const mkOpMultiplyD;

MK_EXTERN
MkOp * const mkOpMultiplyInt32;

MK_EXTERN
MkOp * const mkOpMultiplyInt64;

/* addition operators */

MK_EXTERN
MkOp * const mkOpAdditionF;

MK_EXTERN
MkOp * const mkOpAdditionD;

MK_EXTERN
MkOp * const mkOpAdditionInt32;

MK_EXTERN
MkOp * const mkOpAdditionInt64;

/* buit-in printers */

MK_EXTERN
MkPrintFn mkFloatPrinter;

MK_EXTERN
MkPrintFn mkDoublePrinter;

MK_EXTERN void * const MkFloatZero;
MK_EXTERN void * const MkDoubleZero;
MK_EXTERN void * const MkInt32Zero;
MK_EXTERN void * const MkInt64Zero;

MK_EXTERN void * const MkFloatOne;
MK_EXTERN void * const MkDoubleOne;
MK_EXTERN void * const MkInt32One;
MK_EXTERN void * const MkInt64One;

#endif /* mathkit_h */
