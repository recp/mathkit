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
MK_EXTERN
MkOp mkOpMultiplyF = mkOpMFltImpl;

MK_EXTERN
MkOp mkOpMultiplyD = mkOpMDblImpl;

MK_EXTERN
MkOp mkOpMultiplyInt32 = mkOpMInt32Impl;

MK_EXTERN
MkOp mkOpMultiplyInt64 = mkOpMInt64Impl;

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
