/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "../include/mk.h"

#define __MATHKIT_SRC_

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
mkInt32PrinterImpl(FILE * __restrict ostream,
                  void * __restrict item);

static
inline
void
mkInt64PrinterImpl(FILE * __restrict ostream,
                   void * __restrict item);

/* ************************************************************************* */

/* Printers */
MK_EXPORT
MK_EXTERN
MkPrintFn mkFloatPrinter = mkFloatPrinterImpl;

MK_EXPORT
MK_EXTERN
MkPrintFn mkDoublePrinter = mkDoublePrinterImpl;

MK_EXPORT
MK_EXTERN
MkPrintFn mkInt32Printer = mkInt32PrinterImpl;

MK_EXPORT
MK_EXTERN
MkPrintFn mkInt64Printer = mkInt64PrinterImpl;

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

static
inline
void
mkInt32PrinterImpl(FILE * __restrict ostream,
                   void * __restrict item) {
  fprintf(ostream, "\t%d,", *(int32_t *)item);
}

static
inline
void
mkInt64PrinterImpl(FILE * __restrict ostream,
                   void * __restrict item) {
  fprintf(ostream, "\t%lld,", *(int64_t *)item);
}
