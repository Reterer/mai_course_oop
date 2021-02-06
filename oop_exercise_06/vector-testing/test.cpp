#include "pch.h"
#include "../src/vector.hpp"
#include "../src/allocator.hpp"

#include "pch.h"
#include "../src/figure.hpp"
#include "../src/vector.hpp"

// Тесты для динамического массива

TEST(Vector, InitAndDeinit) {
	Vector<int> v;
	Vector<double> v2(10);
}

TEST(Vector, OperatorSquareBrackets) {
	Vector<int> v = { 1, 2, 3, 4 };

	ASSERT_TRUE(v[0] == 1 && v[3] == 4);
	ASSERT_THROW(v[-1], std::out_of_range);
	ASSERT_THROW(v[4], std::out_of_range);
}

TEST(Vector, Iterator) {
	Vector<int> v = { 1, 2, 3, 4 };
	auto begin = v.begin();
	auto end = v.end();
	
	ASSERT_EQ(*begin, 1);
	ASSERT_EQ(*++begin, 2);
	ASSERT_NE(begin, end);
	ASSERT_THROW(*end, std::out_of_range);

	Vector<int> empty_vec;
	ASSERT_EQ(empty_vec.begin(), empty_vec.end());
}

TEST(Vector, push_back) {
	Vector<int> v;
	v.push_back(10);
	ASSERT_EQ(v[0], 10);
}

TEST(Vector, Insert) {
	Vector<int> v(0);
	v.insert(v.begin(), 10);
	v.insert(v.end(), 42);
	v.insert(++v.begin(), 36);
	ASSERT_EQ(v[0], 10);
	ASSERT_EQ(v[1], 36);
	ASSERT_EQ(v[2], 42);
}

TEST(Vector, Erase) {
	Vector<int> v = { 1,2,3,4 };
	auto it = v.erase(v.begin());
	ASSERT_TRUE(it == v.begin() && v.size() == 3 && v[0] == 2);
}