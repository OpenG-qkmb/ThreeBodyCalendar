#pragma once

#ifndef _PHYSICSCONSTANTS_H_
#define _PHYSICSCONSTANTS_H_

namespace PhysicsConstants {
    constexpr double G = 6.67430e-11;        // 引力常数 (m³/kg/s²)
    constexpr double SOLAR_MASS = 1.989e30;  // 太阳质量 (kg)
    constexpr double EARTH_MASS = 5.972e24;  // 地球质量 (kg)
    constexpr double AU = 1.496e11;          // 天文单位 (m)
    constexpr double DAY_SECONDS = 86400.0;  // 一天的秒数

    // 单位转换
    inline double yearsToSeconds(double years) {
        return years * 365.25 * DAY_SECONDS;
    }

    inline double secondsToYears(double seconds) {
        return seconds / (365.25 * DAY_SECONDS);
    }
}

#endif