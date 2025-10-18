#include "core/Vector3D.h"
#include <cmath>
#include <sstream>

Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

Vector3D Vector3D::operator+(const Vector3D& other) const {
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D& other) const {
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D Vector3D::operator*(double scalar) const {
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D Vector3D::operator/(double scalar) const {
    if (scalar == 0.0) return *this;
    return Vector3D(x / scalar, y / scalar, z / scalar);
}

double Vector3D::dot(const Vector3D& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vector3D Vector3D::cross(const Vector3D& other) const {
    return Vector3D(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

double Vector3D::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

double Vector3D::magnitudeSquared() const {
    return x * x + y * y + z * z;
}

Vector3D Vector3D::normalized() const {
    double mag = magnitude();
    if (mag == 0.0) return Vector3D(0, 0, 0);
    return *this * (1.0 / mag);
}

double Vector3D::distanceTo(const Vector3D& other) const {
    return (*this - other).magnitude();
}

Vector3D Vector3D::zero() {
    return Vector3D(0, 0, 0);
}

Vector3D Vector3D::one() {
    return Vector3D(1, 1, 1);
}

std::string Vector3D::toString() const {
    std::stringstream ss;
    ss << "(" << x << ", " << y << ", " << z << ")";
    return ss.str();
}