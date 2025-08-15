# 收集源文件
file(GLOB_RECURSE SOURCES "*.cpp" "*.cxx" "*.cc" "*.c")
file(GLOB_RECURSE HEADERS "*.h" "*.hpp" "*.hxx")

# 创建库目标
add_library(boring_tool ${SOURCES} ${HEADERS})

# 设置库属性
set_target_properties(boring_tool PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${HEADERS}"
)

# 设置包含目录
target_include_directories(boring_tool
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# 链接依赖库
# target_link_libraries(boring_tool PRIVATE dependency_lib)

# 设置编译选项
target_compile_features(boring_tool PUBLIC cxx_std_17)

# 导出符号（Windows DLL支持）
if(WIN32)
    set_target_properties(boring_tool PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS ON
    )
endif()
