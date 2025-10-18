#include "physics/CelestialBody.h"
#include <sstream>

CelestialBody::CelestialBody(const std::string& name, double mass, double radius)
    : name(name), mass(mass), radius(radius),
    position(Vector3D::zero()), velocity(Vector3D::zero()), acceleration(Vector3D::zero()) {
}

void CelestialBody::updatePosition(double dt) {
    position = position + velocity * dt;
}

void CelestialBody::updateVelocity(double dt) {
    velocity = velocity + acceleration * dt;
}

std::string CelestialBody::toString() const {
    std::stringstream ss;
    ss << name << " [M=" << mass << ", R=" << radius
        << ", Pos=" << position.toString()
        << ", Vel=" << velocity.toString() << "]";
    return ss.str();
}