#include "physics/GravityEngine.h"
#include <cmath>
#include <iostream>

namespace Physics {

    void GravityEngine::calculateGravitationalDerivatives(const SystemState& state, SystemState& derivatives) {
        size_t numBodies = state.positions.size();

        // 位置导数就是速度：dr/dt = v
        for (size_t i = 0; i < numBodies; ++i) {
            derivatives.positions[i] = state.velocities[i];
        }

        // 速度导数就是加速度：dv/dt = a = F/m
        // 我们需要质量信息，这里假设每个天体质量相同（后续会改进）
        std::vector<double> masses(numBodies, PhysicsConstants::SOLAR_MASS); // 临时使用太阳质量

        for (size_t i = 0; i < numBodies; ++i) {
            Vector3D netForce = calculateNetForce(state.positions, masses, i);
            derivatives.velocities[i] = netForce / masses[i];
        }

        derivatives.time = 1.0; // 时间导数总是1
    }

    Vector3D GravityEngine::calculateGravitationalForce(const Vector3D& pos1, double mass1,
        const Vector3D& pos2, double mass2) {
        Vector3D r = pos2 - pos1;
        double distance = r.magnitude();

        // 避免除零错误
        if (distance < 1e-10) {
            return Vector3D::zero();
        }

        // 万有引力公式: F = G * m1 * m2 / r^2
        double forceMagnitude = PhysicsConstants::G * mass1 * mass2 / (distance * distance);
        return r.normalized() * forceMagnitude;
    }

    Vector3D GravityEngine::calculateNetForce(const std::vector<Vector3D>& positions,
        const std::vector<double>& masses,
        size_t targetIndex) {
        Vector3D netForce(0, 0, 0);
        size_t numBodies = positions.size();

        for (size_t i = 0; i < numBodies; ++i) {
            if (i == targetIndex) continue; // 跳过自身

            Vector3D force = calculateGravitationalForce(
                positions[targetIndex], masses[targetIndex],
                positions[i], masses[i]
            );

            netForce = netForce + force;
        }

        return netForce;
    }

    double GravityEngine::calculateTotalEnergy(const std::vector<Vector3D>& positions,
        const std::vector<Vector3D>& velocities,
        const std::vector<double>& masses) {
        double kineticEnergy = 0.0;
        double potentialEnergy = 0.0;
        size_t numBodies = positions.size();

        // 计算动能: K = 1/2 * m * v^2
        for (size_t i = 0; i < numBodies; ++i) {
            kineticEnergy += 0.5 * masses[i] * velocities[i].magnitudeSquared();
        }

        // 计算势能: U = -G * m_i * m_j / r_ij (对所有i<j求和)
        for (size_t i = 0; i < numBodies; ++i) {
            for (size_t j = i + 1; j < numBodies; ++j) {
                double distance = (positions[i] - positions[j]).magnitude();
                if (distance > 1e-10) { // 避免除零
                    potentialEnergy -= PhysicsConstants::G * masses[i] * masses[j] / distance;
                }
            }
        }

        return kineticEnergy + potentialEnergy;
    }

    Vector3D GravityEngine::calculateTotalMomentum(const std::vector<Vector3D>& velocities,
        const std::vector<double>& masses) {
        Vector3D totalMomentum(0, 0, 0);
        size_t numBodies = velocities.size();

        for (size_t i = 0; i < numBodies; ++i) {
            totalMomentum = totalMomentum + velocities[i] * masses[i];
        }

        return totalMomentum;
    }

} // namespace Physics