#!/bin/bash

# 测试运行脚本
set -e

echo "=== Boring Tool 测试运行器 ==="

# 检查构建目录
BUILD_DIR="build_debug"
if [ ! -d "$BUILD_DIR" ]; then
    echo "❌ 构建目录不存在，请先运行 ./build.sh Debug"
    exit 1
fi

cd "$BUILD_DIR"

echo "📁 构建目录: $BUILD_DIR"
echo ""

# 运行简单测试（推荐）
if [ -f "bin/tests/Debug/simple_test" ]; then
    echo "🧪 运行简单测试..."
    ./bin/tests/Debug/simple_test
    echo ""
else
    echo "⚠️  简单测试不存在"
fi

# 运行Google Test（如果可用）
if [ -f "bin/tests/Debug/example_test" ]; then
    echo "🧪 运行Google Test..."
    echo "注意: 需要设置 DYLD_LIBRARY_PATH 环境变量"
    
    # 尝试设置库路径
    export DYLD_LIBRARY_PATH="/opt/anaconda3/lib:$DYLD_LIBRARY_PATH"
    
    if ./bin/tests/Debug/example_test; then
        echo "✅ Google Test 运行成功"
    else
        echo "❌ Google Test 运行失败，可能需要手动设置库路径"
        echo "   运行: export DYLD_LIBRARY_PATH=/opt/anaconda3/lib:\$DYLD_LIBRARY_PATH"
    fi
    echo ""
else
    echo "⚠️  Google Test 不存在"
fi

# 运行示例程序
if [ -f "bin/examples/Debug/main" ]; then
    echo "🚀 运行示例程序..."
    ./bin/examples/Debug/main
    echo ""
else
    echo "⚠️  示例程序不存在"
fi

echo "🎉 测试完成！"
