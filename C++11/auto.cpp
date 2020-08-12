/*
 * C++11 auto关键字自动推导类型
 * g++ -std=c++11 -o auto auto.cpp
 */

#include <iostream>

int main(void)
{
	auto str = "hello world";
	auto n = 100;

	std::cout << str << std::endl;
	std::cout << n << std::endl;

	return 0;
}
