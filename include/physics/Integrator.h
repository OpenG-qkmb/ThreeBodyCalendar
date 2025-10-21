#ifndef _INCLUDE_VECTOR_
#define _INCLUDE_VECTOR_
#include <vector>
#endif

#ifndef _INCLUDE_FUNCTIONAL_
#define _INCLUDE_FUNCTIONAL_
#include <functional>
#endif

#ifndef _INCLUDE_CORE_VECTOR3D_H_
#define _INCLUDE_CORE_VECTOR3D_H_
#include "core/Vector3D.h"
#endif

#pragma once

#ifndef _INTEGRATOR_H_
#define _INTEGRATOR_H_

namespace Physics {

    // 微分方程系统的状态
    struct SystemState {
        std::vector<Vector3D> positions;
        std::vector<Vector3D> velocities;
        double time;

        SystemState(size_t numBodies = 0) : positions(numBodies), velocities(numBodies), time(0.0) {}
    };

    // 微分方程函数类型
    using DerivativeFunction = std::function<void(const SystemState&, SystemState&)>;

    class Integrator {
    public:
        enum Method {
            EULER,              // 欧拉法（简单但精度低）
            RUNGE_KUTTA_4,      // 四阶龙格-库塔法（推荐）
            VERLET              // Verlet积分（能量守恒好）
        };

        // 单步积分
        static void integrateStep(SystemState& state,
            DerivativeFunction derivFunc,
            double dt,
            Method method = RUNGE_KUTTA_4);

        // 多步积分
        static void integrate(SystemState& state,
            DerivativeFunction derivFunc,
            double totalTime,
            double timeStep,
            Method method = RUNGE_KUTTA_4);

    private:
        // 不同积分方法的实现
        static void eulerStep(SystemState& state, DerivativeFunction derivFunc, double dt);
        static void rk4Step(SystemState& state, DerivativeFunction derivFunc, double dt);
        static void verletStep(SystemState& state, DerivativeFunction derivFunc, double dt);

        // 辅助函数
        static SystemState addStates(const SystemState& a, const SystemState& b, double scale = 1.0);
    };

} // namespace Physics

#endif