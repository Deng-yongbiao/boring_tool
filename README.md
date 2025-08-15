# Boring Tool

一个C++工具组件库，包含工作中积累的各种实用工具。

## 特性

- 跨平台支持：Windows (MSVC) 和 macOS (Xcode)
- 现代C++17标准
- CMake构建系统
- 完整的安装和包管理支持
- 示例程序和测试支持

## 系统要求

- CMake 3.16 或更高版本
- C++17 兼容的编译器
- Windows: Visual Studio 2019 或更高版本
- macOS: Xcode 12 或更高版本

## 快速开始

### 克隆仓库

```bash
git clone <your-repo-url>
cd boring_tool
```

### 构建项目

#### macOS/Linux

```bash
# 使用默认Release模式构建
./build.sh

# 或指定构建模式
./build.sh Debug
```

#### Windows

```cmd
# 使用默认Release模式构建
build.bat

# 或指定构建模式
build.bat Debug
```

### 手动构建

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## 项目结构

```
boring_tool/
├── CMakeLists.txt          # 主CMake配置
├── src/                    # 源代码目录
│   ├── CMakeLists.txt     # 源代码构建配置
│   └── *.cpp              # 源文件
├── include/                # 头文件目录
│   └── boring_tool/       # 公共头文件
├── examples/               # 示例程序
│   ├── CMakeLists.txt     # 示例构建配置
│   └── *.cpp              # 示例源文件
├── tests/                  # 测试程序
│   ├── CMakeLists.txt     # 测试构建配置
│   └── *.cpp              # 测试源文件
├── cmake/                  # CMake配置文件
├── build.sh                # macOS/Linux构建脚本
└── build.bat               # Windows构建脚本
```

## 使用库

### 在你的项目中

```cmake
# 查找包
find_package(boring_tool REQUIRED)

# 链接库
target_link_libraries(your_target PRIVATE boring_tool::boring_tool)
```

### 在代码中

```cpp
#include "boring_tool/example.hpp"

int main() {
    boring_tool::ExampleTool tool("我的工具");
    std::string result = tool.process("hello world");
    return 0;
}
```

## 开发

### 添加新的工具组件

1. 在 `include/boring_tool/` 目录下创建头文件
2. 在 `src/` 目录下创建实现文件
3. 更新相应的CMakeLists.txt文件

### 运行测试

#### 方法1: 使用测试脚本（推荐）
```bash
# 运行所有测试
./run_tests.sh
```

#### 方法2: 手动运行
```bash
# 启用测试构建
cmake -DBUILD_TESTS=ON ..
cmake --build .

# 运行简单测试（无需额外依赖）
./build_debug/bin/tests/Debug/simple_test

# 运行Google Test（需要设置库路径）
export DYLD_LIBRARY_PATH=/opt/anaconda3/lib:$DYLD_LIBRARY_PATH
./build_debug/bin/tests/Debug/example_test

# 运行示例程序
./build_debug/bin/examples/Debug/main
```

#### 方法3: 使用CTest
```bash
cd build_debug
ctest --verbose
```

### 安装

```bash
cmake --build . --target install
```

## 许可证

本项目采用 [LICENSE](LICENSE) 许可证。

## 贡献

欢迎提交Issue和Pull Request！
