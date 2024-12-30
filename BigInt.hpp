#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <algorithm>
#include <string.h>

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
	constexpr CT_array () : CT_array(0) {}

	constexpr CT_array (value_type val) {
		int i = SIZE - 1;
		for (; i > 0 && val != 0; --i) {
			arr[i] = val % 10;
			val /= 10;
		}
		while (i >= 0)
			arr[i--] = 0;
	}

	constexpr CT_array (const CT_array<value_type, SIZE>& other) {
		for (int i = SIZE; i --> 0;) {
			arr[i] = other[i];
		}
	}

	constexpr CT_array (const std::initializer_list<value_type>& il) {
		int i = SIZE;
		for (auto it = std::rbegin(il); it != std::rend(il); ++it) {
			arr[--i] = *it;
		}
		if (i < 0)
			throw std::out_of_range("out of range");
		while (i > 0)
			arr[--i] = 0;
	}

	constexpr CT_array (const char* str) {
		int i = SIZE;

		if (str && !__is_numeric(str))
			throw std::invalid_argument("String must contain only digits");

		static_assert((std::is_same_v<T, int>));

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
	constexpr size_type size () const {
		return SIZE;
	}

	constexpr void print () const {
		int i = 0;
		while (arr[i] == 0)
			++i;
		for (;i < SIZE; ++i) {
			std::cout << arr[i];
		}
		std::cout << std::endl;
	}
public:
	constexpr const_reference operator[] (size_type i) const {
		return arr[i];
	}

	constexpr reference operator[] (size_type i) {
		return const_cast<reference>(static_cast<const CT_array&>(*this)[i]);
	}
private:
	T arr[SIZE];

	constexpr static bool __is_numeric(const char* str) {
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
	constexpr BigInt () = default;
	constexpr BigInt (const char* str) : arr(str) {}
	constexpr BigInt (int val) : arr(val) {}
	constexpr BigInt (const std::initializer_list<int>& il) : arr(il) {}
	constexpr BigInt (const BigInt<N>& other) : arr(other.arr) {}
public:
	constexpr void print () const {
		arr.print();
	}
public:
	constexpr int operator[] (size_t i) const {
		return arr[i];
	}

	constexpr int& operator[] (size_t i) {
		return arr[i];
	}

	constexpr BigInt<N> operator+ (const BigInt<N>& other) const {
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

	constexpr BigInt<N> operator- (const BigInt<N>& other) const {
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
private:
	CT_array<int, N> arr;

	static constexpr bool __is_bigger(const BigInt<N>& op1, const BigInt<N>& op2) {
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