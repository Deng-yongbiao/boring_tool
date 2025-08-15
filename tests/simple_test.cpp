#include "boring_tool/example.hpp"
#include <cassert>
#include <iostream>

int main() {
    std::cout << "=== 运行简单测试 ===" << std::endl;
    
    try {
        // 测试构造函数
        btool::ExampleTool tool("测试工具");
        assert(tool.getName() == "测试工具");
        std::cout << "✓ 构造函数测试通过" << std::endl;
        
        // 测试单个处理
        std::string result = tool.process("hello");
        assert(result == "HELLO");
        std::cout << "✓ 单个处理测试通过" << std::endl;
        
        // 测试批量处理
        std::vector<std::string> inputs = {"a", "b", "c"};
        std::vector<std::string> results = tool.batchProcess(inputs);
        assert(results.size() == 3);
        assert(results[0] == "A");
        assert(results[1] == "B");
        assert(results[2] == "C");
        std::cout << "✓ 批量处理测试通过" << std::endl;
        
        std::cout << "\n🎉 所有测试通过！" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ 测试失败: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ 测试失败: 未知错误" << std::endl;
        return 1;
    }
}
