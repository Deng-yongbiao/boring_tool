#include "boring_tool/example.hpp"
#include <cassert>
#include <iostream>
#include <gtest/gtest.h>

// int main() {
//
// }

TEST(basic, test) {
    std::cout << "运行示例测试..." << std::endl;

    // 测试构造函数
    btool::ExampleTool tool("测试工具");
    assert(tool.getName() == "测试工具");

    // 测试单个处理
    std::string result = tool.process("hello");
    assert(result == "HELLO");

    // 测试批量处理
    std::vector<std::string> inputs = {"a", "b", "c"};
    std::vector<std::string> results = tool.batchProcess(inputs);
    assert(results.size() == 3);
    assert(results[0] == "A");
    assert(results[1] == "B");
    assert(results[2] == "C");

    std::cout << "所有测试通过！" << std::endl;
}