# C++ 与 Git 学习路线（面向 ROS 2 / 机器人）

适用背景：会基础 C、一些 Python，有嵌入式开发经验；系统为 Ubuntu 24.04。按每周约 5～7 小时设计，共 8 周。进度可以伸缩，能独立完成每周作品比按日期赶进度更重要。

## 学习方法

- 每周安排 2 次概念学习、2 次动手练习、1 次回顾；建议视频/阅读占 30%，写代码与调试占 70%。
- C 的变量、循环、函数只做快速复习。重点放在 C++ 的对象生命周期、引用与 `const`、标准库、资源管理和构建工具上。
- Git 从第一周起随每个练习一起用。每完成一个可运行的小功能，查看差异并提交一次；提交信息写清“做了什么”。
- 每周保留一份简短笔记：遇到的问题、错误原因、解决方式、下一步。能向别人解释自己的代码，才算真正掌握。

## 八周计划

| 周次 | C++ / 工程主题 | Git 主题 | 本周可检查的成果 |
| --- | --- | --- | --- |
| 1 | Ubuntu 命令行编译；C 与 C++ 差异；`std::string`、`std::vector`、引用、`const`、函数重载 | `init`、`status`、`add`、`commit`、`log`、`diff` | 写一个串口数据文本解析小程序：从输入中提取数值并计算平均值，至少做 3 次提交 |
| 2 | `struct`/`class`、构造与析构、封装、头文件与源文件分离；值传递和引用传递 | `.gitignore`、查看与恢复工作区改动（`restore`） | 将解析程序拆成类和多个文件，解释对象何时创建和销毁 |
| 3 | STL 容器与算法：`vector`、`array`、`map`、迭代器、`find_if`、`sort`；lambda | 分支 `switch -c`、合并 `merge`、冲突练习 | 实现传感器样本统计：过滤异常值、排序、求均值；在实验分支开发并合并 |
| 4 | RAII、智能指针 `unique_ptr`/`shared_ptr`、拷贝与移动、异常基础；避免无必要的裸 `new/delete` | `revert`、`stash`；分清工作区、暂存区与提交 | 给样本统计程序增加资源封装，并用 Git 完成一次安全撤销 |
| 5 | CMake 基础、编译选项、调试 `gdb`、简单单元测试；认识编译与链接错误 | 阅读 `log --oneline --graph`；整理提交 | 用 CMake 构建前面的程序，能定位并修复一个故意制造的 bug |
| 6 | C++17 常用特性：`auto`、结构化绑定、`optional`；回调、lambda 捕获；适量接触线程与互斥 | 远程仓库、`fetch`、`pull`、`push`（需要时再接入托管平台） | 写一个模拟机器人状态/里程计的命令行程序，保存阶段性版本 |
| 7 | ROS 2 Jazzy 工程结构：`colcon`、`ament_cmake`、`rclcpp` 节点、发布/订阅 | 为 ROS 2 包设置 `.gitignore`，提交源码与配置 | 在 Ubuntu 上构建一个 C++ 发布者和订阅者，并说明消息流向 |
| 8 | 参数、定时器、服务；把前面的小程序核心逻辑接入 ROS 2 | 分支协作、合并冲突复盘；写清项目 README | 完成一个“模拟传感器 → 过滤/统计 → 发布状态”的小包，并写运行说明 |

第 6～8 周可以依自己的兴趣替换成编码器、IMU、串口协议或机器人运动学小项目。你的嵌入式经验适合做“从原始数据到机器人状态”的贯穿练习。

## Ubuntu 环境与第一步

已检查到本机有 `g++`、`cmake`、`git` 和 `gdb`。先用终端查看版本：

```bash
g++ --version
cmake --version
git --version
gdb --version
```

第一个 C++ 文件可以放在 `practice/01_cpp_basics/main.cpp`。手动编译时先用：

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -g practice/01_cpp_basics/main.cpp -o /tmp/cpp_first
/tmp/cpp_first
```

当前文件夹顶层存在一个空的、只读的 `.git` 目录，顶层尚不是可用的 Git 仓库。因此首次练习请在 `practice/` 内运行 `git init`，不要在顶层直接初始化，也不要删除现有 `.git` 目录。`practice/` 建好后，在其中依次练习 `git status`、`git add`、`git commit`、`git log`。首次提交前，如果 Git 提示缺少身份信息，可在该仓库里设置 `git config user.name "你的名字"` 和 `git config user.email "你的邮箱"`。

第 1 周的最小任务：写一个程序，读取若干个整数样本，跳过超出自定有效范围的值，输出有效样本个数与平均值。做完后尝试加入一个新功能，再用 `git diff` 看清改动并提交。

## 课程与参考资料

- **C++ 主线**：[黑马程序员 C++ 从 0 到 1](https://www.bilibili.com/video/BV1et411b73Z/)。有基础可快速略过变量、循环等章节，重点看引用、类、对象生命周期、STL。课程较早，Windows 环境搭建部分不要照搬到 Ubuntu；编译按本页命令练习。
- **Git 入门**：[尚硅谷 Git 教程](https://www.bilibili.com/video/BV15J411973T/)。先看基本命令、提交、分支与冲突；涉及旧界面或远程平台的操作，以当前文档为准。查概念时看 [Pro Git 中文版](https://git-scm.com/book/zh/v2) 的第 2～3 章。
- **ROS 2 衔接**：[鱼香 ROS《动手学 ROS 2》](https://www.bilibili.com/video/BV1gr4y1Q7j5/)。可用来理解工作空间、节点与话题；课程录制较早，安装和命令应以 [ROS 2 Jazzy 官方文档](https://docs.ros.org/en/jazzy/) 为准。Ubuntu 24.04 与 Jazzy 对应，开始安装时再确认官方安装步骤。

每周回来时，把当前代码、终端命令、完整报错和“自己认为的原因”发给我；我会按你当时的进度给出下一步练习和代码反馈。
