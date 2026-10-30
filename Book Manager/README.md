# Book Manager · 命令行图书管理

一个用于练习 C++ 类、容器、算法与文件读写的小型图书管理程序。当前实现使用 Windows 控制台接口。

## 功能

- 添加图书，并检查空字段与重复编号。
- 显示全部图书，按编号查找、借出和归还。
- 按书名或编号排序，统计总量与借阅状态。
- 按编号删除图书，启动时读取、正常退出时保存本地记录。

## 构建与运行

需要支持 C++20 的 MSVC。打开 Visual Studio 的 **x64 Native Tools Command Prompt**，从仓库根目录执行：

```bat
cd "Book Manager"
cl /nologo /W4 /utf-8 /EHsc /std:c++20 bookManager.cpp book.cpp /Fe:bookManager.exe
.\bookManager.exe
```

也可以使用现有 [build.cmd](build.cmd)，但其中的 Visual Studio 安装路径需要与本机一致。

## 文件与数据

| 文件 | 作用 |
| --- | --- |
| [book.h](book.h) | 图书类与借阅状态定义 |
| [book.cpp](book.cpp) | 图书类实现 |
| [bookManager.cpp](bookManager.cpp) | 菜单、查询、排序与文件读写 |
| [book.txt](book.txt) | 本地文本记录 |

程序按**当前工作目录**读取和写入 `book.txt`，因此请从本目录启动。每条记录占四行：编号、书名、作者、借阅状态（`0` 为可借，`1` 为已借出）。

菜单输入 `0` 正常退出时保存数据。关闭窗口或强制结束进程可能丢失本次修改；试用仓库中的记录前可先备份 `book.txt`。
