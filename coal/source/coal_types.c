#include "../include/coal_types.h"


V4 COAL_PREFIX(MakeV4)(F32 x, F32 y, F32 z, F32 w)
{
    return (V4) {x,y,z,w};
}

F32 COAL_PREFIX(GetLengthStr)(String8 String)
{
    I32 i =0;
    while (String[i++] != '\0'); 
    return i;
}