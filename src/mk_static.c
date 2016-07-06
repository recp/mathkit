/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#define __MATHKIT_SRC_

#include "../include/mk.h"

static
inline
void
mkFloatPrinterImpl(FILE * __restrict ostream,
                   void * __restrict item);

static
inline
void
mkDoublePrinterImpl(FILE * __restrict ostream,
                    void * __restrict item);

/* multiplication */

static
inline
void
mkOpMFltImpl(void * __restrict a,
             void * __restrict b);

static
inline
void
mkOpMDblImpl(void * __restrict a,
             void * __restrict b);

static
inline
void
mkOpMInt32Impl(void * __restrict a,
               void * __restrict b);

static
inline
void
mkOpMInt64Impl(void * __restrict a,
               void * __restrict b);

/* addition */

static
inline
void
mkOpAFltImpl(void * __restrict a,
             void * __restrict b);

static
inline
void
mkOpADblImpl(void * __restrict a,
             void * __restrict b);

static
inline
void
mkOpAInt32Impl(void * __restrict a,
               void * __restrict b);

static
inline
void
mkOpAInt64Impl(void * __restrict a,
               void * __restrict b);

/* ************************************************************************* */

/* Printers */
MK_EXTERN
MkPrintFn mkFloatPrinter = mkFloatPrinterImpl;

MK_EXTERN
MkPrintFn mkDoublePrinter = mkDoublePrinterImpl;

/* Op */
static
MkOp mkOpMultiplyFImpl = {
  .type  = MK_OP_TYPE_MULTIPLY,
  .op    = mkOpMFltImpl,
  .addop = mkOpAFltImpl
};

static
MkOp mkOpMultiplyDImpl = {
  .type  = MK_OP_TYPE_MULTIPLY,
  .op    = mkOpMDblImpl,
  .addop = mkOpADblImpl
};

static
MkOp mkOpMultiplyInt32Impl = {
  .type  = MK_OP_TYPE_MULTIPLY,
  .op    = mkOpMInt32Impl,
  .addop = mkOpAInt32Impl
};

static
MkOp mkOpMultiplyInt64Impl = {
  .type  = MK_OP_TYPE_MULTIPLY,
  .op    = mkOpMInt64Impl,
  .addop = mkOpAInt64Impl
};

/* addition */
static
MkOp mkOpAdditionFImpl = {
  .type  = MK_OP_TYPE_ADDITION,
  .op    = mkOpAFltImpl,
  .addop = mkOpAFltImpl
};

static
MkOp mkOpAdditionDImpl = {
  .type  = MK_OP_TYPE_ADDITION,
  .op    = mkOpADblImpl,
  .addop = mkOpADblImpl
};

static
MkOp mkOpAdditionInt32Impl = {
  .type  = MK_OP_TYPE_ADDITION,
  .op    = mkOpAInt32Impl,
  .addop = mkOpAInt32Impl
};

static
MkOp mkOpAdditionInt64Impl = {
  .type  = MK_OP_TYPE_ADDITION,
  .op    = mkOpAInt64Impl,
  .addop = mkOpAInt64Impl
};

MK_EXTERN
MkOp * const mkOpMultiplyF = &mkOpMultiplyFImpl;

MK_EXTERN
MkOp * const mkOpMultiplyD = &mkOpMultiplyDImpl;

MK_EXTERN
MkOp * const mkOpMultiplyInt32 = &mkOpMultiplyInt32Impl;

MK_EXTERN
MkOp * const mkOpMultiplyInt64 = &mkOpMultiplyInt64Impl;

MK_EXTERN
MkOp * const mkOpAdditionF = &mkOpAdditionFImpl;

MK_EXTERN
MkOp * const mkOpAdditionD = &mkOpAdditionDImpl;

MK_EXTERN
MkOp * const mkOpAdditionInt32 = &mkOpAdditionInt32Impl;

MK_EXTERN
MkOp * const mkOpAdditionInt64 = &mkOpAdditionInt64Impl;


static float   Mk__floatZero  = 0.0f;
static double  Mk__doubleZero = 0.0;
static int32_t Mk__int32Zero  = 0;
static int64_t Mk__int64Zero  = 0L;

static float   Mk__floatOne   = 1.0f;
static double  Mk__doubleOne  = 1.0;
static int32_t Mk__int32One   = 1;
static int64_t Mk__int64One   = 1L;


MK_EXTERN void * const MkFloatZero  = &Mk__floatZero;
MK_EXTERN void * const MkDoubleZero = &Mk__doubleZero;
MK_EXTERN void * const MkInt32Zero  = &Mk__int32Zero;
MK_EXTERN void * const MkInt64Zero  = &Mk__int64Zero;

MK_EXTERN void * const MkFloatOne   = &Mk__floatOne;
MK_EXTERN void * const MkDoubleOne  = &Mk__doubleOne;
MK_EXTERN void * const MkInt32One   = &Mk__int32One;
MK_EXTERN void * const MkInt64One   = &Mk__int64One;

/* ************************************************************************* */

static
inline
void
mkFloatPrinterImpl(FILE * __restrict ostream,
                   void * __restrict item) {
  fprintf(ostream, "\t%0.2ff,", *(float *)item);
}

static
inline
void
mkDoublePrinterImpl(FILE * __restrict ostream,
                    void * __restrict item) {
  fprintf(ostream, "\t%0.2f,", *(double *)item);
}

/* multiplication */

static
inline
void
mkOpMFltImpl(void * __restrict a,
             void * __restrict b) {
  *(float *)a *= *(float *)b;
}

static
inline
void
mkOpMDblImpl(void * __restrict a,
             void * __restrict b) {
  *(double *)a *= *(double *)b;
}

static
inline
void
mkOpMInt32Impl(void * __restrict a,
               void * __restrict b) {
  *(int32_t *)a *= *(int32_t *)b;
}

static
inline
void
mkOpMInt64Impl(void * __restrict a,
               void * __restrict b) {
  *(int64_t *)a *= *(int64_t *)b;
}

/* addition */

static
inline
void
mkOpAFltImpl(void * __restrict a,
             void * __restrict b) {
  *(float *)a += *(float *)b;
}

static
inline
void
mkOpADblImpl(void * __restrict a,
             void * __restrict b) {
  *(double *)a += *(double *)b;
}

static
inline
void
mkOpAInt32Impl(void * __restrict a,
               void * __restrict b) {
  *(int32_t *)a += *(int32_t *)b;
}

static
inline
void
mkOpAInt64Impl(void * __restrict a,
               void * __restrict b) {
  *(int64_t *)a += *(int64_t *)b;
}
