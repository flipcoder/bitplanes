#ifndef _MATHCOMMON_H_INCLUDED
#define _MATHCOMMON_H_INCLUDED

#include <cmath>

#define EPSILON 0.00001

#ifndef M_PI
    #define M_PI 3.1415926535897932385
#endif

#define DEG2RAD(X) ((X)*M_PI/180.0)
#define RAD2DEG(X) ((X)*180.0/M_PI)
#define DEG2RADf(X) ((X)*(float)M_PI/180.0f)
#define RAD2DEGf(X) ((X)*180.0f/(float)M_PI)

inline float sin_deg(float theta){
    return (sinf(theta*((float)M_PI/180.0f)));
}
inline float cos_deg(float theta){
    return (cosf(theta*((float)M_PI/180.0f)));
}
inline float tan_deg(float theta){
    return (tanf(theta*((float)M_PI/180.0f)));
}

inline double sin_deg(double theta){
    return (sin(theta*(M_PI/180.0)));
}
inline double cos_deg(double theta){
    return (cos(theta*(M_PI/180.0)));
}
inline double tan_deg(double theta){
    return (tan(theta*(M_PI/180.0)));
}

inline bool floatcmp(float a, float b){
    return(fabs(a-b) < EPSILON);
}

template <class T>
inline T absval(T x)
{
    return x>0?x:-x;
}

template <class T>
inline T maxval(T a, T b)
{
    return a>b?a:b;
}

// checks for absolute value, returns actual number
template<class T>
inline T fartherAbs(T a, T b)
{
    if(abs(a) > abs(b))
        return a;
    return b;
}

template<class T>
inline T clamp(T val, T low, T high)
{
    return val < low ? low : (val > high ? high : val);
}

#define sq(a) ((a)*(a))

//#ifdef _MATRIX_ROW_MAJOR
//    #define _MATRIX_INDEX(m,i,j) (m)[i][j]
//    #define _MATRIX_INDEX_1D(m,i,j) (m)[j*4+i]
//#else
//    #define _MATRIX_INDEX(m,i,j) (m)[j][i]
//    #define _MATRIX_INDEX_1D(m,i,j) (m)[i*4+j]
//#endif

inline bool IS_NAN(double f){ return f!=f; }
inline bool IS_NAN(float f){ return f!=f; }

#endif

