# Programming Practice · 编程学习记录

记录 C++ 与 Python 的学习过程，包含小型实践项目、算法题解、阶段计划和进度笔记。代码按主题独立组织，适合从具体练习进入；本仓库持续学习中，各目录的完成程度不同。

## 内容导航

| 入口 | 内容 | 使用方式 |
| --- | --- | --- |
| [C++ 专项练习](cpp_practice/) | 生命周期、异常安全、泛型统计、测量记录分析等 | 阅读对应目录源码，逐项编译 |
| [Book Manager](Book%20Manager/) | 命令行图书管理系统 | Windows 上编译两个源文件，见[项目说明](Book%20Manager/README.md) |
| [LeetCode Hot 100](LeetCode-Hot100/) | 哈希、双指针等题型的 C++ 解题记录 | 作为在线评测题解阅读或提交 |
| [洛谷练习](luogu/) | 字母转换、数字反转、时间计算等基础题 | 根据题目输入输出要求运行 |
| [Python 入门](python_practice/) | 第一个脚本、环境配置、长期路线与进度 | 先阅读[跨平台环境说明](python_practice/跨平台环境说明.md) |
| [简历参考](简历参考/) | 收集的简历与项目展示参考图片 | 仅作学习资料索引 |

## 快速开始

克隆仓库：

```sh
git clone https://github.com/Lover-Leo/Code-Learing.git
cd Code-Learing
```

### C++：先验证工具链

建议使用支持 C++20 的编译器。以下命令在仓库根目录、Visual Studio 的 **x64 Native Tools Command Prompt** 中执行：

```bat
mkdir build
cl /nologo /W4 /utf-8 /EHsc /std:c++20 cpp_practice\00-toolchain-check\main.cpp /Fe:build\toolchain-check.exe
.\build\toolchain-check.exe
```

预期输出 `C++20 toolchain OK`。已有 `build` 目录时可跳过创建步骤。

其他单文件练习可使用相同编译选项，并按程序需要准备输入文件。涉及 `text.txt`、`measurements.txt` 等相对路径的练习，应从相应练习目录运行。Book Manager 使用 Windows 控制台接口，构建方式单独说明。

### Python：运行第一个脚本

完成 Python 环境配置后，在仓库根目录执行：

```sh
python --version
python python_practice/00_environemnt/hello.py
```

当前脚本输出 `Hellow World`。Windows 与 macOS 的安装、解释器选择和验证状态见[跨平台环境说明](python_practice/跨平台环境说明.md)；环境目录不随仓库同步。

## 学习路线与进度

| 方向 | 计划 | 进度 |
| --- | --- | --- |
| C++ | [学习规划与任务目标](cpp_practice/C%2B%2B学习规划和任务目标.md) | [当前完成进度](cpp_practice/当前完成进度.md) |
| Python | [任务目标与长期规划](python_practice/任务目标与长期规划.md) | [当前进度](python_practice/当前进度.md) |

另有 [C++ STL 用法笔记](cpp_practice/【杂项】算竞常用%20C%2B%2B%20STL%20用法.md)。阶段计划表示学习目标，实际完成情况以源码与进度记录为准。

## 使用说明

- 这是多个独立练习的集合，没有统一的全仓库构建入口。
- LeetCode 文件可能保留同一道题的多种解法，部分仅包含 `Solution` 类，需要结合在线评测提供的头文件与入口使用。
- 共享的 VS Code 配置保留在 `.vscode/`；现有 MSVC 构建脚本包含本机 Visual Studio 路径，更换电脑时需检查实际安装位置。
- 原有目录与文件名保持不变，包括早期练习中的拼写。新增内容约定见 [CONTRIBUTING.md](CONTRIBUTING.md)。
