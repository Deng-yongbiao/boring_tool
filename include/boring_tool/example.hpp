#pragma once

#include <string>
#include <vector>

namespace btool {

/**
 * @brief 示例工具类
 * 
 * 这是一个示例类，展示如何组织你的工具组件
 */
class ExampleTool {
public:
    /**
     * @brief 构造函数
     * @param name 工具名称
     */
    explicit ExampleTool(const std::string& name);
    
    /**
     * @brief 析构函数
     */
    ~ExampleTool() = default;
    
    /**
     * @brief 获取工具名称
     * @return 工具名称
     */
    std::string getName() const;
    
    /**
     * @brief 执行工具功能
     * @param input 输入数据
     * @return 处理结果
     */
    std::string process(const std::string& input);
    
    /**
     * @brief 批量处理
     * @param inputs 输入数据列表
     * @return 处理结果列表
     */
    std::vector<std::string> batchProcess(const std::vector<std::string>& inputs);

private:
    std::string name_;
};

} // namespace boring_tool
