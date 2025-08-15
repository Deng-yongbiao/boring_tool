#include "boring_tool/example.hpp"
#include <iostream>
#include <vector>

int main() {
    std::cout << "=== Boring Tool 示例程序 ===" << std::endl;
    
    // 创建工具实例
    btool::ExampleTool tool("字符串转换工具");
    
    std::cout << "工具名称: " << tool.getName() << std::endl;
    
    // 单个处理示例
    std::string input = "hello world";
    std::string result = tool.process(input);
    std::cout << "输入: " << input << " -> 输出: " << result << std::endl;
    
    // 批量处理示例
    std::vector<std::string> inputs = {"apple", "banana", "cherry"};
    std::vector<std::string> results = tool.batchProcess(inputs);
    
    std::cout << "批量处理结果:" << std::endl;
    for (size_t i = 0; i < inputs.size(); ++i) {
        std::cout << "  " << inputs[i] << " -> " << results[i] << std::endl;
    }
    
    std::cout << "示例程序执行完成！" << std::endl;
    return 0;
}
