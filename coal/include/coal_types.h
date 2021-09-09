#ifndef COAL_TYPES_H
#define COAL_TYPES_H
#define UNICODE

typedef int I32;
typedef char I8;

typedef const char* String8;

typedef unsigned int U32;

typedef float F32;
typedef unsigned char U8;
typedef struct V3 {float x,y,z;} V3;
typedef struct V4 {float x,y,z,w;} V4;
typedef struct Color {float r,g,b,a;} Color;
typedef struct V2 {float x,y;} V2;
typedef int B32;
typedef F32 M4[4][4];

#define COAL_PREFIX(name) Coal_##name
#define COALTYPE_PREFIX(name) Coal##name
#define COALENUM_PREFIX(name) COAL_##name

#ifndef COALAPI
#define COALAPI
#endif
#if defined(_WIN32)
#if defined(BUILD_SHARED)
#define COALAPI __declspec(dllexport)
#elif defined(USE_SHARED)
#define COALAPI __declspec(dllimport)
#endif
#endif


#ifndef COAL_PRINTF
#include <stdio.h>
#define COAL_PRINTF printf
#endif
#ifndef COAL_MALLOC
#include <stdlib.h>
#define COAL_MALLOC malloc
#endif
#ifndef COAL_TAN
#include <math.h>
#define COAL_TAN tan
#endif
#ifndef COAL_SIN
#include <math.h>
#define COAL_SIN sin
#endif
#ifndef COAL_COS
#include <math.h>
#define COAL_COS cos
#endif
#ifndef COAL_PI
#define COAL_PI 3.14159265359
#endif
#ifndef COAL_DEG2RAD
#define COAL_DEG2RAD(x) x * COAL_PI/180
#endif

#ifndef COAL_SQRT
#include <math.h>
#define COAL_SQRT sqrtf
#endif
V4
COAL_PREFIX(MakeV4)(F32 x, F32 y, F32 z, F32 w);
F32 
COAL_PREFIX(GetLengthStr)(String8 String);



#include <GL/glew.h>

#endif

