#include "physics/GravityEngine.h"
#include <cmath>
#include <iostream>

namespace Physics {

    void GravityEngine::calculateGravitationalDerivatives(const SystemState& state, SystemState& derivatives) {
        size_t numBodies = state.positions.size();

        // λ�õ��������ٶȣ�dr/dt = v
        for (size_t i = 0; i < numBodies; ++i) {
            derivatives.positions[i] = state.velocities[i];
        }

        // �ٶȵ������Ǽ��ٶȣ�dv/dt = a = F/m
        // ������Ҫ������Ϣ���������ÿ������������ͬ��������Ľ���
        std::vector<double> masses(numBodies, PhysicsConstants::SOLAR_MASS); // ��ʱʹ��̫������

        for (size_t i = 0; i < numBodies; ++i) {
            Vector3D netForce = calculateNetForce(state.positions, masses, i);
            derivatives.velocities[i] = netForce / masses[i];
        }

        derivatives.time = 1.0; // ʱ�䵼������1
    }

    Vector3D GravityEngine::calculateGravitationalForce(const Vector3D& pos1, double mass1,
        const Vector3D& pos2, double mass2) {
        Vector3D r = pos2 - pos1;
        double distance = r.magnitude();

        // ����������
        if (distance < 1e-10) {
            return Vector3D::zero();
        }

        // ����������ʽ: F = G * m1 * m2 / r^2
        double forceMagnitude = PhysicsConstants::G * mass1 * mass2 / (distance * distance);
        return r.normalized() * forceMagnitude;
    }

    Vector3D GravityEngine::calculateNetForce(const std::vector<Vector3D>& positions,
        const std::vector<double>& masses,
        size_t targetIndex) {
        Vector3D netForce(0, 0, 0);
        size_t numBodies = positions.size();

        for (size_t i = 0; i < numBodies; ++i) {
            if (i == targetIndex) continue; // ��������

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

        // ���㶯��: K = 1/2 * m * v^2
        for (size_t i = 0; i < numBodies; ++i) {
            kineticEnergy += 0.5 * masses[i] * velocities[i].magnitudeSquared();
        }

        // ��������: U = -G * m_i * m_j / r_ij (������i<j���)
        for (size_t i = 0; i < numBodies; ++i) {
            for (size_t j = i + 1; j < numBodies; ++j) {
                double distance = (positions[i] - positions[j]).magnitude();
                if (distance > 1e-10) { // �������
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