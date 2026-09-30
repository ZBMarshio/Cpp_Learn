# 面向 ROS 2 的 C++ 学习路线

我有 C、Python 和嵌入式开发基础，使用 Ubuntu 24.04。目标是尽快能读懂、编写并调试 ROS 2 的 C++ 节点，不以学完一本 C++ 教材为前提。

这个仓库的 Git 根目录是 `Cpp_Learn/`；`practice/` 和 `learn/` 都是其中的普通文件夹。已有的样本平均值程序在 `practice/01_cpp_basics/main.cpp`，温度转换程序在同目录的 `temperature.cpp`。后续练习优先改造这些程序，不必反复从“Hello World”开始。

## 学习原则

- 每学一个 C++ 概念，就在现有程序里用一次；能解释代码、编译通过并跑出预期结果后再前进。
- 先掌握写普通节点所需的知识。碰到不熟悉的模板、并发或底层实现时，记录问题，等项目确实用到再深入。
- Git 继续使用 VS Code 的“源代码管理”：完成一个小功能就查看差异、提交。编译产物不要提交。
- C++ 和 ROS 2 交替学习。进入 ROS 2 后，遇到具体 C++ 知识缺口再回头补。

## 需要先会的 C++

| 主题 | 学到什么程度 | 在 ROS 2 中的用途 |
| --- | --- | --- |
| `std::string`、`std::vector`、`std::array` | 会创建、遍历、传给函数 | 保存和处理消息中的文本、数组与传感器样本 |
| 引用、`const`、值传递 | 能读懂 `const T&`，知道何时传值 | 函数参数、消息处理函数 |
| 函数、头文件、命名空间 | 会拆分 `.hpp` / `.cpp`，理解 `std::` | 把算法与节点代码分开，使用 `rclcpp` 接口 |
| `struct`、`class`、构造函数、成员变量 | 能写一个小类，理解对象创建与销毁 | 定义节点类，保存发布者、订阅者和状态 |
| 继承的基本语法 | 看懂 `class MyNode : public rclcpp::Node` | 阅读和编写常见节点示例 |
| `std::shared_ptr`、`std::make_shared` | 理解共享所有权，会按示例使用 | 节点、发布者、订阅者和消息的常见写法 |
| lambda、回调、`std::bind` 的基本用法 | 能看懂并编写简单回调 | 定时器、订阅者、服务回调 |
| `std::chrono`、`auto`、模板的基本形式 | 会使用时间间隔；能读懂 `Publisher<消息类型>` | 定时器与 ROS 2 的类型化接口 |
| 编译、链接、CMake 基础 | 能看懂报错，给程序添加源文件和依赖 | 使用 `ament_cmake` 和 `colcon` 构建包 |

**暂缓专题**：复杂模板与元编程、运算符重载、多重继承、手写 `new/delete`、完整的移动语义、全部 STL 容器、手写多线程。它们以后可能有用，但不是完成第一个 ROS 2 C++ 包的前置条件。`unique_ptr` 和 RAII 先知道用途，遇到资源管理或相关接口时再深入。

## 按成果推进的四个阶段

不设严格周数。每个阶段达到“完成标志”就进入下一阶段。

### 1. 用现有程序补齐 C++ 基础

改造 `practice/01_cpp_basics/main.cpp`：用 `std::vector<double>` 保存有效样本；把“判断有效”和“计算平均值”分别写成函数；让只读容器参数使用 `const std::vector<double>&`。测试空输入、无有效值和正常输入。

完成标志：能解释 `#include`、`std::`、`const &`、`vector`、`main`，并能用下面的命令编译运行：

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -g \
    practice/01_cpp_basics/main.cpp -o /tmp/sample_average
/tmp/sample_average
```

### 2. 把算法整理成可以复用的类

写一个 `SensorFilter` 小类：保存有效范围和样本，提供“加入样本”“计算平均值”两个操作。把声明放进 `.hpp`，实现放进 `.cpp`，在 `main.cpp` 中调用。再写一个简单 lambda，模拟“收到一个样本就调用处理函数”。

完成标志：能说明构造函数、成员变量、头文件与源文件的作用；知道编译多个 `.cpp` 时为什么要把它们一起交给编译器。接着用一个最小的 `CMakeLists.txt` 构建这个程序。

### 3. 开始 ROS 2 C++ 节点

Ubuntu 24.04 对应的学习文档先按 [ROS 2 Jazzy](https://docs.ros.org/en/jazzy/) 走。依次学习工作空间、包、`colcon`、`ament_cmake`，然后照[官方 C++ 发布者与订阅者教程](https://docs.ros.org/en/jazzy/Tutorials/Beginner-Client-Libraries/Writing-A-Simple-Cpp-Publisher-And-Subscriber.html)写两个节点。先看懂 `rclcpp::Node`、定时器、回调和消息类型，再改成自己的数据。

完成标志：能从终端构建并运行两个节点，用 `ros2 topic list`、`ros2 topic echo` 查看它们之间传递的消息；能在 `CMakeLists.txt` 和 `package.xml` 中找到对应依赖。

### 4. 做一个与嵌入式背景相连的小项目

做“模拟传感器 → 过滤 → 发布结果”：一个节点定时发布模拟数据；另一个节点调用第 2 阶段的过滤逻辑，计算并发布结果。随后加入参数，用参数设置有效范围；需要外部触发“清空统计”时，再学习服务。

完成标志：代码能构建运行；可以从命令行观察消息、调整参数；README 中能说清如何启动、各节点负责什么。之后再按项目需要学习 QoS、服务、动作、执行器和多线程。

## 读书与查资料的方法

《C++ Primer Plus》可以当参考书，按上面的主题找对应章节，不必从头逐章读完。每次阅读以“解决当前代码中的一个问题”为目标。ROS 2 的命令、包结构和示例以 [Jazzy 官方教程](https://docs.ros.org/en/jazzy/Tutorials.html)为准；安装时再看[Ubuntu 安装说明](https://docs.ros.org/en/jazzy/Installation/Ubuntu-Install-Debs.html)。

**现在的下一步**：只做第 1 阶段的第一个改动——让样本程序使用 `std::vector<double>` 保存有效输入。完成后编译运行，并在 VS Code 中查看改动、提交一次；再继续拆函数。
