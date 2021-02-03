//
//  Vector2.h
//  Koi
//
//  Created by Michael Schuff on 2/2/21.
//

#ifndef Vector2_h
#define Vector2_h

#include <math.h>

namespace koi {
    
    
    template<class T>
    struct Vector2 {
        static const Vector2 ZERO, X_AXIS, Y_AXIS;
        
        
        T x = 0, y = 0;
        Vector2() : x(0), y(0) {}
        Vector2(const T& _x, const T& _y) : x(_x), y(_y) {}
        Vector2(const Vector2& v) : x(v.x), y(v.y) {}
        Vector2& operator=(const Vector2& v) = default;
        
        T       square()                    const;
        T       magnitude()                 const;
        void    normalize();
        Vector2 normalized()                const;
        Vector2 perpendicular()             const;
        T       crossed(const Vector2& rhs) const;
        
        void    rotate (const T& theta);
        void    rotate (const T& theta, const Vector2& origin);
        Vector2 rotated(const T& theta) const;
        Vector2 rotated(const T& theta, const Vector2& origin) const;
        
        Vector2  operator +  (const Vector2& rhs) const;
        Vector2  operator -  (const Vector2& rhs) const;
        Vector2  operator *  (const T& rhs)       const;
        Vector2  operator *  (const Vector2& rhs) const;
        Vector2  operator /  (const T& rhs)       const;
        Vector2  operator /  (const Vector2& rhs) const;
        Vector2& operator += (const Vector2& rhs);
        Vector2& operator -= (const Vector2& rhs);
        Vector2& operator *= (const T& rhs);
        Vector2& operator /= (const T& rhs);
        Vector2  operator +  () const;
        Vector2  operator -  () const;
        
        bool operator == (const Vector2& rhs) const;
        bool operator != (const Vector2& rhs) const;
        
        const std::string str() const;
        
        operator Vector2<int32_t>() const;
        operator Vector2<float>()   const;
        operator Vector2<double>()  const;
    };
    
    template<class T> const Vector2<T> Vector2<T>::ZERO(0, 0);
    template<class T> const Vector2<T> Vector2<T>::X_AXIS(1, 0);
    template<class T> const Vector2<T> Vector2<T>::Y_AXIS(0, 1);
    
    template<class T> T Distance     (const Vector2<T>& lhs, const Vector2<T>& rhs) { return (lhs - rhs).magnitude(); }
    template<class T> T DotProduct   (const Vector2<T>& lhs, const Vector2<T>& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }
    template<class T> T CrossProduct (const Vector2<T>& lhs, const Vector2<T>& rhs) { return lhs.x * rhs.y - lhs.y * rhs.x; }

    template<class T> T          Vector2<T>::square()                       const { return x * x + y * y; }
    template<class T> T          Vector2<T>::magnitude()                    const { return (T)(std::sqrt(x * x + y * y)); }
    template<class T> void       Vector2<T>::normalize()                          { T r = 1 / this->magnitude(); *this /= r; }
    template<class T> Vector2<T> Vector2<T>::normalized()                   const { T r = 1 / this->magnitude(); return { x * r, y * r }; }
    template<class T> Vector2<T> Vector2<T>::perpendicular()                const { return { -y, x }; }
    template<class T> T          Vector2<T>::crossed(const Vector2<T>& rhs) const { return this->x * rhs.y - this->y * rhs.x; }
    
    template<class T> void       Vector2<T>::rotate (const T& theta)
    { T s = sin(theta), c = cos(theta), _x = this->x; this->x = this->x * c - this->_y * s; this->y = _x * s + this->_y * c; }
    template<class T> void       Vector2<T>::rotate (const T& theta, const Vector2& origin)
    { T s = sin(theta), c = cos(theta); *this -= origin; *this = origin + Vector2<T>(this->x * c - this->y * s, this->x * s + this->y * c); }
    template<class T> Vector2<T> Vector2<T>::rotated(const T& theta) const
    { T s = sin(theta), c = cos(theta); return { this->x * c - this->y * s, this->x * s + this->y * c }; }
    template<class T> Vector2<T> Vector2<T>::rotated(const T& theta, const Vector2& origin) const
    { T s = sin(theta), c = cos(theta); Vector2<T> v(*this - origin); return origin + Vector2<T>(v.x * c - v.y * s, v.x * s + v.y * c); }
    
    template<class T> Vector2<T>  Vector2<T>::operator +  (const Vector2<T>& rhs) const { return  { this->x + rhs.x, this->y + rhs.y }; }
    template<class T> Vector2<T>  Vector2<T>::operator -  (const Vector2<T>& rhs) const { return  { this->x - rhs.x, this->y - rhs.y }; }
    template<class T> Vector2<T>  Vector2<T>::operator *  (const T& rhs)          const { return  { this->x * rhs,   this->y * rhs   }; }
    template<class T> Vector2<T>  Vector2<T>::operator *  (const Vector2<T>& rhs) const { return  { this->x * rhs.x, this->y * rhs.y }; }
    template<class T> Vector2<T>  Vector2<T>::operator /  (const T& rhs)          const { return  { this->x / rhs,   this->y / rhs   }; }
    template<class T> Vector2<T>  Vector2<T>::operator /  (const Vector2<T>& rhs) const { return  { this->x / rhs.x, this->y / rhs.y }; }
    template<class T> Vector2<T>& Vector2<T>::operator += (const Vector2<T>& rhs) { this->x += rhs.x; this->y += rhs.y; return *this; }
    template<class T> Vector2<T>& Vector2<T>::operator -= (const Vector2<T>& rhs) { this->x -= rhs.x; this->y -= rhs.y; return *this; }
    template<class T> Vector2<T>& Vector2<T>::operator *= (const T& rhs)          { this->x *= rhs;   this->y *= rhs;   return *this; }
    template<class T> Vector2<T>& Vector2<T>::operator /= (const T& rhs)          { this->x /= rhs;   this->y /= rhs;   return *this; }
    template<class T> Vector2<T>  Vector2<T>::operator +  () const { return { +x, +y }; }
    template<class T> Vector2<T>  Vector2<T>::operator -  () const { return { -x, -y }; }
    
    template<class T> bool Vector2<T>::operator == (const Vector2<T>& rhs) const { return (this->x == rhs.x && this->y == rhs.y); }
    template<class T> bool Vector2<T>::operator != (const Vector2<T>& rhs) const { return (this->x != rhs.x || this->y != rhs.y); }
    
    template<class T> const std::string Vector2<T>::str() const { return std::string("(") + std::to_string(this->x) + "," + std::to_string(this->y) + ")"; }
    template<class T> std::ostream& operator << (std::ostream& os, const Vector2<T>& rhs) { os << rhs.str(); return os; }
    
    template<class T> Vector2<T>::operator Vector2<int32_t>() const { return { static_cast<int32_t>(this->x), static_cast<int32_t>(this->y) }; }
    template<class T> Vector2<T>::operator Vector2<float>()   const { return { static_cast<float>  (this->x), static_cast<float>  (this->y) }; }
    template<class T> Vector2<T>::operator Vector2<double>()  const { return { static_cast<double> (this->x), static_cast<double> (this->y) }; }
    
    template<class T> inline Vector2<T> operator * (const float&  lhs, const Vector2<T>& rhs) { return { (T)(lhs * (float) rhs.x), (T)(lhs * (float) rhs.y) }; }
    template<class T> inline Vector2<T> operator * (const double& lhs, const Vector2<T>& rhs) { return { (T)(lhs * (double)rhs.x), (T)(lhs * (double)rhs.y) }; }
    template<class T> inline Vector2<T> operator * (const int&    lhs, const Vector2<T>& rhs) { return { (T)(lhs * (int)   rhs.x), (T)(lhs * (int)   rhs.y) }; }
    template<class T> inline Vector2<T> operator / (const float&  lhs, const Vector2<T>& rhs) { return { (T)(lhs / (float) rhs.x), (T)(lhs / (float) rhs.y) }; }
    template<class T> inline Vector2<T> operator / (const double& lhs, const Vector2<T>& rhs) { return { (T)(lhs / (double)rhs.x), (T)(lhs / (double)rhs.y) }; }
    template<class T> inline Vector2<T> operator / (const int&    lhs, const Vector2<T>& rhs) { return { (T)(lhs / (int)   rhs.x), (T)(lhs / (int)   rhs.y) }; }

    typedef Vector2<int32_t>  Vector2i;
    typedef Vector2<uint32_t> Vector2u;
    typedef Vector2<float>    Vector2f;
    typedef Vector2<double>   Vector2d;
}




#endif /* Vector2_h */
