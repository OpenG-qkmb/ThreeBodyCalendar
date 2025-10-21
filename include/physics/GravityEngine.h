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
        // 计算N体引力系统的导数（用于积分器）
        static void calculateGravitationalDerivatives(const SystemState& state, SystemState& derivatives);

        // 计算两个天体间的引力
        static Vector3D calculateGravitationalForce(const Vector3D& pos1, double mass1,
            const Vector3D& pos2, double mass2);

        // 计算单个天体受到的合力
        static Vector3D calculateNetForce(const std::vector<Vector3D>& positions,
            const std::vector<double>& masses,
            size_t targetIndex);

        // 验证能量守恒（用于调试）
        static double calculateTotalEnergy(const std::vector<Vector3D>& positions,
            const std::vector<Vector3D>& velocities,
            const std::vector<double>& masses);

        // 验证动量守恒（用于调试）
        static Vector3D calculateTotalMomentum(const std::vector<Vector3D>& velocities,
            const std::vector<double>& masses);
    };

} // namespace Physics

#endif