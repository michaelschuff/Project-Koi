//
//  Quaternion.h
//  Koi
//
//  Created by Michael Schuff on 2/2/21.
//

#ifndef Quaternion_h
#define Quaternion_h

#include "math.h"
#include "Vector3.h"

namespace koi {
    template<class T>
    struct Quaternion {
        T w = 0, x = 0, y = 0, z = 0;
        Quaternion() : w(1), x(0), y(0), z(0) {}
        Quaternion(const T& _w, const T& _x, const T& _y, const T& _z) : w(_w), x(_x), y(_y), z(_z) {}
        Quaternion(const T& _w, const Vector3<T>& v) : w(_w), x(v.x), y(v.y), z(v.z) {}
        Quaternion(const Vector3<T>& v) : w(0), x(v.x), y(v.y), z(v.z) {}
        Quaternion(const Quaternion& q) : w(q.w), x(q.x), y(q.y), z(q.z) {}
        Quaternion& operator=(const Quaternion& q) = default;
        
        Vector3<T>  v()          const;
        T           norm()       const;
        T           magnitude()  const;
        T           square()     const;
        void        normalize();
        Quaternion  normalized() const;
        Quaternion  conjugate()  const;
        Quaternion  reciprocal() const;
        
        Quaternion  operator +  (const Quaternion& rhs) const;
        Quaternion  operator -  (const Quaternion& rhs) const;
        Quaternion  operator *  (const T& rhs)          const;
        Quaternion  operator *  (const Quaternion& rhs) const;
        Quaternion  operator /  (const T& rhs)          const;
        Quaternion  operator /  (const Quaternion& rhs) const;
        Quaternion& operator += (const Quaternion& rhs);
        Quaternion& operator -= (const Quaternion& rhs);
        Quaternion& operator *= (const T& rhs);
        Quaternion& operator /= (const T& rhs);
        Quaternion  operator +  () const;
        Quaternion  operator -  () const;
        
        bool operator == (const Quaternion& rhs) const;
        bool operator != (const Quaternion& rhs) const;
        
        const  std::string str() const;
        friend std::ostream& operator << (std::ostream& os, const Quaternion& rhs) { os << rhs.str(); return os; }
        
        operator Quaternion<int32_t>() const;
        operator Quaternion<float>()   const;
        operator Quaternion<double>()  const;
        
        
        static const Quaternion ZERO, IDENTITY, X_180, Y_180, Z_180;
    };
    
    template<class T> const Quaternion<T> Quaternion<T>::ZERO(0, 0, 0, 0);
    template<class T> const Quaternion<T> Quaternion<T>::IDENTITY(1, 0, 0, 0);
    template<class T> const Quaternion<T> Quaternion<T>::X_180(0, 1, 0, 0);
    template<class T> const Quaternion<T> Quaternion<T>::Y_180(0, 0, 1, 0);
    template<class T> const Quaternion<T> Quaternion<T>::Z_180(0, 0, 0, 1);
    
    template<class T> Quaternion<T> GetQuaternion(const Vector3<T>& axis, const T& theta) { return Quaternion<T>(cos(theta/2), sin(theta/2) * axis.normalized()).normalized(); }
    template<class T> Quaternion<T> GetQuaternion(const Vector3<T>& start, const Vector3<T>& end) {
        T k_cos_theta = dot(start, end);
        T k = start.square() * end.square();
        if (k_cos_theta == -k) return Quaternion<T>(0, start.orthogonal());
        return Quaternion<T>(k_cos_theta + k, CrossProduct(start, end)).normalized();
    }

    
    template<class T> Vector3<T>    Quaternion<T>::v()          const { return { x, y, z }; }
    template<class T> T             Quaternion<T>::norm()       const { return this->magnitude(); }
    template<class T> T             Quaternion<T>::magnitude()  const { return (T)(std::sqrt(w * w + x * x + y * y + z * z)); }
    template<class T> T             Quaternion<T>::square()     const { return x * x + y * y + z * z; }
    template<class T> void          Quaternion<T>::normalize()        { T r = 1 / magnitude(); *this *= r; }
    template<class T> Quaternion<T> Quaternion<T>::normalized() const { T r = 1 / magnitude(); *this * r; }
    template<class T> Quaternion<T> Quaternion<T>::conjugate()  const { return { this->w, -this->x, -this->y, -this->z }; }
    template<class T> Quaternion<T> Quaternion<T>::reciprocal() const { return conjugate() / square(); }
    
    template<class T> Quaternion<T>  Quaternion<T>::operator +  (const Quaternion<T>& rhs) const
    { return { this->w + rhs.w, this->x + rhs.x, this->y + rhs.y, this->z + rhs.z }; }
    template<class T> Quaternion<T>  Quaternion<T>::operator -  (const Quaternion<T>& rhs) const
    { return { this->w - rhs.w, this->x - rhs.x, this->y - rhs.y, this->z - rhs.z }; }
    template<class T> Quaternion<T>  Quaternion<T>::operator *  (const T& rhs)             const
    { return { this->w * rhs,   this->x * rhs,   this->y * rhs,   this->z * rhs   }; }
    template<class T> Quaternion<T>  Quaternion<T>::operator *  (const Quaternion<T>& rhs) const
    { return { this->w * rhs.w - this->x * rhs.x - this->y * rhs.y - this->z * rhs.z,
               this->w * rhs.x + this->x * rhs.w + this->y * rhs.z - this->z * rhs.y,
               this->w * rhs.y - this->x * rhs.z + this->y * rhs.w + this->z * rhs.x,
               this->w * rhs.z + this->x * rhs.y - this->y * rhs.x + this->z * rhs.w }; }
    template<class T> Quaternion<T>  Quaternion<T>::operator /  (const T& rhs)             const
    { return { this->w / rhs,   this->x / rhs,   this->y / rhs,   this->z / rhs   }; }
    template<class T> Quaternion<T>  Quaternion<T>::operator /  (const Quaternion<T>& rhs) const
    { return { this->w / rhs.w, this->x / rhs.x, this->y / rhs.y, this->z / rhs.y }; }
    template<class T> Quaternion<T>& Quaternion<T>::operator += (const Quaternion<T>& rhs)
    { this->w += rhs.w; this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; return *this; }
    template<class T> Quaternion<T>& Quaternion<T>::operator -= (const Quaternion<T>& rhs)
    { this->w -= rhs.w; this->x -= rhs.x; this->y -= rhs.y; this->z -= rhs.z; return *this; }
    template<class T> Quaternion<T>& Quaternion<T>::operator *= (const T& rhs) { this->w *= rhs; this->x *= rhs; this->y *= rhs; this->z *= rhs; return *this; }
    template<class T> Quaternion<T>& Quaternion<T>::operator /= (const T& rhs) { this->w /= rhs; this->x /= rhs; this->y /= rhs; this->z /= rhs; return *this; }
    template<class T> Quaternion<T>  Quaternion<T>::operator +  () const { return { +w, +x, +y, +z }; }
    template<class T> Quaternion<T>  Quaternion<T>::operator -  () const { return { -w, -x, -y, -z }; }
    
    template<class T> bool Quaternion<T>::operator == (const Quaternion<T>& rhs) const { return (this->w == rhs.w && this->x == rhs.x && this->y == rhs.y && this->z == rhs.z); }
    template<class T> bool Quaternion<T>::operator != (const Quaternion<T>& rhs) const { return (this->w != rhs.w || this->x != rhs.x || this->y != rhs.y || this->z != rhs.z); }
    
    template<class T> const std::string Quaternion<T>::str() const
    { return "(" + std::to_string(this->w) + "," + std::to_string(this->x) + "," + std::to_string(this->y) + "," + std::to_string(this->z) + ")"; }
    
    template<class T> Quaternion<T>::operator Quaternion<int32_t>() const
    { return { static_cast<int32_t>(this->w), static_cast<int32_t>(this->x), static_cast<int32_t>(this->y), static_cast<int32_t>(this->z) }; }
    template<class T> Quaternion<T>::operator Quaternion<float>()   const
    { return { static_cast<float>  (this->w), static_cast<float>  (this->x), static_cast<float>  (this->y), static_cast<float>  (this->z) }; }
    template<class T> Quaternion<T>::operator Quaternion<double>() const
    { return { static_cast<double> (this->w), static_cast<double> (this->x), static_cast<double> (this->y), static_cast<double> (this->z) }; }
    
    template<class T> inline Quaternion<T> operator * (const float&  lhs, const Quaternion<T>& rhs)
    { return { (T)(lhs * (float) rhs.x), (T)(lhs * (float) rhs.y), (T)(lhs * (float) rhs.z) }; }
    template<class T> inline Quaternion<T> operator * (const double& lhs, const Quaternion<T>& rhs)
    { return { (T)(lhs * (double)rhs.x), (T)(lhs * (double)rhs.y), (T)(lhs * (double)rhs.z) }; }
    template<class T> inline Quaternion<T> operator * (const int&    lhs, const Quaternion<T>& rhs)
    { return { (T)(lhs * (int)   rhs.x), (T)(lhs * (int)   rhs.y), (T)(lhs * (int)   rhs.z) }; }
    template<class T> inline Quaternion<T> operator / (const float&  lhs, const Quaternion<T>& rhs)
    { return { (T)(lhs / (float) rhs.x), (T)(lhs / (float) rhs.y), (T)(lhs / (float) rhs.z) }; }
    template<class T> inline Quaternion<T> operator / (const double& lhs, const Quaternion<T>& rhs)
    { return { (T)(lhs / (double)rhs.x), (T)(lhs / (double)rhs.y), (T)(lhs / (double)rhs.z) }; }
    template<class T> inline Quaternion<T> operator / (const int&    lhs, const Quaternion<T>& rhs)
    { return { (T)(lhs / (int)   rhs.x), (T)(lhs / (int)   rhs.y), (T)(lhs / (int)   rhs.z) }; }

    typedef Quaternion<int32_t>  Quaternioni;
    typedef Quaternion<uint32_t> Quaternionu;
    typedef Quaternion<float>    Quaternionf;
    typedef Quaternion<double>   Quaterniond;
    
    
    
    template<class T> Quaternion<T> Vector3<T>::operator + (const T& k) const { return { k, *this }; }
    template<class T> Quaternion<T> operator + (const T& k, const Vector3<T>& v) { return { k, v }; }
    
    template<class T> void       Vector3<T>::rotate (const Quaternion<T>& q)                                           { *this = (q * (0 + *this) * q.conjugate()).v(); }
    template<class T> void       Vector3<T>::rotate (const Vector3& axis,   const T& theta)                            { rotate(GetQuaternion(axis, theta)); }
    template<class T> void       Vector3<T>::rotate (const Vector3& origin, const Vector3& axis, const T& theta)       { *this = origin + (*this - origin).rotated(axis, theta); }
    template<class T> Vector3<T> Vector3<T>::rotated(const Quaternion<T>& q)                                     const { return (q * (0 + *this) * q.conjugate()).v(); }
    template<class T> Vector3<T> Vector3<T>::rotated(const Vector3& axis,   const T& theta)                      const { return rotated(GetQuaternion(axis, theta)); }
    template<class T> Vector3<T> Vector3<T>::rotated(const Vector3& origin, const Vector3& axis, const T& theta) const { return origin + (*this - origin).rotated(axis, theta); }

}

#endif /* Quaternion_h */
