#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <algorithm>
#include <string.h>

#ifndef TMP
	#define TMP true
#endif
// TMP

#if TMP
    #define COMPILE_TIME_WORK constexpr
#else
    #define COMPILE_TIME_WORK
#endif // checking

template <typename T, size_t SIZE>
class CT_array {
public:
	using value_type = T;
	using size_type = size_t;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
public:
	COMPILE_TIME_WORK
    CT_array (value_type val = 0) {
		int i = SIZE - 1;
		for (; i > 0 && val != 0; --i) {
			arr[i] = val % 10;
			val /= 10;
		}
		while (i >= 0)
			arr[i--] = 0;
	}


	COMPILE_TIME_WORK
    CT_array (const CT_array<value_type, SIZE>& other) {
		for (int i = SIZE; i --> 0;) {
			arr[i] = other[i];
		}
	}


	COMPILE_TIME_WORK
    CT_array (const std::initializer_list<value_type>& il) {
		int i = SIZE;
		for (auto it = std::rbegin(il); it != std::rend(il); ++it) {
			arr[--i] = *it;
		}
		if (i < 0)
			throw std::out_of_range("out of range");
		while (i > 0)
			arr[--i] = 0;
	}


	COMPILE_TIME_WORK
    CT_array (const char* str) {
		int i = SIZE;

		if (str && !__is_numeric(str))
			throw std::invalid_argument("String must contain only digits");

		static_assert((std::is_same_v<T, int>) || (std::is_same_v<T, char>));

		for (int j = strlen(str); i --> 0 && j --> 0;) {
			arr[i] = str[j] - '0';
		}

		if (i < 0)
			throw std::out_of_range("out of range");
		while (i >= 0) {
			arr[i--] = 0;
		}
	}

public:

	COMPILE_TIME_WORK
    size_type capacity () const {
		return SIZE;
	}

	COMPILE_TIME_WORK
    size_type size () const {
        size_type i = __till_num();
        return SIZE - i;
	}

	COMPILE_TIME_WORK
    void fill (const value_type& val) {
        for (size_t i = 0; i < SIZE; ++i) {
            arr[i] = val;
        }
	}

	COMPILE_TIME_WORK
    void print () const {
		size_t i = __till_num();
		for (;i < SIZE; ++i) {
			std::cout << arr[i];
		}
		std::cout << std::endl;
	}
public:

	COMPILE_TIME_WORK
    const_reference operator[] (size_type i) const {
		return arr[i];
	}


	COMPILE_TIME_WORK
    reference operator[] (size_type i) {
		return const_cast<reference>(static_cast<const CT_array&>(*this)[i]);
	}
private:
	T arr[SIZE];

	COMPILE_TIME_WORK
	size_type __till_num () const {
		size_type i = 0;
		while (i < SIZE && arr[i] == 0)
			++i;
		return i;
	}
	
	COMPILE_TIME_WORK
    static bool __is_numeric(const char* str) {
		for (int i = 0; str[i] != '\0'; ++i) {
			if (str[i] < '0' || str[i] > '9')
				return false;
		}
		return true;
	}
};

template <size_t N>
class BigInt {
public:
	using value_type = char;
	using size_type = size_t;
	using pointer = char*;
	using const_pointer = const char*;
	using reference = char&;
	using const_reference = const char&;

	COMPILE_TIME_WORK
    BigInt () = default;

	COMPILE_TIME_WORK
    BigInt (const char* str) : arr(str) {}

	COMPILE_TIME_WORK
    BigInt (int val) : arr(val) {}

	COMPILE_TIME_WORK
    BigInt (const std::initializer_list<value_type>& il) : arr(il) {}

	COMPILE_TIME_WORK
    BigInt (const BigInt<N>& other) : arr(other.arr) {}
public:

	COMPILE_TIME_WORK
    void print () const {
		size_type i = 0;
		while (i < N && arr[i] == 0)
			++i;
		for (; i < N; ++i) {
			std::printf("%d", arr[i]);
		}
		std::cout.put('\n');
	}

	COMPILE_TIME_WORK
    size_type size () const {
		return arr.size();
	}

	COMPILE_TIME_WORK
    size_type capacity () const {
		return arr.capacity();
	}

	COMPILE_TIME_WORK
    void fill (value_type val) {
		arr.fill(val);
	}
public:

	COMPILE_TIME_WORK
    const value_type operator[] (size_type i) const {
		return arr[i];
	}


	COMPILE_TIME_WORK
    reference operator[] (size_type i) {
		return arr[i];
	}


	COMPILE_TIME_WORK
    BigInt<N> operator+ (const BigInt<N>& other) const {
		BigInt<N> res;
		int mod = 0;
		int curr = 0;
		int carry = 0;

		for (int i = N; i --> 0;) {
			curr = carry + arr[i] + other.arr[i];
			mod = curr % 10;
			res.arr[i] = mod;
			carry = curr / 10;
		}

		return res;
	}

	COMPILE_TIME_WORK
    BigInt<N> operator- (const BigInt<N>& other) const {
		if (__is_bigger(other, *this))
			throw std::invalid_argument("Result can't be negative");

		BigInt<N> res;
		BigInt<N> cache = *this;

		for (int i = N; i --> 0;) {
			if (cache.arr[i] >= other.arr[i])
				res[i] = cache.arr[i] - other.arr[i];
			else {
				for (int j = i - 1; j >= 0; --j) {
					if (cache.arr[j] != 0) {
						--cache.arr[j];
						break;
					}
				}
				res[i] = (10 + cache.arr[i]) - other.arr[i];
			}
		}

		return res;
	}

    COMPILE_TIME_WORK
    BigInt<N>& operator+= (const BigInt<N>& other) {
        *this = *this + other;
        return *this;
    }

    COMPILE_TIME_WORK
    BigInt<N>& operator-= (const BigInt<N>& other) {
        *this = *this - other;
        return *this;
    }

    COMPILE_TIME_WORK
    BigInt<N> operator* (const BigInt<N>& other) const {
        BigInt<N> res;
        BigInt<N> row;

        int carry = 0;
        int mod = 0;
        int curr = 0;
        int offset = 0;

        int num1_size;
        int num2_size = other.size();

        for (int i = other.capacity() - 1; num2_size >= 0; --i, --num2_size) {
            num1_size = this->size();
            for (int j = this->capacity() - 1; num1_size >= 0; --j, --num1_size) {
                curr = other.arr[i] * arr[j] + carry;
                carry = curr / 10;
                mod = curr % 10;
                row[j - offset] = mod;
            }
            res += row;
            row.fill(0);
            ++offset;
        }

        return res;
    }

	COMPILE_TIME_WORK
	BigInt<N> operator/ (const BigInt<N>& other) const {
		BigInt<N> res;



		return res;
	}


private:
	CT_array<char, N> arr;

	static
	COMPILE_TIME_WORK
    bool __is_bigger(const BigInt<N>& op1, const BigInt<N>& op2) {
		for (int i = 0; i < N; ++i) {
			if (op1[i] < op2[i])
				return false;
			else if (op1[i] > op2[i])
				return true;
		}
		return false;
	}
};

#endif // BIGINT_HPP