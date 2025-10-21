#include <iostream>
#include <cmath>
#include "physics/GravityEngine.h"
#include "physics/PhysicsConstants.h"
#include "physics/Integrator.h"
#include "core/Vector3D.h"

static bool approxEqualDouble(double a, double b, double relTol = 1e-9, double absTol = 1e-12) {
    double diff = std::fabs(a - b);
    if (diff <= absTol) return true;
    double maxAbs = std::fmax(std::fabs(a), std::fabs(b));
    return diff <= relTol * maxAbs;
}

static bool approxEqualVec(const Vector3D& a, const Vector3D& b, double relTol = 1e-9, double absTol = 1e-12) {
    return approxEqualDouble(a.x, b.x, relTol, absTol) &&
           approxEqualDouble(a.y, b.y, relTol, absTol) &&
           approxEqualDouble(a.z, b.z, relTol, absTol);
}

#define ASSERT(cond, msg) \
    do { if (!(cond)) { std::cerr << "ASSERT FAILED: " << msg << " (" << __FILE__ << ":" << __LINE__ << ")\n"; return 1; } } while(0)

int test_calculateGravitationalForce_basic() {
    Vector3D p1(0,0,0);
    Vector3D p2(1,0,0);
    double m1 = 1.0;
    double m2 = 1.0;
    Vector3D f = Physics::GravityEngine::calculateGravitationalForce(p1, m1, p2, m2);
    double expectedMag = PhysicsConstants::G * m1 * m2 / (1.0 * 1.0);
    Vector3D expected(expectedMag, 0, 0);
    ASSERT(approxEqualVec(f, expected), "Gravitational force basic value mismatch");
    return 0;
}

int test_calculateGravitationalForce_samePosition_returnsZero() {
    Vector3D p(1.0, 2.0, -3.0);
    double m = 5.0;
    Vector3D f = Physics::GravityEngine::calculateGravitationalForce(p, m, p, m);
    ASSERT(approxEqualVec(f, Vector3D::zero()), "Force for identical positions should be zero");
    return 0;
}

int test_calculateNetForce_two_bodies_matches_pairwise() {
    std::vector<Vector3D> positions = { Vector3D(0,0,0), Vector3D(2,0,0) };
    std::vector<double> masses = { 3.0, 4.0 };
    Vector3D net0 = Physics::GravityEngine::calculateNetForce(positions, masses, 0);
    Vector3D pair = Physics::GravityEngine::calculateGravitationalForce(positions[0], masses[0], positions[1], masses[1]);
    ASSERT(approxEqualVec(net0, pair), "Net force (two bodies) should equal pairwise force");
    return 0;
}

int test_calculateNetForce_three_body_symmetry_zero() {
    double d = 5.0;
    std::vector<Vector3D> positions = { Vector3D(0,0,0), Vector3D(-d,0,0), Vector3D(d,0,0) };
    std::vector<double> masses = { 2.0, 3.0, 3.0 };
    Vector3D net0 = Physics::GravityEngine::calculateNetForce(positions, masses, 0);
    ASSERT(approxEqualVec(net0, Vector3D::zero()), "Symmetric three-body net force should be zero on center mass");
    return 0;
}

int test_calculateTotalEnergy_two_body_static() {
    double d = 10.0;
    std::vector<Vector3D> positions = { Vector3D(0,0,0), Vector3D(d,0,0) };
    std::vector<Vector3D> velocities = { Vector3D::zero(), Vector3D::zero() };
    std::vector<double> masses = { 2.0, 3.0 };
    double E = Physics::GravityEngine::calculateTotalEnergy(positions, velocities, masses);
    double expectedPotential = -PhysicsConstants::G * masses[0] * masses[1] / d;
    ASSERT(approxEqualDouble(E, expectedPotential), "Total energy (static two-body) mismatch");
    return 0;
}

int test_calculateTotalMomentum() {
    std::vector<Vector3D> velocities = { Vector3D(1,2,3), Vector3D(-1, 0.5, 0) };
    std::vector<double> masses = { 2.0, 4.0 };
    Vector3D total = Physics::GravityEngine::calculateTotalMomentum(velocities, masses);
    Vector3D expected = velocities[0] * masses[0] + velocities[1] * masses[1];
    ASSERT(approxEqualVec(total, expected), "Total momentum mismatch");
    return 0;
}

int test_calculateGravitationalDerivatives_basic() {
    using namespace Physics;
    size_t n = 2;
    SystemState state(n), derivatives(n);
    state.positions[0] = Vector3D(0,0,0);
    state.positions[1] = Vector3D(3,0,0);
    state.velocities[0] = Vector3D(0.1, 0.0, 0.0);
    state.velocities[1] = Vector3D(-0.2, 0.0, 0.0);
    state.time = 0.0;

    GravityEngine::calculateGravitationalDerivatives(state, derivatives);

    // positions derivative equals velocities
    ASSERT(approxEqualVec(derivatives.positions[0], state.velocities[0]), "Derivative position != velocity for body 0");
    ASSERT(approxEqualVec(derivatives.positions[1], state.velocities[1]), "Derivative position != velocity for body 1");

    // time derivative is 1.0
    ASSERT(approxEqualDouble(derivatives.time, 1.0), "Time derivative should be 1.0");

    // velocity derivative equals netForce / SOLAR_MASS (GravityEngine uses SOLAR_MASS locally)
    std::vector<double> masses(n, PhysicsConstants::SOLAR_MASS);
    Vector3D expectedNet0 = GravityEngine::calculateNetForce(state.positions, masses, 0);
    Vector3D expectedAcc0 = expectedNet0 / PhysicsConstants::SOLAR_MASS;
    ASSERT(approxEqualVec(derivatives.velocities[0], expectedAcc0, 1e-8), "Acceleration mismatch for body 0");

    return 0;
}

int main() {
    struct Test { const char* name; int(*func)(); };
    Test tests[] = {
        {"calculateGravitationalForce_basic", test_calculateGravitationalForce_basic},
        {"calculateGravitationalForce_samePosition", test_calculateGravitationalForce_samePosition_returnsZero},
        {"calculateNetForce_two_bodies", test_calculateNetForce_two_bodies_matches_pairwise},
        {"calculateNetForce_three_body_symmetry", test_calculateNetForce_three_body_symmetry_zero},
        {"calculateTotalEnergy_two_body_static", test_calculateTotalEnergy_two_body_static},
        {"calculateTotalMomentum", test_calculateTotalMomentum},
        {"calculateGravitationalDerivatives_basic", test_calculateGravitationalDerivatives_basic}
    };

    int failed = 0;
    for (auto &t : tests) {
        std::cout << "[ RUN      ] " << t.name << std::endl;
        int r = t.func();
        if (r == 0) {
            std::cout << "[       OK ] " << t.name << std::endl;
        } else {
            std::cout << "[  FAILED  ] " << t.name << std::endl;
            ++failed;
        }
    }

    if (failed == 0) {
        std::cout << "ALL TESTS PASSED\n";
        return 0;
    } else {
        std::cerr << failed << " test(s) failed\n";
        return 1;
    }
}