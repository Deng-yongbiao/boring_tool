#include "boring_tool/span.h"
#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <string>

using namespace btool;

class SpanTest : public ::testing::Test {
protected:
    void SetUp() override {
        for (int i = 0; i < 10; ++i) {
            test_data_[i] = i;
        }
        for (int i = 0; i < 5; ++i) {
            const_test_data_[i] = i * 10;
        }
    }

    int test_data_[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int const_test_data_[5] = {0, 10, 20, 30, 40};
    std::vector<int> test_vector_ = {100, 200, 300, 400, 500};
    std::array<int, 3> test_array_ = {1000, 2000, 3000};
};

// 基本构造测试
TEST_F(SpanTest, DefaultConstructor) {
    Span<int> span;
    EXPECT_EQ(span.size(), 0);
    EXPECT_TRUE(span.empty());
    EXPECT_EQ(span.data(), nullptr);
}

TEST_F(SpanTest, PointerLengthConstructor) {
    Span<int> span(test_data_, 5);
    EXPECT_EQ(span.size(), 5);
    EXPECT_FALSE(span.empty());
    EXPECT_EQ(span.data(), test_data_);
}

TEST_F(SpanTest, ArrayConstructor) {
    int local_array[4] = {1, 2, 3, 4};
    Span<int> span(local_array);
    EXPECT_EQ(span.size(), 4);
    EXPECT_EQ(span.data(), local_array);
}

TEST_F(SpanTest, ConstContainerConstructor) {
    Span<const int> span(test_vector_);
    EXPECT_EQ(span.size(), test_vector_.size());
    EXPECT_EQ(span.data(), test_vector_.data());
}

TEST_F(SpanTest, MutableContainerConstructor) {
    Span span(test_vector_);
    EXPECT_EQ(span.size(), test_vector_.size());
    EXPECT_EQ(span.data(), test_vector_.data());
}

// 访问方法测试
TEST_F(SpanTest, DataAndSize) {
    Span<int> span(test_data_, 7);
    EXPECT_EQ(span.data(), test_data_);
    EXPECT_EQ(span.size(), 7);
}

TEST_F(SpanTest, Empty) {
    Span<int> empty_span;
    Span<int> non_empty_span(test_data_, 3);
    
    EXPECT_TRUE(empty_span.empty());
    EXPECT_FALSE(non_empty_span.empty());
}

TEST_F(SpanTest, FrontAndBack) {
    Span<int> span(test_data_, 5);
    EXPECT_EQ(span.front(), 0);
    EXPECT_EQ(span.back(), 4);
}

TEST_F(SpanTest, SubscriptOperator) {
    Span<int> span(test_data_, 6);
    EXPECT_EQ(span[0], 0);
    EXPECT_EQ(span[3], 3);
    EXPECT_EQ(span[5], 5);
}

TEST_F(SpanTest, AtMethod) {
    Span<int> span(test_data_, 5);
    EXPECT_EQ(span.at(0), 0);
    EXPECT_EQ(span.at(2), 2);
    EXPECT_EQ(span.at(4), 4);
}

// 迭代器测试
TEST_F(SpanTest, Iterators) {
    Span<int> span(test_data_, 4);
    
    auto it = span.begin();
    EXPECT_EQ(*it, 0);
    ++it;
    EXPECT_EQ(*it, 1);
    
    auto end_it = span.end();
    EXPECT_EQ(end_it - span.begin(), 4);
}

TEST_F(SpanTest, ConstIterators) {
    Span<int> span(test_data_, 4);
    
    auto cit = span.cbegin();
    EXPECT_EQ(*cit, 0);
    
    auto cend_it = span.cend();
    EXPECT_EQ(cend_it - span.cbegin(), 4);
}

TEST_F(SpanTest, RangeBasedFor) {
    Span<int> span(test_data_, 4);
    int expected[] = {0, 1, 2, 3};
    int i = 0;
    
    for (int val : span) {
        EXPECT_EQ(val, expected[i++]);
    }
    EXPECT_EQ(i, 4);
}

// 子视图测试
TEST_F(SpanTest, Subspan) {
    Span<int> span(test_data_, 8);
    
    auto sub1 = span.subspan(2, 3);
    EXPECT_EQ(sub1.size(), 3);
    EXPECT_EQ(sub1[0], 2);
    EXPECT_EQ(sub1[1], 3);
    EXPECT_EQ(sub1[2], 4);
    
    auto sub2 = span.subspan(5);
    EXPECT_EQ(sub2.size(), 3);
    EXPECT_EQ(sub2[0], 5);
    EXPECT_EQ(sub2[2], 7);
    
    auto sub3 = span.subspan(3, 0);
    EXPECT_EQ(sub3.size(), 0);
    EXPECT_TRUE(sub3.empty());
}

TEST_F(SpanTest, First) {
    Span<int> span(test_data_, 6);
    
    auto first3 = span.first(3);
    EXPECT_EQ(first3.size(), 3);
    EXPECT_EQ(first3[0], 0);
    EXPECT_EQ(first3[2], 2);
    
    auto first0 = span.first(0);
    EXPECT_EQ(first0.size(), 0);
    EXPECT_TRUE(first0.empty());
}

TEST_F(SpanTest, Last) {
    Span<int> span(test_data_, 6);
    
    auto last3 = span.last(3);
    EXPECT_EQ(last3.size(), 3);
    EXPECT_EQ(last3[0], 3);
    EXPECT_EQ(last3[2], 5);
    
    auto last0 = span.last(0);
    EXPECT_EQ(last0.size(), 0);
    EXPECT_TRUE(last0.empty());
}

// 比较操作测试
TEST_F(SpanTest, Equality) {
    Span<int> span1(test_data_, 4);
    Span<int> span2(test_data_, 4);
    Span<int> span3(test_data_ + 1, 4);
    
    EXPECT_EQ(span1, span2);
    EXPECT_NE(span1, span3);
}

TEST_F(SpanTest, EqualityDifferentSizes) {
    Span<int> span1(test_data_, 3);
    Span<int> span2(test_data_, 4);
    
    EXPECT_NE(span1, span2);
}

TEST_F(SpanTest, EqualityEmptySpans) {
    Span<int> empty1;
    Span<int> empty2;
    
    EXPECT_EQ(empty1, empty2);
}

// 辅助函数测试
TEST_F(SpanTest, MakeSpan) {
    auto span1 = MakeSpan(test_data_, 5);
    EXPECT_EQ(span1.size(), 5);
    EXPECT_EQ(span1.data(), test_data_);
    
    auto span2 = MakeSpan(test_vector_);
    EXPECT_EQ(span2.size(), test_vector_.size());
    EXPECT_EQ(span2.data(), test_vector_.data());
    
    auto span3 = MakeSpan(test_array_);
    EXPECT_EQ(span3.size(), test_array_.size());
    EXPECT_EQ(span3.data(), test_array_.data());
}

TEST_F(SpanTest, MakeConstSpan) {
    auto span1 = MakeConstSpan(test_data_, 4);
    EXPECT_EQ(span1.size(), 4);
    EXPECT_EQ(span1.data(), test_data_);
    
    auto span2 = MakeConstSpan(test_vector_);
    EXPECT_EQ(span2.size(), test_vector_.size());
    EXPECT_EQ(span2.data(), test_vector_.data());
}

TEST_F(SpanTest, StringAsBytes) {
    std::string test_string = "Hello World";
    auto bytes = StringAsBytes(test_string);
    
    EXPECT_EQ(bytes.size(), test_string.size());
    EXPECT_EQ(bytes[0], 'H');
    EXPECT_EQ(bytes[4], 'o');

    //修改原始字符串会影响字节视图
    test_string[0] = 'A';
    EXPECT_EQ(bytes[0], 'A');
}

TEST_F(SpanTest, BytesAsStringView) {
    std::string test_string = "Test String";
    auto bytes = StringAsBytes(test_string);
    auto string_view = BytesAsStringView(bytes);
    
    EXPECT_EQ(string_view.size(), test_string.size());
    EXPECT_EQ(string_view, test_string);
}

TEST_F(SpanTest, muiltiSpanToOneMem) {
    std::string original = "Hello World";

    // 创建多个视图，都指向同一块内存
    auto bytes1 = StringAsBytes(original);
    auto bytes2 = StringAsBytes(original);
    auto str_view1 = BytesAsStringView(bytes1);
    auto str_view2 = BytesAsStringView(bytes2);

    // 所有视图都指向 original 的内存
    // 修改 original 会影响所有视图
    original[0] = 'J';  // 改为 "Jello World"

    // 所有视图都会看到变化
    EXPECT_EQ(str_view1, "Jello World");
    EXPECT_EQ(str_view1, str_view2);
}

// 边界条件测试
TEST_F(SpanTest, SingleElementSpan) {
    Span<int> span(test_data_, 1);
    EXPECT_EQ(span.size(), 1);
    EXPECT_FALSE(span.empty());
    EXPECT_EQ(span.front(), span.back());
    EXPECT_EQ(span[0], 0);
}

TEST_F(SpanTest, ZeroLengthSpan) {
    Span<int> span(test_data_, 0);
    EXPECT_EQ(span.size(), 0);
    EXPECT_TRUE(span.empty());
    EXPECT_EQ(span.data(), test_data_);
}

TEST_F(SpanTest, ConstCorrectness) {
    Span<const int> const_span(const_test_data_, 3);
    EXPECT_EQ(const_span[0], 0);
    EXPECT_EQ(const_span[1], 10);
}

TEST_F(SpanTest, MutableSpan) {
    Span<int> mutable_span(test_data_, 3);
    mutable_span[1] = 999;
    EXPECT_EQ(test_data_[1], 999);
}

// 模板推导测试
TEST_F(SpanTest, TemplateDeduction) {
    int array[4] = {1, 2, 3, 4};
    auto span1 = Span(array);
    EXPECT_EQ(span1.size(), 4);
    
    std::vector<int> vec = {10, 20, 30};
    auto span2 = Span(vec);
    EXPECT_EQ(span2.size(), 3);
}

// 容器兼容性测试
TEST_F(SpanTest, VectorCompatibility) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    Span<int> span(vec);
    
    EXPECT_EQ(span.size(), vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(span[i], vec[i]);
    }
}

TEST_F(SpanTest, ArrayCompatibility) {
    std::array<int, 3> arr = {100, 200, 300};
    Span<int> span(arr);
    
    EXPECT_EQ(span.size(), arr.size());
    arr[2] = 100;
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << "span[" << i << "] = " << span[i] << ", ";
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
        EXPECT_EQ(span[i], arr[i]);
    }
}

// 字符串相关测试
TEST_F(SpanTest, StringCompatibility) {
    const std::string str = "Hello";
    Span span(str);
    
    EXPECT_EQ(span.size(), str.size());
    EXPECT_EQ(span[0], 'H');
    EXPECT_EQ(span[4], 'o');
}

// 嵌套Span测试
TEST_F(SpanTest, NestedSpans) {
    Span<int> outer_span(test_data_, 8);
    auto inner_span = outer_span.subspan(2, 4);
    auto inner_inner_span = inner_span.subspan(1, 2);
    
    EXPECT_EQ(outer_span.size(), 8);
    EXPECT_EQ(inner_span.size(), 4);
    EXPECT_EQ(inner_inner_span.size(), 2);
    
    EXPECT_EQ(inner_span[0], 2);
    EXPECT_EQ(inner_inner_span[0], 3);
}

