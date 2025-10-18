#ifndef _INCLUDE_CORE_VECTOR3D_H_
#define _INCLUDE_CORE_VECTOR3D_H_
#include "core/Vector3D.h"
#endif

#ifndef _INCLUDE_STRING_
#define _INCLUDE_STRING_
#include <string>
#endif

#pragma once

#ifndef _CELESTIALBODY_H_
#define _CELESTIALBODY_H_

class CelestialBody {
protected:
    std::string name;
    double mass;           // 质量 (kg)
    double radius;         // 半径 (m)
    Vector3D position;     // 位置 (m)
    Vector3D velocity;     // 速度 (m/s)
    Vector3D acceleration; // 加速度 (m/s²)

public:
    CelestialBody(const std::string& name, double mass, double radius);
    virtual ~CelestialBody() = default;

    // 状态更新
    virtual void updatePosition(double dt);
    virtual void updateVelocity(double dt);

    // Getter/Setter
    std::string getName() const { return name; }
    double getMass() const { return mass; }
    double getRadius() const { return radius; }
    Vector3D getPosition() const { return position; }
    Vector3D getVelocity() const { return velocity; }
    Vector3D getAcceleration() const { return acceleration; }

    void setPosition(const Vector3D& pos) { position = pos; }
    void setVelocity(const Vector3D& vel) { velocity = vel; }
    void setAcceleration(const Vector3D& acc) { acceleration = acc; }

    // 实用函数
    virtual std::string toString() const;
};

#endif