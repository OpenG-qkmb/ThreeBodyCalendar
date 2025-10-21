#include "physics/Integrator.h"
#include <iostream>

namespace Physics {

    void Integrator::integrateStep(SystemState& state,
        DerivativeFunction derivFunc,
        double dt,
        Method method) {
        switch (method) {
        case EULER:
            eulerStep(state, derivFunc, dt);
            break;
        case RUNGE_KUTTA_4:
            rk4Step(state, derivFunc, dt);
            break;
        case VERLET:
            verletStep(state, derivFunc, dt);
            break;
        default:
            std::cerr << "Unknown integration method, using RK4" << std::endl;
            rk4Step(state, derivFunc, dt);
        }
    }

    void Integrator::integrate(SystemState& state,
        DerivativeFunction derivFunc,
        double totalTime,
        double timeStep,
        Method method) {
        int steps = static_cast<int>(totalTime / timeStep);

        for (int i = 0; i < steps; ++i) {
            integrateStep(state, derivFunc, timeStep, method);
            state.time += timeStep;
        }
    }

    // 欧拉法实现
    void Integrator::eulerStep(SystemState& state, DerivativeFunction derivFunc, double dt) {
        SystemState derivative(state.positions.size());
        derivFunc(state, derivative);

        // 更新位置和速度: y_{n+1} = y_n + dt * f(t_n, y_n)
        for (size_t i = 0; i < state.positions.size(); ++i) {
            state.positions[i] = state.positions[i] + derivative.positions[i] * dt;
            state.velocities[i] = state.velocities[i] + derivative.velocities[i] * dt;
        }
    }

    // 四阶龙格-库塔法实现
    void Integrator::rk4Step(SystemState& state, DerivativeFunction derivFunc, double dt) {
        size_t n = state.positions.size();

        SystemState k1(n), k2(n), k3(n), k4(n);
        SystemState temp(n);

        // k1 = f(t_n, y_n)
        derivFunc(state, k1);

        // k2 = f(t_n + dt/2, y_n + dt/2 * k1)
        temp = addStates(state, k1, dt / 2.0);
        temp.time = state.time + dt / 2.0;
        derivFunc(temp, k2);

        // k3 = f(t_n + dt/2, y_n + dt/2 * k2)
        temp = addStates(state, k2, dt / 2.0);
        temp.time = state.time + dt / 2.0;
        derivFunc(temp, k3);

        // k4 = f(t_n + dt, y_n + dt * k3)
        temp = addStates(state, k3, dt);
        temp.time = state.time + dt;
        derivFunc(temp, k4);

        // y_{n+1} = y_n + dt/6 * (k1 + 2*k2 + 2*k3 + k4)
        SystemState weightedSum = addStates(k1, k2, 2.0);
        weightedSum = addStates(weightedSum, k3, 2.0);
        weightedSum = addStates(weightedSum, k4, 1.0);

        for (size_t i = 0; i < n; ++i) {
            state.positions[i] = state.positions[i] + weightedSum.positions[i] * (dt / 6.0);
            state.velocities[i] = state.velocities[i] + weightedSum.velocities[i] * (dt / 6.0);
        }
    }

    // Verlet积分实现
    void Integrator::verletStep(SystemState& state, DerivativeFunction derivFunc, double dt) {
        static std::vector<Vector3D> prevPositions;

        if (prevPositions.size() != state.positions.size()) {
            // 第一次调用，使用欧拉法初始化
            prevPositions = state.positions;
            SystemState derivative(state.positions.size());
            derivFunc(state, derivative);

            for (size_t i = 0; i < state.positions.size(); ++i) {
                prevPositions[i] = state.positions[i] - state.velocities[i] * dt +
                    derivative.velocities[i] * (dt * dt * 0.5);
            }
            return;
        }

        SystemState derivative(state.positions.size());
        derivFunc(state, derivative);

        std::vector<Vector3D> newPositions(state.positions.size());
        for (size_t i = 0; i < state.positions.size(); ++i) {
            // r_{n+1} = 2r_n - r_{n-1} + a_n * dt^2
            newPositions[i] = state.positions[i] * 2.0 - prevPositions[i] +
                derivative.velocities[i] * (dt * dt);

            // 更新速度: v_n = (r_{n+1} - r_{n-1}) / (2*dt)
            state.velocities[i] = (newPositions[i] - prevPositions[i]) / (2.0 * dt);
        }

        prevPositions = state.positions;
        state.positions = newPositions;
    }

    // 辅助函数：状态相加
    SystemState Integrator::addStates(const SystemState& a, const SystemState& b, double scale) {
        SystemState result(a.positions.size());

        for (size_t i = 0; i < a.positions.size(); ++i) {
            result.positions[i] = a.positions[i] + b.positions[i] * scale;
            result.velocities[i] = a.velocities[i] + b.velocities[i] * scale;
        }

        result.time = a.time + b.time * scale;
        return result;
    }

} // namespace Physics