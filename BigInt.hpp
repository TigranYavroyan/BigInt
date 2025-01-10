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

template <size_t N>
class BigInt;

template <typename T, size_t SIZE>
class CT_array {
public:
	using value_type = T;
	using size_type = size_t;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

    template <size_t N>
    friend class BigInt;
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

		for (int j = __strlen(str); i --> 0 && j --> 0;) {
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
        size_type i = __till_num(arr);
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
		size_t i = __till_num(arr);
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

    template <typename U>
    static
	COMPILE_TIME_WORK
	size_type __till_num (U* arr) {
		size_type i = 0;
		while (i < SIZE && arr[i] == 0)
			++i;
		return i;
	}

	static
	COMPILE_TIME_WORK
	size_type __strlen (const char* str) {
		size_type i = 0;
		while (str[i])
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
public:
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

    COMPILE_TIME_WORK
    BigInt (const BigInt<N>& other, size_type start, size_type end, size_type pos = 0) {

    }
public:

	COMPILE_TIME_WORK
    void print () const {
		size_type i = CT_array<char, N>::__till_num(arr.arr);
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

    COMPILE_TIME_WORK
    void subnum (const BigInt<N>& other, size_type start, size_type end, size_type pos = 0) {
        if (pos >= N)
            throw std::out_of_range("Out of range");
        if (pos == 0)
            pos = CT_array<char, N>::__till_num();
        while (start != end) {
            arr[pos] = other.arr[start++];
        }
	}
public:

    COMPILE_TIME_WORK
    bool operator== (const BigInt<N>& other) const {
        for (int i = 0; i < N; ++i) {
            if (arr[i] != other.arr[i])
                return false;
        }
        return true;
    }

    COMPILE_TIME_WORK
    bool operator!= (const BigInt<N>& other) const {
        return !(*this == other);
    }

    COMPILE_TIME_WORK
    bool operator> (const BigInt<N>& other) const {
        return (__is_bigger(*this, other));
    }

    COMPILE_TIME_WORK
    bool operator< (const BigInt<N>& other) const {
        return !((*this > other) && (*this != other));
    }

    COMPILE_TIME_WORK
    bool operator<= (const BigInt<N>& other) const {
        return !(*this > other);
    }

    COMPILE_TIME_WORK
    bool operator>= (const BigInt<N>& other) const {
        return !(*this < other);
    }

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
		if (other > *this)
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

        int num1_size = 0;
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
        BigInt<N> curr;

        long long this_start = CT_array<char, N>::__till_num(other.arr.arr);
        long long this_end = this_start;
        const long long other_start = CT_array<char, N>::__till_num(other.arr.arr);
        const long long other_end = 0;
        const long long other_num_size = other_start - other_end;

        int count = 1;

        if (other_num_size == 0)
            throw std::invalid_argument("Can't divide by zero");

        while (this_end >= 0) {
            this_end += other_num_size;
            if (!__is_bigger_equal_ranges(arr, other.arr, this_start, this_end, other_start, other_end))
                ++this_end;

            while ()
        }

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

    static
	COMPILE_TIME_WORK
    bool __is_bigger_equal_ranges(const CT_array<char, N>& op1, const CT_array<char, N>& op2, long long f_start, long long f_end, long long s_start, long long s_end) {
		while (f_start >= f_end && s_start >= s_end) {
            if (op1[f_start] < op2[s_start])
                return false;
            ++f_start;
            ++s_start;
        }
        return true;
	}
};

#endif // BIGINT_HPP