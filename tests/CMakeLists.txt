# 查找Google Test（可选）
find_package(GTest QUIET)
find_package(Threads REQUIRED)

# 如果找不到GTest，尝试使用pkg-config
if(NOT GTest_FOUND)
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(GTEST gtest)
        if(GTEST_FOUND)
            set(GTest_FOUND TRUE)
            set(GTest_INCLUDE_DIRS ${GTEST_INCLUDE_DIRS})
            set(GTest_LIBRARIES ${GTEST_LIBRARIES})
        endif()
    endif()
endif()

if(GTest_FOUND)
    # 收集测试源文件
    file(GLOB TEST_SOURCES "*.cpp" "*.cxx" "*.cc" "*.c")
    
    # 创建测试可执行文件
    foreach(TEST_SOURCE ${TEST_SOURCES})
        get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
        
        add_executable(${TEST_NAME} ${TEST_SOURCE})
        
        # 链接主库和测试库
        target_link_libraries(${TEST_NAME} PRIVATE 
            boring_tool
            GTest::GTest
            GTest::Main
            Threads::Threads
        )
        
        # 设置包含目录
        target_include_directories(${TEST_NAME} PRIVATE
            ${CMAKE_SOURCE_DIR}/include
            ${CMAKE_SOURCE_DIR}/src
        )
        
        # 设置输出目录
        set_target_properties(${TEST_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests
        )
        
        # 设置RPATH，确保运行时能找到Google Test库
        if(APPLE)
            set_target_properties(${TEST_NAME} PROPERTIES
                BUILD_WITH_INSTALL_RPATH TRUE
                INSTALL_RPATH "/opt/anaconda3/lib"
            )
        endif()
        
        # 添加到CTest
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endforeach()
else()
    message(STATUS "Google Test not found, creating simple tests instead")
    
    # 创建简单的测试（不依赖Google Test）
    file(GLOB SIMPLE_TEST_SOURCES "simple_test.cpp")
    
    foreach(SIMPLE_TEST_SOURCE ${SIMPLE_TEST_SOURCES})
        get_filename_component(SIMPLE_TEST_NAME ${SIMPLE_TEST_SOURCE} NAME_WE)
        
        add_executable(${SIMPLE_TEST_NAME} ${SIMPLE_TEST_SOURCE})
        
        # 链接主库
        target_link_libraries(${SIMPLE_TEST_NAME} PRIVATE 
            boring_tool
            Threads::Threads
        )
        
        # 设置包含目录
        target_include_directories(${SIMPLE_TEST_NAME} PRIVATE
            ${CMAKE_SOURCE_DIR}/include
            ${CMAKE_SOURCE_DIR}/src
        )
        
        # 设置输出目录
        set_target_properties(${SIMPLE_TEST_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/tests
        )
        
        # 添加到CTest
        add_test(NAME ${SIMPLE_TEST_NAME} COMMAND ${SIMPLE_TEST_NAME})
    endforeach()
endif()
