#ifndef _VECTOR2_H
#define _VECTOR2_H

// Not everything is here but I will add more operators as I need them

#include <cmath>
#include "common.h"

class Vector2
{
	public:

		union
		{
			struct { float x,y; };
			float p[2];
		};

		Vector2():
			x(0.0f),
			y(0.0f)
		{}

		Vector2(const Vector2& v)
		{
			x = v.x;
			y = v.y;
		}

		explicit Vector2(float f) {
			x=y=f;
		}
		Vector2(float fx, float fy) {
			x=fx;
			y=fy;
		}
		void zero(){
			x=y=0.0f;
		}

		Vector2 operator +(const Vector2& v) const
        {
            return Vector2(x+v.x, y+v.y);
        }
		Vector2 operator +=(const Vector2& v)
		{
			return (*this = *this+v);
		}
        Vector2 operator -(const Vector2& v) const
        {
            return Vector2(x-v.x, y-v.y);
        }
		Vector2 operator -() const // negate
		{
			return Vector2(-x,-y);
		}
        Vector2 operator -=(const Vector2& v)
        {
            return (*this = *this-v);
        }

		Vector2 operator |(float length) const
		{
			float mag = magnitude();
			if(!floatcmp(mag,0.0f))
				return (*this * (length/mag));
			else
				return Vector2();
		}

		float operator[](unsigned int idx) const {
			return p[idx];
		}
		float& operator[](unsigned int idx){
			return p[idx];
		}

        float dot(const Vector2& v2) const
        {
            return ((x*v2.x)+(y*v2.y));
        }
        Vector2 operator *(const Vector2 v2) const
        {
            return Vector2(x*v2.x, y*v2.y);
        }
        Vector2 operator /(const Vector2& v2) const
        {
            if(floatcmp(v2.x,0.0f) || floatcmp(v2.y,0.0f))
                return Vector2();
            return Vector2(x/v2.x,y/v2.y);
        }

		Vector2 operator *(float s) const
		{
			return Vector2((x*s),(y*s));
		}
        Vector2 operator /(float s) const
		{
            if(floatcmp(s,0.0f))
                return Vector2(0.0f, 0.0f);
			return Vector2((x/s),(y/s));
		}
		friend const Vector2 operator*(float s, const Vector2& v)
		{
			return v*s;
		}

		Vector2 operator *=(float s)
		{
			return (*this = (*this * s));
		}

		Vector2& operator =(const Vector2& v2)
		{
			x = v2.x;
			y = v2.y;
			return *this;
		}
        
        friend bool operator==(const Vector2& a, const Vector2& b) {
            return(floatcmp(a.x, b.x) &&
                floatcmp(a.y, b.y));
        }

		float magnitude() const
        {
            return sqrt(x*x + y*y);
        }

		const Vector2 normalize()
        {
            float mag = magnitude();
    
            if(!floatcmp(mag, 0.0f))
            {
                x/=mag;
                y/=mag;
            }
			return *this;
        }

		Vector2 unit() const
		{
			Vector2 v = *this;
			return v.normalize();
		}

		float* array() const { return (float*)&p[0]; }

		bool isZero(){
			return (floatcmp(x,0.0f) && floatcmp(y,0.0f));
		}

		Vector2 X() const { return Vector2(x, 0.0f); }
		Vector2 Y() const { return Vector2(0.0f, y); }
		
		Vector2 mult(const Vector2& v) const {
			return Vector2(
				x * v.x,
				y * v.y
			);
		}

};

#endif

