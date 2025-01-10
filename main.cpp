#include "BigInt.hpp"

int main () {

	#if TMP
		constexpr
    #else
        const
    #endif
    size_t size = 50;
	if
	COMPILE_TIME_WORK
    (size) {
		std::cout << "Compile time start" << std::endl;

        COMPILE_TIME_WORK
        BigInt<size> num1 = "10000";

        COMPILE_TIME_WORK
        BigInt<size> num2 = "10";

        COMPILE_TIME_WORK
        BigInt<size> res = num1 / num2;
        {
            COMPILE_TIME_WORK
            BigInt<size> num1 = "20000";

            COMPILE_TIME_WORK
            BigInt<size> num2 = "20000";

            COMPILE_TIME_WORK
            BigInt<size> res = num1 + num2;

            std::cout << "res: ";
            res.print();
        }
        std::cout << "res: ";
		res.print();
		std::cout << "Compile time end" << std::endl;
	}
	std::cout << "Run time" << std::endl;
}