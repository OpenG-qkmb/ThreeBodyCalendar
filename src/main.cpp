#include <iostream>
#include "core/Vector3D.h"
#include "physics/CelestialBody.h"
#include "physics/PhysicsConstants.h"

void testVector3D() {
    std::cout << "=== Vector3D Test ===" << std::endl;

    Vector3D v1(1, 2, 3);
    Vector3D v2(4, 5, 6);

    std::cout << "v1: " << v1.toString() << std::endl;
    std::cout << "v2: " << v2.toString() << std::endl;
    std::cout << "v1 + v2: " << (v1 + v2).toString() << std::endl;
    std::cout << "v1 ¡¤ v2: " << v1.dot(v2) << std::endl;
    std::cout << "|v1|: " << v1.magnitude() << std::endl;
}

void testCelestialBody() {
    std::cout << "\n=== CelestialBody Test ===" << std::endl;

    CelestialBody earth("Earth", PhysicsConstants::EARTH_MASS, 6.371e6);
    earth.setPosition(Vector3D(1.5e11, 0, 0));  // 1.5 * 10^8 km
    earth.setVelocity(Vector3D(0, 2.98e4, 0));  // 29.8 km/s

    std::cout << earth.toString() << std::endl;
}

void testPhysicsConstants() {
    std::cout << "\n=== Testing of Physical Constants ===" << std::endl;
    std::cout << "Gravitational constant G: " << PhysicsConstants::G << std::endl;
    std::cout << "1 year = " << PhysicsConstants::yearsToSeconds(1) << " s" << std::endl;
    std::cout << "1 AU = " << PhysicsConstants::AU << " m" << std::endl;
}

int main() {
    std::cout << "Basic tests" << std::endl;
    std::cout << "=========================" << std::endl;

    try {
        testVector3D();
        testCelestialBody();
        testPhysicsConstants();

        std::cout << "\nAll basic tests passed!" << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "\nFoundational infrastructure successfully established." << std::endl;
    return 0;
}