#include "../include/coal_matrices.h"



void
COAL_PREFIX(M4MultiplyM4)(M4 a, M4 b, M4 Dest)
{
    for (I32 x=0;x<4;x++)
        for (I32 y=0;y<4;y++)
        Dest[x][y] = a[x][y] * b[x][y];
}
void
COAL_PREFIX(M4AddM4)(M4 a, M4 b, M4 Dest)
{
    for (I32 x=0;x<4;x++)
        for (I32 y=0;y<4;y++)
        Dest[x][y] = a[x][y] + b[x][y];
}

void
COAL_PREFIX(M4SubtractM4)(M4 a, M4 b, M4 Dest)
{
    for (I32 x=0;x<4;x++)
        for (I32 y=0;y<4;y++)
        Dest[x][y] = a[x][y] - b[x][y];
}

void
COAL_PREFIX(M4DivideM4)(M4 a, M4 b, M4 Dest)
{
    for (I32 x=0;x<4;x++)
        for (I32 y=0;y<4;y++)
        Dest[x][y] = a[x][y] / b[x][y];
}
void 
COAL_PREFIX(M4Clear)(M4 Dest)
{
    for (I32 x=0;x<4;x++)
        for (I32 y=0;y<4;y++)
        Dest[x][y] = 0;
}

void 
COAL_PREFIX(M4Orthographic)(M4 Dest, F32 left, F32 right, F32 bottom, F32 top, F32 near, F32 far)
{
    COAL_PREFIX(M4Clear)(Dest);
    Dest[0][0] = 2 / (right - left);
    Dest[1][1] = 2 / (top - bottom);
    Dest[2][2] = (-2) / (far - near);
    Dest[3][0] = -( (right+left)/(right-left));
    Dest[3][1] = -((top+bottom)/(top-bottom));
    Dest[3][2] = -((far+near)/(far-near));
    Dest[3][3] = 1;
}


void 
COAL_PREFIX(M4Perspective)(M4 Dest, F32 FOV, F32 Aspect, F32 near, F32 far)
{
    COAL_PREFIX(M4Clear)(Dest);
    
    
    F32 cotangent  = 1.0f / COAL_TAN(FOV * (COAL_PI / 360.0F));
    
    Dest[0][0] = cotangent / Aspect;
    Dest[1][1] = cotangent;
    Dest[2][2] = -1.0f;
    Dest[2][3] = (near + far) / (near - far);
    Dest[3][2] = (2.0f * near * far) / (near-far);
    Dest[3][3] = 0.0f;
    
}

void
COAL_PREFIX(M4Translation)(M4 Dest, F32 x, F32 y, F32 z)
{
    COAL_PREFIX(M4Clear)(Dest);
    Dest[0][0] = 1;
    Dest[1][1] = 1;
    Dest[2][2] = 1;
    Dest[3][3] = 1;
    Dest[3][0] = x;
    Dest[3][1] = y;
    Dest[3][2] = z;
}

void
COAL_PREFIX(M4Scale)(M4 Dest,  F32 x, F32 y, F32 z )
{
    COAL_PREFIX(M4Clear)(Dest);
    /* NOTE: Untested. */
    Dest[0][0] = 1.0f;
    Dest[1][1] = 1.0f;
    Dest[2][2] = 1.0f;
    Dest[3][3] = 1.0f;
    
    
    
    Dest[0][0] = x;
    Dest[1][1] = y;
    Dest[2][2] = z;
}
void
COAL_PREFIX(M4Rotate)(M4 Dest, F32 angle, F32 x, F32 y, F32 z )
{
    COAL_PREFIX(M4Clear)(Dest);
    Dest[0][0] = 1.0f;
    Dest[1][1] = 1.0f;
    Dest[2][2] = 1.0f;
    Dest[3][3] = 1.0f;
    
    /* normalizing */
    F32 DotProduct = COAL_SQRT((x * x) + (y * y) + (z * z));
    if (DotProduct != 0.0f)
    {
        x = x * (1.0f / DotProduct);
        y = y * (1.0f / DotProduct);
        z= z * (1.0f / DotProduct);
    };
    
    F32 stheta = COAL_SIN( COAL_DEG2RAD( angle));
    F32 ctheta = COAL_COS( COAL_DEG2RAD( angle));
    F32 cvalue = 1.0f - ctheta;
    
    Dest[0][0] = (x * y * cvalue) + ctheta;
    Dest[0][1] = (x * y * cvalue) + (z * stheta);
    Dest[0][2] = (x * z * cvalue) - (y * stheta);
    
    Dest[1][0] = (y * x * cvalue) - (z * stheta);
    Dest[1][1] = (y * y * cvalue) + ctheta;
    Dest[1][2] = (y * z * cvalue) + (x * stheta);
    
    Dest[2][0] = (z * x * cvalue) + (y * stheta);
    Dest[2][1] = (z * y * cvalue) - (x * stheta);
    Dest[2][2] = (z * z * cvalue) + ctheta;
    
    
    
}

void 
COAL_PREFIX(M4LookAt)(M4 Dest, F32 EyeX, F32 EyeY, F32 EyeZ,     F32 CenterX, F32 CenterY,F32 CenterZ, F32 UpX, F32 UpY,F32 UpZ)
{
    
    
    // TODO
}