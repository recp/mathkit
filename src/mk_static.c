/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#define __MATHKIT_SRC_

#include "../include/mathkit.h"

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

/* Printers */
MK_EXTERN
MkPrintFn mkFloatPrinter = mkFloatPrinterImpl;

MK_EXTERN
MkPrintFn mkDoublePrinter = mkDoublePrinterImpl;

/* Op */
static
MkOp mkOpMultiplyFImpl = {
  .type = MK_OP_TYPE_MULTIPLY,
  .op   = mkOpMFltImpl
};

static
MkOp mkOpMultiplyDImpl = {
  .type = MK_OP_TYPE_MULTIPLY,
  .op   = mkOpMDblImpl
};

static
MkOp mkOpMultiplyInt32Impl = {
  .type = MK_OP_TYPE_MULTIPLY,
  .op   = mkOpMInt32Impl
};

static
MkOp mkOpMultiplyInt64Impl = {
  .type = MK_OP_TYPE_MULTIPLY,
  .op   = mkOpMInt64Impl
};


MK_EXTERN
MkOp * const mkOpMultiplyF = &mkOpMultiplyFImpl;

MK_EXTERN
MkOp * const mkOpMultiplyD = &mkOpMultiplyDImpl;

MK_EXTERN
MkOp * const mkOpMultiplyInt32 = &mkOpMultiplyInt32Impl;

MK_EXTERN
MkOp * const mkOpMultiplyInt64 = &mkOpMultiplyInt64Impl;

/* ************************************************************************* */

static
inline
void
mkFloatPrinterImpl(FILE * __restrict ostream,
                   void * __restrict item) {
  fprintf(ostream, "\t%0.3ff,", *(float *)item);
}

static
inline
void
mkDoublePrinterImpl(FILE * __restrict ostream,
                    void * __restrict item) {
  fprintf(ostream, "\t%0.3f,", *(double *)item);
}

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
