#include "BigInt.hpp"

int main () {
	constexpr size_t size = 50;
	if constexpr (size) {
		std::cout << "Compile time start" << std::endl;
		constexpr BigInt<size> num1 = "129523499999992454325786789";
		constexpr BigInt<size> num2 = "129523499999986324532453278";
		constexpr BigInt<size> res = num1 + num2;
		constexpr BigInt<size> res2 = num1 - num2;
		res.print();
		res2.print();
		std::cout << "Compile time end" << std::endl;
	}
	std::cout << "Run time" << std::endl;
}