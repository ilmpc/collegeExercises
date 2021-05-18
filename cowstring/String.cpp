// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <cstring>
#include <algorithm>
#include <stdexcept>
#include "String.hpp"


String::String() : _refCounter(new size_t(1)), _capacity(2048), _data(new char[_capacity]) {
    _data[0] = '\0';
}

String::String(const char *str) : String(str, CStringLen(str)) {
}

String::String(const char *str, size_t n) : _refCounter(new size_t(1)) {
    if (str == nullptr) {
        throw std::invalid_argument("Null pointer");
    }
    if (n == npos) {
        _capacity = CStringLen(str);
    } else {
        _capacity = n + 1;
    }
    _data = new char[_capacity];
    std::copy_n(str, n, _data);
    _data[n] = '\0';
}

String::String(size_t n, char c) : _refCounter(new size_t(1)), _capacity(n + 1),
                                   _data(new char[_capacity]) {
    std::fill_n(_data, n, c);
    _data[n] = '\0';
}

String::String(const String &str) : _refCounter(str._refCounter), _capacity(str._capacity),
                                    _data(str._data) {
    ++(*_refCounter);
}

String::String(const String &str, size_t pos, size_t len) {
    size_t sourceSize = str.size();
    if (sourceSize < pos) {
        throw std::out_of_range("Can't copy string from pos, that bigger than size of string.");
    }
    if (len == npos) {
        _capacity = sourceSize - pos + 1;
    } else {
        if (sourceSize < pos + len) {
            throw std::out_of_range("Not enough elements in string. Use without length to copy to the end of string.");
        }
        _capacity = len + 1;
    }
    _refCounter = new size_t(1);
    _data = new char[_capacity];
    std::copy_n(str._data + pos, _capacity - 1, _data);
    _data[_capacity - 1] = '\0';
}

String::~String() {
    if (_refCounter) {
        --(*_refCounter);
        if (*_refCounter == 0) {
            delete _refCounter;
            delete[] _data;
        }
    }
}

size_t String::size() const {
    return CStringLen(_data);
}

size_t String::capacity() const {
    return _capacity;
}

void String::reserve(size_t n) {
    if (n > _capacity) {
        _capacity = n + 1;
        auto sourceSize = this->size() + 1; //+null
        auto tempData = new char[_capacity];
        std::copy_n(this->_data, sourceSize, tempData);
        if (*_refCounter == 1) {
            delete[] this->_data;
        } else {
            --(*_refCounter);
            _refCounter = new size_t(1);
        }
        this->_data = tempData;
    }
}

void String::clear() {
    if (*_refCounter > 1) {
        --(_refCounter);
        _refCounter = new size_t(1);
        _data = new char[_capacity];
    }
    _data[0] = '\0';
}

bool String::empty() const {
    if (_capacity == 0) {
        return true;
    } else {
        return _data[0] == '\0';
    }
}

char &String::at(size_t pos) {
    if (pos > this->size() + 1) {
        throw std::out_of_range("Access to undefined memory.");
    }
    return (*this)[pos];
}

const char &String::at(size_t pos) const {
    if (pos > this->size() + 1) {
        throw std::out_of_range("Access to undefined memory.");
    }
    return (*this)[pos];
}

char &String::operator[](size_t pos) {
    if (*_refCounter > 1) {
        auto tempData = new char[_capacity];
        std::copy_n(this->_data, this->size(), tempData);
        --(_refCounter);
        _refCounter = new size_t(1);
        this->_data = tempData;
    }
    return _data[pos];
}

const char &String::operator[](size_t pos) const {
    return _data[pos];
}

char &String::back() {
    if (_capacity == 0) {
        throw std::out_of_range("Access to undefined memory.");
    }
    return _data[this->size()];
}

const char &String::back() const {
    if (_capacity == 0) {
        throw std::out_of_range("Access to undefined memory.");
    }
    return _data[this->size()];
}

char &String::front() {
    if (_capacity == 0) {
        throw std::out_of_range("Access to undefined memory.");
    }
    return _data[0];
}

const char &String::front() const {
    if (_capacity == 0) {
        throw std::out_of_range("Access to undefined memory.");
    }
    return _data[0];
}

String &String::operator+=(const String &str) {
    if (str.empty()) {
        return *this;
    }
    if (*_refCounter > 1 || this->size() + str.size() + 1 > _capacity) {
        if (*_refCounter > 1) {
            --(*_refCounter);
            _refCounter = new size_t(1);
        }
        _capacity = this->size() + str.size() + 1;
        auto tempData = new char[_capacity];
        std::copy_n(this->_data, this->size(), tempData);
        std::copy_n(str._data, str.size(), tempData + this->size());
        tempData[_capacity - 1] = '\0';
        _data = tempData;
    } else {
        std::copy_n(str._data, str.size(), _data + this->size());
        _data[this->size() + str.size()] = '\0';
    }
    return *this;
}

String &String::operator+=(const char *str) {
    if (str == nullptr) {
        throw std::invalid_argument("Null pointer");
    }
    if (str[0] == '\0') {
        return *this;
    }
    size_t r_sz = CStringLen(str);
    if (*_refCounter > 1 || this->size() + r_sz + 1 > _capacity) {
        if (*_refCounter > 1) {
            --(*_refCounter);
            _refCounter = new size_t(1);
        }
        _capacity = this->size() + r_sz + 1;
        auto tempData = new char[_capacity];
        std::copy_n(this->_data, this->size(), tempData);
        std::copy_n(str, r_sz, tempData + this->size());
        tempData[_capacity - 1] = '\0';
        _data = tempData;
    } else {
        std::copy_n(str, r_sz, _data + this->size());
        _data[this->size() + r_sz] = '\0';
    }
    return *this;
}

String &String::operator+=(char c) {
    if (c == '\0') {
        return *this;
    }
    if (*_refCounter > 1 || this->size() + 2 > _capacity) {
        if (*_refCounter > 1) {
            --(*_refCounter);
            _refCounter = new size_t(1);
        }
        _capacity = this->size() + 2;
        auto tempData = new char[_capacity];
        std::copy_n(this->_data, this->size(), tempData);
        tempData[_capacity - 2] = c;
        tempData[_capacity - 1] = '\0';
        _data = tempData;
    } else {
        _data[this->size() - 2] = c;
        _data[this->size() - 1] = '\0';
    }
    return *this;
}

String &String::operator=(const String &str) {
    if (this == &str) {
        return *this;
    }
    --(*_refCounter);
    if (*_refCounter == 0) {
        delete _refCounter;
        delete[] _data;
    }
    _refCounter = str._refCounter;
    ++(*_refCounter);
    _capacity = str._capacity;
    _data = str._data;
    return *this;
}

String &String::operator=(const char *str) {
    if (str == nullptr) {
        throw std::invalid_argument("Null pointer");
    }
    if (this->_data == str) {
        return *this;
    }
    size_t r_sz = CStringLen(str);
    --(*_refCounter);
    if (*_refCounter == 0) {
        delete _refCounter;
        delete[] _data;
    }
    _refCounter = new size_t(1);
    _capacity = r_sz + 1;
    _data = new char[_capacity];
    std::copy_n(str, r_sz, _data);
    _data[r_sz] = '\0';
    return *this;
}

String &String::insert(size_t pos, const String &str) {
    if (pos > this->size()) {
        throw std::out_of_range("Position is over the string.");
    }
    if (str.empty()) {
        return *this;
    }
    if (*_refCounter > 1 || this->size() + str.size() + 1 > _capacity) {
        if (*_refCounter > 1) {
            --(*_refCounter);
            _refCounter = new size_t(1);
        }
        _capacity = this->size() + str.size() + 1;
        auto tempData = new char[_capacity];
        std::copy_n(this->_data, pos, tempData);
        std::copy_n(str._data, str.size(), tempData + pos); //TODO check ranges!
        std::copy_n(this->_data + pos, this->size() - pos, tempData + pos + str.size());
        tempData[_capacity - 1] = '\0';
        _data = tempData;
    } else {
        std::copy_n(_data + pos, this->size() - pos, _data + pos + str.size());
        std::copy_n(str._data, str.size(), _data + pos); //TODO check ranges!
        _data[this->size() + str.size()] = '\0';
    }
    return *this;

}

String &String::insert(size_t pos, const char *str) {
    if (str == nullptr) {
        throw std::invalid_argument("Null pointer");
    }
    if (pos > this->size()) {
        throw std::out_of_range("Position is over the string.");
    }
    if (str[0] == '\0') {
        return *this;
    }
    size_t r_sz = CStringLen(str);
    if (*_refCounter > 1 || this->size() + r_sz + 1 > _capacity) {
        if (*_refCounter > 1) {
            --(*_refCounter);
            _refCounter = new size_t(1);
        }
        _capacity = this->size() + r_sz + 1;
        auto tempData = new char[_capacity];
        std::copy_n(this->_data, pos, tempData);
        std::copy_n(str, r_sz, tempData + pos); //TODO check ranges!
        std::copy_n(this->_data + pos, this->size() - pos, tempData + pos + CStringLen(str));
        tempData[_capacity - 1] = '\0';
        _data = tempData;
    } else {
        std::copy_n(_data + pos, this->size() - pos, _data + pos + CStringLen(str));
        std::copy_n(str, r_sz, _data + pos); //TODO check ranges!
        _data[this->size() + r_sz] = '\0';
    }
    return *this;
}

String &String::insert(size_t pos, size_t n, char c) {
    if (pos > this->size()) {
        throw std::out_of_range("Position is over the string.");
    }
    if (*_refCounter > 1 || this->size() + n + 1 > _capacity) {
        if (*_refCounter > 1) {
            --(*_refCounter);
            _refCounter = new size_t(1);
        }
        _capacity = this->size() + n + 1;
        auto tempData = new char[_capacity];
        std::copy_n(this->_data, pos, tempData);
        std::fill_n(tempData + pos, n, c); //TODO check ranges!
        std::copy_n(this->_data + pos, this->size() - pos, tempData + pos + n);
        tempData[_capacity - 1] = '\0';
        _data = tempData;
    } else {
        std::copy_n(_data + pos, this->size() - pos, _data + pos + n);
        std::fill_n(_data + pos, n, c); //TODO check ranges!
        _data[this->size() + n] = '\0';
    }
    return *this;
}

String &String::erase(size_t pos, size_t len) {
    if (len == 0) {
        return *this;
    }
    if (*_refCounter > 1) {
        --(*_refCounter);
        _refCounter = new size_t(1);
        if (len == npos) {
            len = this->size() - pos;
        }
        _capacity = this->size() - len + 1;
        auto tempData = new char[_capacity];
        std::copy_n(_data, pos, tempData);
        std::copy_n(_data + pos + len, this->size() - pos - len, tempData + pos);
        tempData[_capacity - 1] = '\0';
        _data = tempData;
    } else {
        if (len == npos) {
            len = this->size() - pos;
        }
        auto sourceSize = this->size();
        std::copy_n(_data + pos + len, sourceSize - pos - len, _data + pos);
        _data[sourceSize - len] = '\0';
    }
    return *this;
}

String &String::replace(size_t pos, size_t len, const String &str) {
    if (pos > this->size()) {
        throw std::out_of_range("Position is over the string.");
    }
    size_t r_sz = this->size();
    if (pos + len > r_sz) {
        len = npos;
    }
    if (len == npos) {
        _data[pos] = '\0';
        return insert(pos, str);
    }

    std::copy_n(_data + pos + len, r_sz - pos - len, _data + pos);
    _data[r_sz - len] = '\0';
    return insert(pos, str);
}

String &String::replace(size_t pos, size_t len, const char *str) {
    if (str == nullptr) {
        throw std::invalid_argument("Null pointer");
    }
    if (pos > this->size()) {
        throw std::out_of_range("Position is over the string.");
    }
    size_t r_sz = this->size();
    if (pos + len > r_sz) {
        len = npos;
    }
    if (len == npos) {
        _data[pos] = '\0';
        return insert(pos, str);
    }

    std::copy_n(_data + pos + len, r_sz - pos - len, _data + pos);
    _data[r_sz - len] = '\0';
    return insert(pos, str);
}

String &String::replace(size_t pos, size_t len, size_t n, char c) {
    if (pos > this->size()) {
        throw std::out_of_range("Position is over the string.");
    }
    size_t r_sz = this->size();
    if (pos + len > r_sz) {
        len = npos;
    }
    if (len == npos) {
        _data[pos] = '\0';
        return insert(pos, n, c);
    }

    std::copy_n(_data + pos + len, r_sz - pos - len, _data + pos);
    _data[r_sz - len] = '\0';
    return insert(pos, n, c);
}

void String::swap(String &str) {
    if (this == &str) {
        return;
    }
    if (*this->_refCounter > 1) {
        --(*this->_refCounter);
        this->_refCounter = new size_t(1);
        auto tempData = new char[this->_capacity];
        std::copy_n(this->_data, CStringLen(this->_data), tempData);
        tempData[CStringLen(this->_data)] = '\0';
        this->_data = tempData;
    }
    if (*str._refCounter > 1) {
        --(*str._refCounter);
        str._refCounter = new size_t(1);
        auto tempData = new char[str._capacity];
        std::copy_n(str._data, CStringLen(str._data), tempData);
        tempData[CStringLen(str._data)] = '\0';
        str._data = tempData;
    }
    auto t_refCounter = this->_refCounter;
    auto t_capacity = this->_capacity;
    auto t_data = this->_data;
    _refCounter = str._refCounter;
    _capacity = str._capacity;
    _data = str._data;
    str._refCounter = t_refCounter;
    str._capacity = t_capacity;
    str._data = t_data;
}

const char *String::data() const {
    return _data;
}

size_t String::find(const String &str, size_t pos) const {
    size_t r_sz = str.size();
    if (r_sz == 0) {
        return npos;
    }
    size_t l_sz = this->size();
    if (pos > l_sz) {
        return npos;
    }
    for (size_t i = pos; i < l_sz; ++i) {
        size_t beginSubStr = npos;
        for (size_t j = 0; j < r_sz && _data[i] == str._data[j]; ++j) {
            if (!j) {
                beginSubStr = i;
            }
            ++i;
            if (j == r_sz - 1) {
                return beginSubStr;
            }
        }
    }
    return npos;
}

size_t String::find(const char *str, size_t pos) const {
    if (str == nullptr) {
        throw std::invalid_argument("Null pointer");
    }
    size_t l_sz = this->size();
    size_t r_sz = CStringLen(str);
    if (str[0] == '\0') {
        return npos;
    }
    if (pos > l_sz) {
        return npos;
    }
    for (size_t i = pos; i < l_sz; ++i) {
        size_t beginSubStr = npos;
        for (size_t j = 0; j < r_sz && _data[i] == str[j]; ++j) {
            if (!j) {
                beginSubStr = i;
            }
            ++i;
            if (j == r_sz - 1) {
                return beginSubStr;
            }
        }
    }
    return npos;
}

size_t String::find(char c, size_t pos) const {
    size_t l_sz = this->size();
    if (pos > l_sz) {
        return npos;
    }
    for (size_t i = pos; i < l_sz; ++i) {
        if (_data[i] == c) {
            return i;
        }
    }
    return npos;
}

String String::substr(size_t pos, size_t len) const {
    return String(*this, pos, len);
}

int String::compare(const String &str) const {
    size_t l_sz = size();
    size_t r_sz = str.size();
    for (size_t i = 0; i < std::min(l_sz, r_sz); ++i) {
        if (_data[i] > str._data[i]) {
            return 1;
        }
        if (_data[i] < str._data[i]) {
            return -1;
        }
    }
    if (l_sz < r_sz)
        return -1;
    if (l_sz > r_sz)
        return 1;
    return 0;
}

int String::compare(const char *str) const {
    if (str == nullptr) {
        throw std::invalid_argument("Null pointer");
    }
    size_t l_sz = size();
    size_t r_sz = CStringLen(str);
    for (size_t i = 0; i < std::min(l_sz, r_sz); ++i) {
        if (_data[i] > str[i]) {
            return 1;
        }
        if (_data[i] < str[i]) {
            return -1;
        }
    }
    if (l_sz < r_sz)
        return -1;
    if (l_sz > r_sz)
        return 1;
    return 0;
}

size_t String::countRef() const {
    return *_refCounter;
}

size_t String::CStringLen(const char *str) const {
    if (str == nullptr) {
        throw std::invalid_argument("Null pointer");
    }
    if (str[0] == '\0') {
        return 0;
    } else {
        return strlen(str);
    }
}
