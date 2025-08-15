#include "boring_tool/example.hpp"
#include <algorithm>
#include <sstream>

namespace btool {

ExampleTool::ExampleTool(const std::string& name) : name_(name) {}

std::string ExampleTool::getName() const {
    return name_;
}

std::string ExampleTool::process(const std::string& input) {
    // 示例处理逻辑：将输入转换为大写
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

std::vector<std::string> ExampleTool::batchProcess(const std::vector<std::string>& inputs) {
    std::vector<std::string> results;
    results.reserve(inputs.size());
    
    for (const auto& input : inputs) {
        results.push_back(process(input));
    }
    
    return results;
}

} // namespace boring_tool
