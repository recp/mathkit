# mathkit
C vector, matrix library (including 3d, opengl math)

|| **Unix (gcc, clang)** | **Windows (msvc)** |
|---|---|---|
| **Build** | [![Build Status](https://travis-ci.org/recp/mathkit.svg?branch=master)](https://travis-ci.org/recp/mathkit)|[![Build status](https://ci.appveyor.com/api/projects/status/xodt8l6bp2jr41q6/branch/master?svg=true)](https://ci.appveyor.com/project/recp/mathkit/branch/master)

*Note: This project is not ready for production yet*

mathkit uses `MkHint` struct to help compiler to eliminate branches compile-time. If compiler will do, compile-time known matrices will be optimised by compiler e.g. vectorization, unrool loops, eliminate unused braches... To do that almost all important functions are inline (if compiler can inline).
User can prefer a matrix is compile-time or run time by `MkHint`. For instance if we know that our matrices are 4x4 e.g. when working on OpenGL then we can optimise the matrices aggressively in compile-time

mathkit uses single type for matrices: `MkMatrix` (run time && compile time matrices)

## Usage
```C
#include <mk.h>
#include <mk-matrix.h>

float m1Buf[16] = {
  1,  2,  3,  4,
  5,  6,  7,  8,
  9,  10, 11, 12,
  13, 14, 15, 16  
};

float m2Buf[16] = {
  10,  20,  30,  40,
  50,  60,  70,  80,
  90,  10,  110, 120,
  130, 140, 150, 160  
};

float m3Buf[16] = {
  0.1,  0.2,  0.3,  0.4,
  0.5,  0.6,  0.7,  0.8,
  0.9,  0.10, 0.11, 0.12,
  0.13, 0.14, 0.15, 0.16  
};

float resultBuf[16];

#define hint4x4f MK_HINT(MK_FLOAT, 4, 4, false)

MkMatrix m1;
MkMatrix m2;
MkMatrix m3;
MkMatrix result;

mkMatrixInit(&m1, m1Buf, hint4x4f);
mkMatrixInit(&m2, m2Buf, hint4x4f);
mkMatrixInit(&m3, m3Buf, hint4x4f);
mkMatrixInit(&result, resultBuf, hint4x4f);

mkMatrixMatrixMulN((MkMatrix *[]){&m1, &m2, &m3},
                   &result,
                   3,
                   (MkHint []){hint4x4f, hint4x4f, hint4x4f});

mkMatrixPrint(&result,
              mkFloatPrinter,
              stdout);      
```

```
Output:

Matrix (4x4):
	1601.00f,	896.00f,	1082.00f,	1268.00f,
	3677.00f,	2040.00f,	2460.40f,	2880.80f,
	5753.00f,	3184.00f,	3838.80f,	4493.60f,
	7829.00f,	4328.00f,	5217.20f,	6106.40f,
```

## Build

### Unix (Autotools)

```text
$ sh autogen.sh
$ ./configure
$ make
$ [sudo] make install
```

### Windows (MSBuild)

```text
$ msbuild mathkit.vcxproj /p:Configuration=Release
```

## Roadmap

- [ ] Row Major Matrices
    - [X] Matrix - Matrix multiplication
    - [X] Matrix - Scalar ops
    - [X] Small matrix optimisations
    - [ ] Large matrix optimisations (SSE, AVX)
- [ ] Col Major Matrices
- [ ] Vectors
    - [ ] Basic struct
    - [ ] Normalize, Cross, Dot products
- [ ] GL Math
    - [ ] basic funcs(lookAt, translate, rotate...) 
- [ ] Matrix - Vectors
- [ ] Tests, Benchmarks
- [ ] Documentation
