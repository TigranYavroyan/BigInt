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
    CT_array (value_type val = 0);

	COMPILE_TIME_WORK
    CT_array (const CT_array<value_type, SIZE>& other);

	COMPILE_TIME_WORK
    CT_array (const std::initializer_list<value_type>& il);

	COMPILE_TIME_WORK
    CT_array (const char* str);
public:

	COMPILE_TIME_WORK
    size_type capacity () const;

	COMPILE_TIME_WORK
    size_type size () const;

	COMPILE_TIME_WORK
    void fill (const value_type& val);

	COMPILE_TIME_WORK
    void print () const;
public:

	COMPILE_TIME_WORK
    const_reference operator[] (size_type i) const;

	COMPILE_TIME_WORK
    reference operator[] (size_type i);
private:
	T arr[SIZE];

    template <typename U>
    static
	COMPILE_TIME_WORK
	size_type __till_num (U* arr);

	static
	COMPILE_TIME_WORK
	size_type __strlen (const char* str);

	COMPILE_TIME_WORK
    static bool __is_numeric(const char* str);
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
    BigInt (const char* str);

	COMPILE_TIME_WORK
    BigInt (int val);

	COMPILE_TIME_WORK
    BigInt (const std::initializer_list<value_type>& il);

	COMPILE_TIME_WORK
    BigInt (const BigInt<N>& other);
public:

	COMPILE_TIME_WORK
    void print () const;

	COMPILE_TIME_WORK
    size_type size () const;

	COMPILE_TIME_WORK
    size_type capacity () const;

	COMPILE_TIME_WORK
    void fill (value_type val);

    COMPILE_TIME_WORK
    void subnum (const BigInt<N>& other, size_type start, size_type end, size_type pos = 0);
public:

    COMPILE_TIME_WORK
    bool operator== (const BigInt<N>& other) const;

    COMPILE_TIME_WORK
    bool operator!= (const BigInt<N>& other) const;

    COMPILE_TIME_WORK
    bool operator> (const BigInt<N>& other) const;

    COMPILE_TIME_WORK
    bool operator< (const BigInt<N>& other) const;

    COMPILE_TIME_WORK
    bool operator<= (const BigInt<N>& other) const;

    COMPILE_TIME_WORK
    bool operator>= (const BigInt<N>& other) const;

	COMPILE_TIME_WORK
    const value_type operator[] (size_type i) const;

	COMPILE_TIME_WORK
    reference operator[] (size_type i);

	COMPILE_TIME_WORK
    BigInt<N> operator+ (const BigInt<N>& other) const;

	COMPILE_TIME_WORK
    BigInt<N> operator- (const BigInt<N>& other) const;

    COMPILE_TIME_WORK
    BigInt<N> operator* (const BigInt<N>& other) const;

	COMPILE_TIME_WORK
	std::pair<BigInt<N>, BigInt<N>> operator/ (const BigInt<N>& other) const;

    COMPILE_TIME_WORK
    BigInt<N>& operator+= (const BigInt<N>& other);

    COMPILE_TIME_WORK
    BigInt<N>& operator-= (const BigInt<N>& other);

    COMPILE_TIME_WORK
    BigInt<N>& operator*= (const BigInt<N>& other);

	COMPILE_TIME_WORK
    BigInt<N>& operator/= (const BigInt<N>& other);

private:
	CT_array<char, N> arr;

	static
	COMPILE_TIME_WORK
    bool __is_bigger(const BigInt<N>& op1, const BigInt<N>& op2);

    static
	COMPILE_TIME_WORK
    bool __is_bigger_equal_ranges(const CT_array<char, N>& op1, const CT_array<char, N>& op2, long long f_start, long long f_end, long long s_start, long long s_end);

	static
	COMPILE_TIME_WORK
	int __calculate_count (BigInt<N>& dividend, const BigInt<N>& divisor);
};

#include "BigInt.cpp"

#endif // BIGINT_HPP