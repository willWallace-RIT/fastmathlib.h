#include <stdint.h>
#include <string.h>

static inline uint32_t f2u(float x){uint32_t u;memcpy(&u,&x,4);return u;}
static inline float u2f(uint32_t u){float x;memcpy(&x,&u,4);return x;}

float fmul_fast(float a,float b){uint32_t ia=f2u(a),ib=f2u(b);return u2f((ia+ib-0x3F800000u)+(((ia^ib)&0x007FFFFFu)>>4));}

float fdiv_fast(float a,float b){uint32_t ia=f2u(a),ib=f2u(b);return u2f((ia-ib+0x3F800000u)-(((ia^ib)&0x007FFFFFu)>>4));}

float finv_fast(float x){uint32_t ix=f2u(x);return u2f((0x7F000000u-ix)+((ix&0x007FFFFFu)>>3));}

float fsqrt_fast(float x){uint32_t ix=f2u(x);return u2f((ix>>1)+0x1FC00000u+((ix&0x007FFFFFu)>>5));}

float frsqrt_fast(float x){uint32_t ix=f2u(x);return u2f((0x5F400000u-(ix>>1))+((ix&0x007FFFFFu)>>4));}
