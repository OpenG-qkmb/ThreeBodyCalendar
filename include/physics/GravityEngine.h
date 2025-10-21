#ifndef _INCLUDE_VECTOR_
#define _INCLUDE_VECTOR_
#include <vector>
#endif

#ifndef _INCLUDE_CORE_VECTOR3D_H_
#define _INCLUDE_CORE_VECTOR3D_H_
#include "core/Vector3D.h"
#endif

#ifndef _INCLUDE_INTEGRATOR_H_
#define _INCLUDE_INTEGRATOR_H_
#include "physics/Integrator.h"
#endif

#ifndef _INCLUDE_PHYSICSCONSTANTS_H_
#define _INCLUDE_PHYSICSCONSTANTS_H_
#include "physics/PhysicsConstants.h"
#endif

#pragma once

#ifndef _GRAVITYENGINE_H_
#define _GRAVITYENGINE_H_

namespace Physics {

    class GravityEngine {
    public:
        // ����N������ϵͳ�ĵ��������ڻ�������
        static void calculateGravitationalDerivatives(const SystemState& state, SystemState& derivatives);

        // ������������������
        static Vector3D calculateGravitationalForce(const Vector3D& pos1, double mass1,
            const Vector3D& pos2, double mass2);

        // ���㵥�������ܵ��ĺ���
        static Vector3D calculateNetForce(const std::vector<Vector3D>& positions,
            const std::vector<double>& masses,
            size_t targetIndex);

        // ��֤�����غ㣨���ڵ��ԣ�
        static double calculateTotalEnergy(const std::vector<Vector3D>& positions,
            const std::vector<Vector3D>& velocities,
            const std::vector<double>& masses);

        // ��֤�����غ㣨���ڵ��ԣ�
        static Vector3D calculateTotalMomentum(const std::vector<Vector3D>& velocities,
            const std::vector<double>& masses);
    };

} // namespace Physics

#endif