#!/bin/bash

# 构建脚本 - macOS/Linux
set -e

# 默认构建类型
BUILD_TYPE=${1:-Release}
BUILD_DIR="build_${BUILD_TYPE}"

echo "构建类型: ${BUILD_TYPE}"
echo "构建目录: ${BUILD_DIR}"

# 创建构建目录
mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}

# 配置CMake
if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS - 使用Xcode生成器
    cmake -G "Xcode" -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
else
    # Linux - 使用Unix Makefiles
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..
fi

# 构建
if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS - 使用Xcode构建
    cmake --build . --config ${BUILD_TYPE}
else
    # Linux - 使用make构建
    make -j$(nproc)
fi

echo "构建完成！"
echo "可执行文件位置: ${BUILD_DIR}/bin/"
echo "库文件位置: ${BUILD_DIR}/lib/"
