#include "BigInt.hpp"

int main () {

	#if TMP
		constexpr
    #else
        const
    #endif
    size_t size = 100;
	if
	COMPILE_TIME_WORK
    (size) {
		std::cout << "Compile time start" << std::endl;

        COMPILE_TIME_WORK
        BigInt<size> num1 = "999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999";

        COMPILE_TIME_WORK
        BigInt<size> num2 = "12312312312";

        COMPILE_TIME_WORK
        BigInt<size> res = num1 * num2;

		res.print();
		std::cout << "Compile time end" << std::endl;
	}
	std::cout << "Run time" << std::endl;
}