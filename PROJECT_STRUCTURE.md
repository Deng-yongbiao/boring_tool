# 项目结构说明

## 目录结构

```
boring_tool/
├── CMakeLists.txt              # 主CMake配置文件
├── src/                        # 源代码目录
│   ├── CMakeLists.txt         # 源代码构建配置
│   └── example.cpp            # 示例实现文件
├── include/                    # 公共头文件目录
│   └── boring_tool/           # 命名空间目录
│       └── example.hpp        # 示例头文件
├── examples/                   # 示例程序目录
│   ├── CMakeLists.txt         # 示例构建配置
│   └── main.cpp               # 示例主程序
├── tests/                      # 测试程序目录
│   ├── CMakeLists.txt         # 测试构建配置
│   └── example_test.cpp       # 示例测试文件
├── cmake/                      # CMake配置文件
│   └── boring_toolConfig.cmake.in  # 包配置文件模板
├── build.sh                    # macOS/Linux构建脚本
├── build.bat                   # Windows构建脚本
├── README.md                   # 项目说明文档
└── PROJECT_STRUCTURE.md        # 本文件
```

## 文件说明

### CMake配置文件

- **CMakeLists.txt**: 主配置文件，设置项目属性、编译选项、平台特定配置
- **src/CMakeLists.txt**: 库构建配置，收集源文件并创建库目标
- **examples/CMakeLists.txt**: 示例程序构建配置
- **tests/CMakeLists.txt**: 测试程序构建配置

### 构建脚本

- **build.sh**: macOS/Linux平台的构建脚本，支持Debug/Release模式
- **build.bat**: Windows平台的构建脚本，支持Debug/Release模式

### 源代码组织

- **include/boring_tool/**: 公共头文件，使用命名空间避免冲突
- **src/**: 实现文件，包含所有工具组件的具体实现
- **examples/**: 使用示例，展示如何使用库中的工具
- **tests/**: 单元测试，验证库功能的正确性

## 平台支持

### Windows (MSVC)
- 使用Visual Studio生成器
- 支持静态链接 (/MT, /MTd)
- 启用警告级别4 (/W4)
- 定义Windows特定宏

### macOS (Xcode)
- 使用Xcode生成器
- 启用严格警告 (-Wall -Wextra -Wpedantic)
- 优化设置 (-O3 for Release, -g -O0 for Debug)
- 自动生成Xcode scheme

## 构建选项

### 主要选项
- `BUILD_TESTS`: 是否构建测试 (默认: OFF)
- `BUILD_EXAMPLES`: 是否构建示例 (默认: ON)

### 构建类型
- `Debug`: 调试版本，包含调试信息
- `Release`: 发布版本，优化性能

## 输出目录

构建完成后，文件将输出到以下目录：
- **可执行文件**: `build_<Type>/bin/`
- **库文件**: `build_<Type>/lib/`
- **示例程序**: `build_<Type>/bin/examples/`
- **测试程序**: `build_<Type>/bin/tests/`

## 添加新工具组件

1. **创建头文件**: 在 `include/boring_tool/` 目录下创建 `.hpp` 文件
2. **创建实现文件**: 在 `src/` 目录下创建对应的 `.cpp` 文件
3. **更新CMakeLists.txt**: 如果需要特殊配置，更新相应的CMake文件

### 示例
```cpp
// include/boring_tool/my_tool.hpp
namespace boring_tool {
    class MyTool {
        // 你的工具类定义
    };
}

// src/my_tool.cpp
#include "boring_tool/my_tool.hpp"
// 实现代码
```

## 依赖管理

当前配置支持以下依赖查找：
- **PkgConfig**: 自动查找系统包
- **Google Test**: 测试框架（可选）
- **Threads**: 线程库（必需）

## 安装和打包

项目支持完整的安装和打包功能：
- 自动生成CMake配置文件
- 支持 `find_package()` 查找
- 支持 `target_link_libraries()` 链接
- 版本兼容性检查

## 开发工作流

1. **开发**: 在 `src/` 和 `include/` 目录下编写代码
2. **测试**: 在 `tests/` 目录下编写测试
3. **示例**: 在 `examples/` 目录下创建使用示例
4. **构建**: 使用构建脚本或手动CMake命令
5. **安装**: 使用 `cmake --build . --target install`

## 注意事项

- 所有公共头文件都应放在 `include/boring_tool/` 目录下
- 使用 `boring_tool` 命名空间避免符号冲突
- 遵循C++17标准
- 在Windows上注意DLL导出符号设置
- 测试和示例程序会自动链接到主库
