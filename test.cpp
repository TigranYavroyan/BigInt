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
        BigInt<size> num1 = "12193263113702179522618503273386678859448712086533622923332237463801111263526900";

        COMPILE_TIME_WORK
        BigInt<size> num2 = "9876543210987654321098765432109876543210";

        auto [res, mod] = num1 / num2;
        std::cout << "res: ";
		res.print();
        std::cout << "mod: ";
        mod.print();
        // {
        //     COMPILE_TIME_WORK
        //     BigInt<size> num1 = "0";

        //     COMPILE_TIME_WORK
        //     BigInt<size> num2 = "1";

        //     COMPILE_TIME_WORK
        //     BigInt<size> res = num1 + num2;

        //     std::cout << std::boolalpha << (num1 > num2) << std::endl;
        //     std::cout << (num1 >= num2) << std::endl;
        //     std::cout << (num1 <= num2) << std::endl;
        //     std::cout << (num1 < num2) << std::endl;
        //     std::cout << (num1 == num2) << std::endl;
        //     std::cout << (num1 != num2) << std::endl;
        //     std::cout << "res: ";
        //     res.print();
        // }
		std::cout << "Compile time end" << std::endl;
	}
	std::cout << "Run time" << std::endl;
}