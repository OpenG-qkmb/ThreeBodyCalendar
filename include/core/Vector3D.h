#ifndef __INCLUDE_STRING_
#define __INCLUDE_STRING_
#include <string>
#endif

#pragma once

#ifndef _VECTOR3D_H_
#define _VECTOR3D_H_


class Vector3D {
public:
    double x, y, z;

    // 构造函数
    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0);

    // 基础运算
    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;
    Vector3D operator*(double scalar) const;
    Vector3D operator/(double scalar) const;

    // 向量运算
    double dot(const Vector3D& other) const;
    Vector3D cross(const Vector3D& other) const;
    double magnitude() const;
    double magnitudeSquared() const;
    Vector3D normalized() const;

    // 实用函数
    double distanceTo(const Vector3D& other) const;
    static Vector3D zero();
    static Vector3D one();

    // 字符串表示
    std::string toString() const;
};

#endif