/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef mk_sse_h
#define mk_sse_h

#if defined( _WIN32 )
#  ifdef __AVX2__
#  elif defined ( __AVX__ )
#  elif _M_IX86_FP == 1
#    define __SSE__
#  elif _M_IX86_FP == 2 || (defined(_M_AMD64) || defined(_M_X64))
#    define __SSE2__
#  endif
#endif

#if defined( __AVX__ )
#  include "mk-intrin-avx.h"
#elif defined( __SSE__ ) || defined( __SSE2__ )
#  include "mk-intrin-sse.h"
#endif

#endif /* mk_sse_h */
