template <typename T, size_t SIZE>
COMPILE_TIME_WORK
CT_array<T, SIZE>::CT_array (value_type val) {
	int i = SIZE - 1;
	for (; i > 0 && val != 0; --i) {
		arr[i] = val % 10;
		val /= 10;
	}
	while (i >= 0)
		arr[i--] = 0;
}

template <typename T, size_t SIZE>
COMPILE_TIME_WORK
CT_array<T, SIZE>::CT_array (const CT_array<value_type, SIZE>& other) {
	for (int i = SIZE; i --> 0;) {
		arr[i] = other[i];
	}
}


template <typename T, size_t SIZE>
COMPILE_TIME_WORK
CT_array<T, SIZE>::CT_array (const std::initializer_list<value_type>& il) {
	int i = SIZE;
	for (auto it = std::rbegin(il); it != std::rend(il); ++it) {
		arr[--i] = *it;
	}
	if (i < 0)
		throw std::out_of_range("out of range");
	while (i > 0)
		arr[--i] = 0;
}


template <typename T, size_t SIZE>
COMPILE_TIME_WORK
CT_array<T, SIZE>::CT_array (const char* str) {
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

template <typename T, size_t SIZE>
COMPILE_TIME_WORK
typename CT_array<T, SIZE>::size_type CT_array<T, SIZE>::capacity () const {
	return SIZE;
}

template <typename T, size_t SIZE>
COMPILE_TIME_WORK
typename CT_array<T, SIZE>::size_type CT_array<T, SIZE>::size () const {
	size_type i = __till_num(arr);
	return SIZE - i;
}

template <typename T, size_t SIZE>
COMPILE_TIME_WORK
void CT_array<T, SIZE>::fill (const value_type& val) {
	for (size_t i = 0; i < SIZE; ++i) {
		arr[i] = val;
	}
}

template <typename T, size_t SIZE>
COMPILE_TIME_WORK
void CT_array<T, SIZE>::print () const {
	size_t i = __till_num(arr);
	for (;i < SIZE; ++i) {
		std::cout << arr[i];
	}
	std::cout << std::endl;
}

template <typename T, size_t SIZE>
COMPILE_TIME_WORK
typename CT_array<T, SIZE>::const_reference CT_array<T, SIZE>::operator[] (size_type i) const {
	return arr[i];
}


template <typename T, size_t SIZE>
COMPILE_TIME_WORK
typename CT_array<T, SIZE>::reference CT_array<T, SIZE>::operator[] (size_type i) {
	return const_cast<reference>(static_cast<const CT_array&>(*this)[i]);
}

template <typename T, size_t SIZE>
template <typename U>
COMPILE_TIME_WORK
typename CT_array<T, SIZE>::size_type CT_array<T, SIZE>::__till_num (U* arr) {
	size_type i = 0;
	while (i < SIZE && arr[i] == 0)
		++i;
	return i;
}

template <typename T, size_t SIZE>
COMPILE_TIME_WORK
typename CT_array<T, SIZE>::size_type CT_array<T, SIZE>::__strlen (const char* str) {
	size_type i = 0;
	while (str[i])
		++i;
	return i;
}

template <typename T, size_t SIZE>
COMPILE_TIME_WORK
bool CT_array<T, SIZE>::__is_numeric(const char* str) {
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

template <size_t N>
COMPILE_TIME_WORK
BigInt<N>::BigInt (const char* str) : arr(str) {}

template <size_t N>
COMPILE_TIME_WORK
BigInt<N>::BigInt (int val) : arr(val) {}

template <size_t N>
COMPILE_TIME_WORK
BigInt<N>::BigInt (const std::initializer_list<value_type>& il) : arr(il) {}

template <size_t N>
COMPILE_TIME_WORK
BigInt<N>::BigInt (const BigInt<N>& other) : arr(other.arr) {}

template <size_t N>
COMPILE_TIME_WORK
void BigInt<N>::print () const {
	size_type i = CT_array<char, N>::__till_num(arr.arr);
	for (; i < N; ++i) {
		std::printf("%d", arr[i]);
	}
	std::cout.put('\n');
}

template <size_t N>
COMPILE_TIME_WORK
typename BigInt<N>::size_type BigInt<N>::size () const {
	return arr.size();
}

template <size_t N>
COMPILE_TIME_WORK
typename BigInt<N>::size_type BigInt<N>::capacity () const {
	return arr.capacity();
}

template <size_t N>
COMPILE_TIME_WORK
void BigInt<N>::fill (value_type val) {
	arr.fill(val);
}

template <size_t N>
COMPILE_TIME_WORK
void BigInt<N>::subnum (const BigInt<N>& other, size_type start, size_type end, size_type pos) {
	if (pos >= N)
		throw std::out_of_range("Out of range");
	if (pos == 0)
		pos = CT_array<char, N>::__till_num(this->arr.arr);
	while (start != end && pos < N) {
		arr[pos] = other.arr[start];
		++pos;
		++start;
	}
}

template <size_t N>
COMPILE_TIME_WORK
bool BigInt<N>::operator== (const BigInt<N>& other) const {
	for (int i = 0; i < N; ++i) {
		if (arr[i] != other.arr[i])
			return false;
	}
	return true;
}

template <size_t N>
COMPILE_TIME_WORK
bool BigInt<N>::operator!= (const BigInt<N>& other) const {
	return !(*this == other);
}

template <size_t N>
COMPILE_TIME_WORK
bool BigInt<N>::operator> (const BigInt<N>& other) const {
	return (__is_bigger(*this, other));
}

template <size_t N>
COMPILE_TIME_WORK
bool BigInt<N>::operator< (const BigInt<N>& other) const {
	return !(*this > other || *this == other);
}

template <size_t N>
COMPILE_TIME_WORK
bool BigInt<N>::operator<= (const BigInt<N>& other) const {
	return !(*this > other);
}

template <size_t N>
COMPILE_TIME_WORK
bool BigInt<N>::operator>= (const BigInt<N>& other) const {
	return !(*this < other);
}

template <size_t N>
COMPILE_TIME_WORK
const typename BigInt<N>::value_type BigInt<N>::operator[] (size_type i) const {
	return arr[i];
}

template <size_t N>
COMPILE_TIME_WORK
typename BigInt<N>::reference BigInt<N>::operator[] (size_type i) {
	return arr[i];
}

template <size_t N>
COMPILE_TIME_WORK
BigInt<N> BigInt<N>::operator+ (const BigInt<N>& other) const {
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

template <size_t N>
COMPILE_TIME_WORK
BigInt<N> BigInt<N>::operator- (const BigInt<N>& other) const {
	if (other > *this)
		throw std::invalid_argument("Result can't be negative");

	BigInt<N> res;
	BigInt<N> cache = *this;

	for (int i = N - 1; i > 0; --i) {
		if (cache.arr[i] >= other.arr[i])
			res[i] = cache.arr[i] - other.arr[i];
		else {
			for (int j = i - 1; j >= 0; --j) {
				if (cache.arr[j] != 0) {
					--cache.arr[j];
					while (cache.arr[++j] == 0 && j != i)
						cache.arr[j] = 9;
					break;
				}
			}
			res[i] = (10 + cache.arr[i]) - other.arr[i];
		}
	}

	return res;
}


template <size_t N>
COMPILE_TIME_WORK
BigInt<N> BigInt<N>::operator* (const BigInt<N>& other) const {
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

template <size_t N>
COMPILE_TIME_WORK
std::pair<BigInt<N>, BigInt<N>> BigInt<N>::operator/ (const BigInt<N>& other) const {
	const long long other_num_size = other.size();

	if (other_num_size == 0)
		throw std::invalid_argument("Can't divide by zero");

	std::string res;
	BigInt<N> curr;
	BigInt<N> tmp;

	long long s_start = CT_array<char, N>::__till_num(this->arr.arr);
	long long s_end = s_start + other_num_size;
	int count;

	curr.subnum(*this, s_start, s_end, N - other_num_size);
	if (curr < other) {
		curr *= BigInt<N>("10");
		curr[N - 1] = arr[s_end];
		++s_end;
	}
	tmp = curr;
	count = __calculate_count(tmp, other);
	res += count + '0';
	s_start = s_end;

	bool once_done;
	while (s_start < N) {
		once_done = false;
		while (tmp < other && s_start < N) {
			tmp *= BigInt<N>("10");
			tmp[N - 1] = arr[s_start];
			if (once_done)
				res += '0';
			++s_start;
			once_done = true;
		}
		count = __calculate_count(tmp, other);
		res += count + '0';
	}

	return {BigInt<N>(res.c_str()), tmp};
}

template <size_t N>
COMPILE_TIME_WORK
BigInt<N>& BigInt<N>::operator+= (const BigInt<N>& other) {
	*this = *this + other;
	return *this;
}

template <size_t N>
COMPILE_TIME_WORK
BigInt<N>& BigInt<N>::operator-= (const BigInt<N>& other) {
	*this = *this - other;
	return *this;
}

template <size_t N>
COMPILE_TIME_WORK
BigInt<N>& BigInt<N>::operator*= (const BigInt<N>& other) {
	*this = *this * other;
	return *this;
}

template <size_t N>
COMPILE_TIME_WORK
BigInt<N>& BigInt<N>::operator/= (const BigInt<N>& other) {
	*this = *this / other;
	return *this;
}


template <size_t N>
COMPILE_TIME_WORK
bool BigInt<N>::__is_bigger(const BigInt<N>& op1, const BigInt<N>& op2) {
	for (int i = 0; i < N; ++i) {
		if (op1[i] < op2[i])
			return false;
		else if (op1[i] > op2[i])
			return true;
	}
	return false;
}

template <size_t N>
COMPILE_TIME_WORK
bool BigInt<N>::__is_bigger_equal_ranges(const CT_array<char, N>& op1, const CT_array<char, N>& op2, long long f_start, long long f_end, long long s_start, long long s_end) {
	while (f_start >= f_end && s_start >= s_end) {
		if (op1[f_start] < op2[s_start])
			return false;
		--f_start;
		--s_start;
	}
	return true;
}

template <size_t N>
COMPILE_TIME_WORK
int BigInt<N>::__calculate_count (BigInt<N>& dividend, const BigInt<N>& divisor) {
	int count = 0;

	while (dividend >= divisor) {
		dividend -= divisor;
		++count;
	}

	return count;
}