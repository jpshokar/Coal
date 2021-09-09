

#ifndef COAL_MATRICES_H
#define COAL_MATRICES_H
#include "coal_types.h"

COALAPI void
COAL_PREFIX(M4MultiplyM4)(M4 a, M4 b, M4 Dest);
COALAPI void
COAL_PREFIX(M4AddM4)(M4 a, M4 b, M4 Dest);
COALAPI void
COAL_PREFIX(M4SubtractM4)(M4 a, M4 b, M4 Dest);
COALAPI void
COAL_PREFIX(M4DivideM4)(M4 a, M4 b, M4 Dest);
COALAPI void 
COAL_PREFIX(M4Clear)(M4 Dest);
COALAPI void 
COAL_PREFIX(M4Orthographic)(M4 Dest, F32 left, F32 right, F32 bottom, F32 top, F32 near, F32 far); 
COALAPI void 
COAL_PREFIX(M4Perspective)(M4 Dest, F32 FOV, F32 Aspect, F32 near, F32 far);
COALAPI void
COAL_PREFIX(M4Translation)(M4 Dest, F32 x, F32 y, F32 z);
COALAPI void
COAL_PREFIX(M4Scale)(M4 Dest, F32 x, F32 y, F32 z );
COALAPI void
COAL_PREFIX(M4Rotate)(M4 Dest, F32 angle, F32 x, F32 y, F32 z );
COALAPI void 
COAL_PREFIX(M4LookAt)(M4 Dest, F32 EyeX, F32 EyeY, F32 EyeZ,  F32 CenterX, F32 CenterY,F32 CenterZ, F32 UpX, F32 UpY,F32 UpZ);

#endif 
