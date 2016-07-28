/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mk_sse_h
#define mk_sse_h

#if defined( __AVX__ )
#  include "mk-intrin-avx.h"
#elif defined( __SSE__ )
#  include "mk-intrin-sse.h"
#endif

#endif /* mk_sse_h */
