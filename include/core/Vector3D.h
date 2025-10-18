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

    // ���캯��
    Vector3D(double x = 0.0, double y = 0.0, double z = 0.0);

    // ��������
    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;
    Vector3D operator*(double scalar) const;
    Vector3D operator/(double scalar) const;

    // ��������
    double dot(const Vector3D& other) const;
    Vector3D cross(const Vector3D& other) const;
    double magnitude() const;
    double magnitudeSquared() const;
    Vector3D normalized() const;

    // ʵ�ú���
    double distanceTo(const Vector3D& other) const;
    static Vector3D zero();
    static Vector3D one();

    // �ַ�����ʾ
    std::string toString() const;
};

#endif