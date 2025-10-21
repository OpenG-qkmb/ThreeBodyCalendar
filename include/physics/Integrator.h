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

    // ΢�ַ���ϵͳ��״̬
    struct SystemState {
        std::vector<Vector3D> positions;
        std::vector<Vector3D> velocities;
        double time;

        SystemState(size_t numBodies = 0) : positions(numBodies), velocities(numBodies), time(0.0) {}
    };

    // ΢�ַ��̺�������
    using DerivativeFunction = std::function<void(const SystemState&, SystemState&)>;

    class Integrator {
    public:
        enum Method {
            EULER,              // ŷ�������򵥵����ȵͣ�
            RUNGE_KUTTA_4,      // �Ľ�����-���������Ƽ���
            VERLET              // Verlet���֣������غ�ã�
        };

        // ��������
        static void integrateStep(SystemState& state,
            DerivativeFunction derivFunc,
            double dt,
            Method method = RUNGE_KUTTA_4);

        // �ಽ����
        static void integrate(SystemState& state,
            DerivativeFunction derivFunc,
            double totalTime,
            double timeStep,
            Method method = RUNGE_KUTTA_4);

    private:
        // ��ͬ���ַ�����ʵ��
        static void eulerStep(SystemState& state, DerivativeFunction derivFunc, double dt);
        static void rk4Step(SystemState& state, DerivativeFunction derivFunc, double dt);
        static void verletStep(SystemState& state, DerivativeFunction derivFunc, double dt);

        // ��������
        static SystemState addStates(const SystemState& a, const SystemState& b, double scale = 1.0);
    };

} // namespace Physics

#endif