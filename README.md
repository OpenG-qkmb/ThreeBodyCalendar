# 三体人的万年历 ThreeBodyCalendar

这是中国科大计算机程序设计课程大作业。该项目拟实现模拟任意给定参数的三体运动，并以某一恒星附近的一颗行星为研究对象生成该行星的万年历。

This project is intended for submission as a major assignment for the Computer Programming course at the University of Science and Technology of China. It aims to simulate the three-body motion of any given parameters, generating a perpetual calendar for a planet orbiting a specific star.

拟采用的项目结构如下：

```text
ThreeBodyCalendar/
├── .github/                   # GitHub特定配置
│   └── workflows/             # CI/CD流水线
├── cmake/                     # CMake模块
├── docs/                      # 文档
├── include/                   # 头文件
│   ├── core/
│   ├── physics/
│   ├── simulation/
│   └── utils/
├── src/                       # 源代码
│   ├── core/
│   ├── physics/
│   ├── simulation/
│   └── main.cpp
├── tests/                     # 测试代码
├── resources/                 # 资源文件
├── third_party/               # 第三方库
├── scripts/                   # 构建脚本
├── CMakeLists.txt
├── README.md
├── .gitignore
└── LICENSE
```