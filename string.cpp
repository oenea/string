#include "String.h"
#include <cstring>

using size_type = size_t;

String::String() noexcept {
    _setCapacity(0);
    _setLength(0);
}

String::String(const String& other) {
    _append(other._str, other._strlen);
}

String::String(const String& other, size_type pos, size_t len) {
    append(other._str, pos, len);
}

String::String(String&& other) {
    *this = std::move(other);
}

String::String(const char* copy) {
    _append(copy);
}

String::String(const char* s, size_t n) {
    append(s, 0, n);
}

String::String(size_t n, char c) {
    append(n, c);
}


String::String& operator=(const String& other) {
    if(this != &other) {
        _setLength(0);
        _append(other._str, other._strlen);
    }

    return *this;
}

String::String& operator=(String&& other) {
    if (this != &other) {
        delete _str;
        _str = other._str;
        _strlen = other._strlen;
        _strcap = other._strcap;
        other._str = nullptr;
        other._strlen = 0;
        other._strcap = 0;
    }

    return *this;
}

String::~String() {
    delete _str;
    _strlen = 0;
    _strcap = 0;
    _increaseBy = 0;
}

bool operator==(const String& lhs, const String& rhs)
    return lhs._compare(rhs) == 0;

bool operator!=(const String& lhs, const String& rhs)
    return lhs._compare(rhs) != 0;

bool operator<(const String& lhs, const String& rhs)
    return lhs._compare(rhs) < 0;

bool operator>(const String& lhs, const String& rhs)
    return lhs._compare(rhs) > 0;

bool operator<=(const String& lhs, const String& rhs) 
    return lhs._compare(rhs) <= 0;

bool operator>=(const String& lhs, const String& rhs)
    return lhs._compare(rhs) >= 0;

int String::_compare(const String& rhs) const {
    if (_strlen > rhs._strlen)
        return -1;
    else if (_strlen < rhs._strlen)
        return 1;
    else 
        return strcmp(str, rhs._str);
}

const char& String::operator[](size_type i) const 
    return *(_str + i);

char& String::operator[](size_type i) 
    return *(_str + i);

const char& String::at(size_type i) const {
    if (i < 0 || _strlen <= i)
        throw std::invalid_argument("Out of bound");
    else 
        return operator[](i);
}

char& Strig::at(size_type i) {
    if (i < 0 || _strlen <= i)
        throw std::invalid_argument("Out of bound");
    else 
        return operator[](i);
}

const char& String::front() const
    return operator[](0);

char& String::front()
    return operator[](0);

const char& String::back() const {
    return operator[](_strlen - 1);
}

char& String::back() {
    return operator[](_strlen - 1);
}

String& String::operator+=(const String& s) {
    _append(s._str, s._strlen);
    return *this;
}

String& String::operator+=(const char* s) {
	_append(s);
	return *this;
}

String& String::operator+=(char c) {
	_append(&c, 1);
	return *this;
}

String & String::append(const String & other) {
	_append(other._str, other._strlen);
	return *this;
}

String & String::append(const String& other, size_type subpos, size_t sublen) {
	sublen = _getLength(other, subpos, sublen);
	char* buffer = nullptr;
	_substr(buffer, other._str, subpos, sublen);
	_append(buffer, sublen);
    delete buffer;
	return *this;
}

String& String::append(const char* other) {
	_append(other);
	return *this;
}

String& String::append(const char* s, size_t n) {
	char* buffer = nullptr;
	_substr(buffer, s, 0, n);
	_append(buffer, n);
    delete buffer;
	return *this;
}

String& String::append(size_type n, char c) {
	char* buffer = nullptr;
	_alloc_cstring(buffer, n, c);
	_append(buffer, n);
    delete buffer;
	return *this;
}

String & String::push_back(char c) {
	_append(&c, 1);
	return *this;
}

String& String::insert(size_type pos, const String& other) {
	_insert_str(pos, other._str, other._strlen);
	return *this;
}

String & String::insert(size_type pos, const String & other, size_type subpos, size_t sublen)
{
	sublen = _getLength(other, subpos, sublen);
	char* buffer = nullptr;
	_substr(buffer, other._str, subpos, sublen);
	_insert_str(pos, buffer, sublen);
	delete buffer;
	return *this;
}

String& String::insert(size_type pos, const char* other) {
	_insert_str(pos, other);
	return *this;
}

String & String::insert(size_type pos, const char* s, size_t n) {
	char* buffer = nullptr;
	_substr(buffer, s, 0, n);
	_insert_str(pos, buffer, n);
	delete buffer;
	return *this;
}

String & String::insert(size_type pos, size_t n, char c) {
	char* buffer = nullptr;
	_alloc_cstring(buffer, n, c);
	_insert_str(pos, buffer, n);
	delete buffer;
	return *this;
}

String& String::erase(size_type pos, size_t len) {
	_erase(pos, len);
	return *this;
}

String& String::replace(size_type pos, size_t len, const String& other) {
	_replace(pos, len, other._str, other._strlen);
	return *this;
}

String& String::replace(size_type pos, size_t len, const String& other, size_type subpos, size_t sublen) {
	sublen = _getLength(other, subpos, sublen);
	char* buffer = nullptr;
	_substr(buffer, other._str, subpos, sublen);
	_replace(pos, len, buffer, strlen(buffer));
    delete buffer;
	return *this;
}

String& String::replace(size_type pos, size_t len, const char* s) {
	_replace(pos, len, s, strlen(s));
	return *this;
}

String& String::replace(size_type pos, size_t len, const char* other, size_t n) {
	_replace(pos, len, other, n);
	return *this;
}

String& String::replace(size_type pos, size_t len, size_t n, char c) {
	char* buffer = nullptr;
	_alloc_cstring(buffer, n, c);
	_replace(pos, len, buffer, n);
	delete buffer;
	return *this;
}

void String::swap(String& other) {
	String temp = std::move(*this);
	*this = std::move(other);
	other = std::move(temp);
}

String & String::pop_back() {
	_erase((end() - 1).current.pos, 1);
	return *this;
}

inline void String::_append(const char* other) {
	return _append(other, strlen(other));
}

void String::_append(const char* other, size_t n) {
	if (!other || n == 0)
		return; 
	_increaseCapacity(_strlen + n);
	size_type i;
	for (i = 0; i < n; ++i)
		operator[](_strlen + i) = other[i];

	operator[](_strlen + i) = '\0';
	_setLength(_strlen + n);
}

void String::_insert_str(size_type pos, const char* other) {
	if (other != nullptr)
		_insert_str(pos, other, strlen(other));
}

void String::_insert_str(size_type pos, const char* other, size_t n) {
	if (pos == _strlen)
		return _append(other, n);

	if (pos > _strlen) {
		throw;
	}

	if (n == 0)
		return;

	_increaseCapacity(_strlen + n); 

	if (_str) {
		char* buffer = nullptr;
		_substr(buffer, _str, pos, _strlen);
		_clear_str(pos);
		_append(other, n);
		_append(buffer, strlen(buffer));
		delete buffer;
	} else {
		_append(other, n);
    }
}

void String::_substr(char*& buffer, const char* other, size_type pos, size_t len) const {
	if (other == nullptr)
		throw;
	_alloc_cstring(buffer, len);
	for (size_type i = 0; i < len; ++i)
		buffer[i] = other[pos + i];
}

void String::_erase(size_type pos, size_t len) {
	len = _getLength(*this, pos, len);
	for (size_t i = pos+ len; i < _strlen; ++i) 
		operator[](i - len) = operator[](i);
	_clear_str(_strlen - len);
}

void String::_replace(size_type pos, size_t len, const char* other, size_t n) {
	len = _getLength(*this, pos, len);
	char* buffer = nullptr;
	_substr(buffer, _str, pos + len, _strlen);
	_clear_str(pos);
	char* replace_buffer = nullptr;
	_substr(replace_buffer, other, 0, n);
	_append(replace_buffer);
	_append(buffer);
    delete replace_buffer;
    delete buffer;
}

size_t String::_getLength(const String& str, size_type pos, size_t len) const {
	if (len == npos)
		len = _strlen - pos;

	if (pos + len > str._strlen) {
		throw;	
	}
	return len;
}

const char* String::c_str() const
	return _str;

size_t String::copy(char* s, size_t len, size_type pos) const {
	if (!s)
		throw;
	len = _getLength(*this, pos, len);
	for (size_type i = 0; i < len; ++i)
		*(s + i) = operator[](pos + i);
	return len;
}

size_t String::length() const
	return _strlen;

inline size_t String::size() const
	return length();

size_t String::max_size() const
	return String::npos -1;

void String::resize(size_t n) {
	if (_strlen == n) return; 
	if (_strlen < n) {
		_setLength(n);
		return;
	}
	_clear_str(n);
}

void String::resize(size_type n, char c) {
	if (_strlen == n) return;
	if (_strlen < n) {
		size_type pos = _strlen;
		_setLength(n);
		_fill_str(_str, _strlen, pos, c);
		return;
	}
	_clear_str(n);
}

size_t String::capacity() const
	return _str_cap;

void String::reserve(size_t n) {
	if (_str_cap == n) return;
	if (_str_cap < n) {
		_setCapacity(n);
		return;
	}
	if (_str_cap / 2 > _strlen) {
		_decreaseCapacity(_str_cap / 2);
	}
}

void String::clear()
	_clear_str(0);

bool String::empty() const
	return _strlen ? false : true;

void String::shrink_to_fit()
	_decreaseCapacity(_strlen);

void String::_setLength(const size_t len) {
	if (_strlen > len)
		_clear_str(len);
	else if (_str_cap < len)
		_increaseCapacity(len);
	_strlen = len;
}

void String::_setCapacity(const size_t cap) {
	if (_str_cap == cap && _str)
		return;
	if (cap < _strlen)
		return;
	_str_cap = cap;

	char * buffer = _str;
	_str = nullptr;
	_alloc_cstring(_str, _str_cap);
	if (buffer) { 
		for (size_type i = 0; i < _strlen; ++i)
			operator[](i) = buffer[i];
		operator[](_strlen) = '\0';
	}
	delete buffer;
}

void String::_increaseCapacity(const size_t n) {
	if (_str_cap > n && _str)
		return;

	size_t cap = _str_cap;
	while (cap <= n)
		cap += _increaseBy;
	_increaseBy++;

	_setCapacity(cap);
}

void String::_decreaseCapacity(const size_t cap) {
	if (_str_cap < cap)
		return;

	if (_increaseBy > 15)
		--_increaseBy;
	_setCapacity(cap);
}

void String::_alloc_cstring(char*& buffer,  const size_t n)  const {
	if (buffer)
		throw;
	buffer = new char[n + 1]();
}

void String::_alloc_cstring(char*& buffer, const size_t n, char c) const {
	 _alloc_cstring(buffer, n);
	_fill_str(buffer, n, 0, c);
}

void String::_alloc_cstring(char*& buffer, const size_t n, const String::const_iterator i1, const String::const_iterator i2) const {
	_alloc_cstring(buffer, n);
	String::const_iterator begin = i1;
	for (size_type i = 0; i < n; ++i)
		buffer[i] = *begin++;
}

void String::_fill_str(char* other, const size_t len, const size_type pos, char c) const {
	size_type begin = pos;
	while (begin != len)
		other[begin++] = c;
	other[begin] = '\0';
}

void String::_clear_str(const size_type pos) {
	_fill_str(_str, _strlen, pos, '\0');
	_strlen = pos;
}

void swap(String& lhs, String& rhs) {
	lhs.swap(rhs);
}

String operator+(const String& lhs, const String& rhs) {
	String toReturn = lhs;
	toReturn += rhs;
	return toReturn;
}

String operator+(const String& lhs, const char* rhs) {
	String toReturn = lhs;
	toReturn += rhs;
	return toReturn;
}

String operator+(const char* lhs, const String& rhs) {
	String toReturn = lhs;
	toReturn += rhs;
	return toReturn;
}

String operator+(const String& lhs, char rhs) {
	String toReturn = lhs;
	toReturn += rhs;
	return toReturn;
}

String operator+(char lhs, const String& rhs) {
	String toReturn = rhs;
	toReturn += lhs;
	return toReturn;
}

std::ostream& operator<<(std::ostream& os, const String& str) {
	for (size_t i = 0; i < str.length(); ++i)
		os << str[i];
	return os;
}

std::istream& operator>>(std::istream& is, String& str) {
	str.clear();
	char c;
	do {
		c = is.get();
		if (c == '\n' || c == ' ')
			break;
		str.push_back(c);
	} while (true);
	return is;
}

std::istream& getline(std::istream& is, String& str, char delim) {
	str.clear();
	char c;
	do {
		c = is.get();
		if (c == delim)
			break;
		str.push_back(c);
	} while (true);
	return is;
}

std::istream& getline(std::istream& is, String& str) {
	return getline(is, str, '\n');
}
