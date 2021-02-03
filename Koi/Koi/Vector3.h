//
//  Vector3.h
//  Koi
//
//  Created by Michael Schuff on 2/2/21.
//

#ifndef Vector3_h
#define Vector3_h

#include <math.h>

namespace koi {
    template<class T>
    struct Quaternion;
    
    template<class T>
    struct Vector3 {
        static const Vector3 ZERO, X_AXIS, Y_AXIS, Z_AXIS;
        
        
        T x = 0, y = 0, z = 0;
        Vector3() : x(0), y(0), z(0) {}
        Vector3(const T& _x, const T& _y, const T& _z) : x(_x), y(_y), z(_z) {}
        Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
        Vector3& operator=(const Vector3& v) = default;
        
        T       magnitude()                 const;
        T       square()                    const;
        void    normalize();
        Vector3 normalized()                const;
        Vector3 orthogonal()                const;
        T       crossed(const Vector3& rhs) const;
        
        void    rotate (const Quaternion<T>& q);
        Vector3 rotated(const Quaternion<T>& q) const;
        void    rotate (const Vector3& axis,   const T& theta);
        Vector3 rotated(const Vector3& axis,   const T& theta) const;
        void    rotate (const Vector3& origin, const Vector3& axis, const T& theta);
        Vector3 rotated(const Vector3& origin, const Vector3& axis, const T& theta) const;
        
        Quaternion<T> operator +  (const T& rhs)       const;
        Vector3       operator +  (const Vector3& rhs) const;
        Vector3       operator -  (const Vector3& rhs) const;
        Vector3       operator *  (const T& rhs)       const;
        Vector3       operator *  (const Vector3& rhs) const;
        Vector3       operator /  (const T& rhs)       const;
        Vector3       operator /  (const Vector3& rhs) const;
        Vector3&      operator += (const Vector3& rhs);
        Vector3&      operator -= (const Vector3& rhs);
        Vector3&      operator *= (const T& rhs);
        Vector3&      operator /= (const T& rhs);
        Vector3       operator +  () const;
        Vector3       operator -  () const;
        
        bool operator == (const Vector3& rhs) const;
        bool operator != (const Vector3& rhs) const;
        
        const  std::string str() const;
        friend std::ostream& operator << (std::ostream& os, const Vector3& rhs) { os << rhs.str(); return os; }
        
        operator Vector3<int32_t>() const;
        operator Vector3<float>()   const;
        operator Vector3<double>()  const;
        
        
    };
    
    template<class T> Quaternion<T> operator + (const T& k, const Vector3<T>& v);
    
    template<class T> const Vector3<T> Vector3<T>::ZERO(0, 0, 0);
    template<class T> const Vector3<T> Vector3<T>::X_AXIS(1, 0, 0);
    template<class T> const Vector3<T> Vector3<T>::Y_AXIS(0, 1, 0);
    template<class T> const Vector3<T> Vector3<T>::Z_AXIS(0, 0, 1);
    
    template<class T> T          Distance    (const Vector3<T>& lhs, const Vector3<T>& rhs) { return (lhs - rhs).magnitude(); }
    template<class T> T          DotProduct  (const Vector3<T>& lhs, const Vector3<T>& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }
    template<class T> Vector3<T> CrossProduct(const Vector3<T>& lhs, const Vector3<T>& rhs)
    { return { lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x }; }
    
    template<class T> T          Vector3<T>::magnitude()  const { return (T)(std::sqrt(x * x + y * y + z * z)); }
    template<class T> T          Vector3<T>::square()     const { return x * x + y * y + z * z; }
    template<class T> void       Vector3<T>::normalize()        { T r = 1 / magnitude(); *this *= r; }
    template<class T> Vector3<T> Vector3<T>::normalized() const { T r = 1 / magnitude(); return *this * r; }
    template<class T> Vector3<T> Vector3<T>::orthogonal() const
    { T ax = abs(this->x), ay = abs(this->y), az = abs(this->z); return CrossProduct(*this, ax < ay ? (ax < az ? X_AXIS : Z_AXIS) : (ay < az ? Y_AXIS : Z_AXIS)); }
    template<class T> T          Vector3<T>::crossed(const Vector3<T>& rhs) const
    { return { this->y * rhs.z - this->z * rhs.y, this->z * rhs.x - this->x * rhs.z, this->x * rhs.y - this->y * rhs.x }; }
    
    template<class T> Vector3<T>  Vector3<T>::operator +  (const Vector3<T>& rhs) const { return { this->x + rhs.x, this->y + rhs.y, this->z + rhs.z }; }
    template<class T> Vector3<T>  Vector3<T>::operator -  (const Vector3<T>& rhs) const { return { this->x - rhs.x, this->y - rhs.y, this->z - rhs.z }; }
    template<class T> Vector3<T>  Vector3<T>::operator *  (const T& rhs)          const { return { this->x * rhs,   this->y * rhs,   this->z * rhs   }; }
    template<class T> Vector3<T>  Vector3<T>::operator *  (const Vector3<T>& rhs) const { return { this->x * rhs.x, this->y * rhs.y, this->z * rhs.y }; }
    template<class T> Vector3<T>  Vector3<T>::operator /  (const T& rhs)          const { return { this->x / rhs,   this->y / rhs,   this->z / rhs   }; }
    template<class T> Vector3<T>  Vector3<T>::operator /  (const Vector3<T>& rhs) const { return { this->x / rhs.x, this->y / rhs.y, this->z / rhs.y }; }
    template<class T> Vector3<T>& Vector3<T>::operator += (const Vector3<T>& rhs) { this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; return *this; }
    template<class T> Vector3<T>& Vector3<T>::operator -= (const Vector3<T>& rhs) { this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; return *this; }
    template<class T> Vector3<T>& Vector3<T>::operator *= (const T& rhs)          { this->x *= rhs;   this->y *= rhs;   this->z *= rhs;   return *this; }
    template<class T> Vector3<T>& Vector3<T>::operator /= (const T& rhs)          { this->x /= rhs;   this->y /= rhs;   this->z /= rhs;   return *this; }
    template<class T> Vector3<T>  Vector3<T>::operator +  () const { return { +x, +y, +z }; }
    template<class T> Vector3<T>  Vector3<T>::operator -  () const { return { -x, -y, -z }; }
    
    template<class T> bool Vector3<T>::operator == (const Vector3<T>& rhs) const { return (this->x == rhs.x && this->y == rhs.y && this->z == rhs.z); }
    template<class T> bool Vector3<T>::operator != (const Vector3<T>& rhs) const { return (this->x != rhs.x || this->y != rhs.y || this->z != rhs.z); }
    
    template<class T> const std::string Vector3<T>::str() const
    { return "(" + std::to_string(this->x) + ","  + std::to_string(this->y) + ","  + std::to_string(this->z) + ")"; }
    
    template<class T> Vector3<T>::operator Vector3<int32_t>() const
    { return { static_cast<int32_t>(this->x), static_cast<int32_t>(this->y), static_cast<int32_t>(this->z) }; }
    template<class T> Vector3<T>::operator Vector3<float>()   const
    { return { static_cast<float>  (this->x), static_cast<float>  (this->y), static_cast<float>  (this->z) }; }
    template<class T> Vector3<T>::operator Vector3<double>()  const
    { return { static_cast<double> (this->x), static_cast<double> (this->y), static_cast<double> (this->z) }; }
    
    template<class T> inline Vector3<T> operator * (const float&  lhs, const Vector3<T>& rhs)
    { return { (T)(lhs * (float) rhs.x), (T)(lhs * (float) rhs.y), (T)(lhs * (float) rhs.z) }; }
    template<class T> inline Vector3<T> operator * (const double& lhs, const Vector3<T>& rhs)
    { return { (T)(lhs * (double)rhs.x), (T)(lhs * (double)rhs.y), (T)(lhs * (double)rhs.z) }; }
    template<class T> inline Vector3<T> operator * (const int&    lhs, const Vector3<T>& rhs)
    { return { (T)(lhs * (int)   rhs.x), (T)(lhs * (int)   rhs.y), (T)(lhs * (int)   rhs.z) }; }
    template<class T> inline Vector3<T> operator / (const float&  lhs, const Vector3<T>& rhs)
    { return { (T)(lhs / (float) rhs.x), (T)(lhs / (float) rhs.y), (T)(lhs / (float) rhs.z) }; }
    template<class T> inline Vector3<T> operator / (const double& lhs, const Vector3<T>& rhs)
    { return { (T)(lhs / (double)rhs.x), (T)(lhs / (double)rhs.y), (T)(lhs / (double)rhs.z) }; }
    template<class T> inline Vector3<T> operator / (const int&    lhs, const Vector3<T>& rhs)
    { return { (T)(lhs / (int)   rhs.x), (T)(lhs / (int)   rhs.y), (T)(lhs / (int)   rhs.z) }; }

    typedef Vector3<int32_t>  Vector3i;
    typedef Vector3<uint32_t> Vector3u;
    typedef Vector3<float>    Vector3f;
    typedef Vector3<double>   Vector3d;
}

#endif /* Vector3_h */
