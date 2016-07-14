/*
* Copyright (c), Recep Aslantas.
*
* MIT License (MIT), http://opensource.org/licenses/MIT
* Full license can be found in the LICENSE file
*/

#ifndef mk__config_h
#define mk__config_h

#if defined(_WIN32) || defined(WIN32)

// Exclude rarely-used stuff from Windows headers
#  define WIN32_LEAN_AND_MEAN 
#  include <SDKDDKVer.h>

// Windows Header Files:
#  include <windows.h>

#endif

#endif /* mk__config_h */