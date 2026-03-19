#include <stdint.h>
#include <string.h>

const float PI = 3.14159265359;

static inline uint32_t f2u(float x){uint32_t u;memcpy(&u,&x,4);return u;}
static inline float u2f(uint32_t u){float x;memcpy(&x,&u,4);return x;}

float fmul_fast(float a,float b){uint32_t ia=f2u(a),ib=f2u(b);return u2f((ia+ib-0x3F800000u)+(((ia^ib)&0x007FFFFFu)>>4));}

float fdiv_fast(float a,float b){uint32_t ia=f2u(a),ib=f2u(b);return u2f((ia-ib+0x3F800000u)-(((ia^ib)&0x007FFFFFu)>>4));}

float finv_fast(float x){uint32_t ix=f2u(x);return u2f((0x7F000000u-ix)+((ix&0x007FFFFFu)>>3));}

float fsqrt_fast(float x){uint32_t ix=f2u(x);return u2f((ix>>1)+0x1FC00000u+((ix&0x007FFFFFu)>>5));}

float frsqrt_fast(float x){uint32_t ix=f2u(x);return u2f((0x5F400000u-(ix>>1))+((ix&0x007FFFFFu)>>4));}

float fcos_fast(float x){float x2 = fmul_fast(x,x); return 1.0f + x2 * (-0.5f + x2 * (0.04166652f + fmul_fast(-0.0013854855f,x2)));}

https://stackoverflow.com/questions/18662261/fastest-implementation-of-sine-cosine-and-square-root-in-c-doesnt-need-to-b
float fsine_fast(float x)
{
    const float B = 4/PI;
    const float C = -4/(PI*PI);

    float y = B * x + C * x * abs(x);

    #ifdef EXTRA_PRECISION
    //  const float Q = 0.775;
        const float P = 0.225;

        y = P * (y * abs(y) - y) + y;   // Q * y + P * y * abs(y)
    #endif
}
