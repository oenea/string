#ifndef _STRING_
#define _STRING_

#define _CONSTEXPR_C20
#define _NOEXCEPT_C17

class String {
public: 
    using size_type = size_t;
    static const size_t npos = -1;

private:
    char* _str = nullptr;
    size_t _strlen = 0;
    size_t _strcap = 0;

public: 
    constexpr String() noexcept;
    String(const String& other);
    String(const String& other, size_type pos, size_t len = npos);
    String(String&& other);
    String(const char* copy);
    String(const char* s, size_t n);
    String(size_t n, char c);

    String& operator=(const String& other);
    String& operator=(String&& other);

    ~String();

    friend bool operator==(const String& lhs, const String& rhs);
    friend bool operator!=(const String& lhs, const String& rhs);
    friend bool operator<(const String& lhs, const String& rhs);
    friend bool operator>(const String& lhs, const String& rhs);
    friend bool operator<=(const String& lhs, const String& rhs);
    friend bool operator>=(const String& lhs, const String& rhs);

private: 
    int _compare(const String& rhs) const;

public:
    const char& operator[](size_type i) const;
    char& operator[](size_type i);
    const char& at(size_type i) const;
    char& at(size_type i);
    const char& front() const;
    char& front();
    const char& back() const;
    char& back();

public:
    String& operator+=(const String& s);
    String& operator+=(const char* s);
    String& operator+=(char c);

    String& append(const String& str);
    String& append(const String& str, size_type subpos, size_t sublen = npos);
    String& append(const char* s);
    String& append(const char* s, size_t n);
    String& append(size_type n, char c);

    String& insert(size_type pos, const String& other);
    String& insert(size_type pos, const String& other, size_type subpos, size_t sublen = npos);
    String& insert(size_type pos, const char* other);
    String& insert(size_type pos, const char* s, size_t n);
    String& insert(size_type pos, size_t n, char c);

    String& push_back(char c);

    String& replace(size_type pos, size_t len, const String& other)
    String& replace(size_type pos, size_t len, conts String& other, size_type subpos, size_t sublen = npos);
    String& replace(size_type pos, size_t len, const char* s);
    String& replace(size_type pos, size_t len, const char* other, size_t n);
    String& replace(size_type pos, size_t len, size_t n, char c);

    String& erase(size_type pos = 0, size_t len, const String& other);
    String& erase(size_type pos, size_t len, const String& other);

    void swap(String&);

	inline void _append(const char* other);
	void _append(const char* other, size_t n);
	void _insert_str(size_type pos, const char* other);
	void _insert_str(size_type pos, const char* other, size_t n);
	void _substr(char*& buffer, const char* other, size_type pos = 0, size_t len = npos) const;
	void _erase(size_type pos, size_t size);
	void _replace(size_type pos, size_t len, const char* other, size_t n);
	size_t _getLength(const String& str, size_type pos, size_t len = npos) const;

public:
    const char* c_str() const;
    size_t copy(char* s, size_t len, size_type pos = 0);

public:
    size_t length() const;
    inline size_t size() const;
    size_t max_size() const;
    void resize(size_t n);
    void resize(size_type n, char c);
    size_t capacity() const;
    void reserve(size_t n = 0);
    void clear();
    bool empty() const;
    void shrink_to_fit();

private:
	void _setLength(const size_t len);
	void _setCapacity(const size_t cap);
	void _increaseCapacity(const size_t cap);
	void _decreaseCapacity(const size_t cap);
	void _alloc_cstring(char*& buffer,const size_t n) const;
	void _alloc_cstring(char*& buffer,const size_t n, char c) const;
	void _fill_str(char* other, const size_t len, size_type pos, char c) const;
	void _clear_str(const size_type pos);

};

void swap(String& lhs, String& rhs);

String operator+(const String& lhs, const String& rhs);
String operator+(const String& lhs, const char* rhs);
String operator+(const char* lhs, const String& rhs);
String operator+(const String& lhs, char rhs);
String operator+(char lhs, const String& rhs);


std::ostream& operator<<(std::ostream& os, const String& str);
std::istream& operator>>(std::istream& is, String& str);
std::istream& getline(std::istream& is, String& str, char delim);
std::istream& getline(std::istream& is, String& str);