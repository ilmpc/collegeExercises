#include "Rna.h"

namespace biologist {
    Rna::Rna() : Rna(STD_SIZE) {}

    Rna::Rna(size_t capacity_Nuc) : _capacity_Size_t(NucltoSize_T(capacity_Nuc)), _length(0),
                                    _data(new size_t[_capacity_Size_t]) {}


    Rna::Rna(size_t capacity_Size_t, void *) : _capacity_Size_t(capacity_Size_t), _length(0),
                                               _data(new size_t[capacity_Size_t]) {}

    Rna::Rna(Nucleotide n, size_t length) : Rna(length) {
        _length = length;
        size_t temp = 0;
        if ((size_t) n != 0)
            for (size_t i = 0; i < sizeof(size_t) * 8; i += 2) {
                temp |= static_cast<size_t>(n) << i;
            }
        std::fill_n(_data, _capacity_Size_t, temp);
    }

    Rna::Rna(size_t capacity_Size_t, size_t length, size_t *data) : _capacity_Size_t(capacity_Size_t), _length(length),
                                                                    _data(data) {}

    Rna::Rna(const Rna &p) : Rna(p._capacity_Size_t, nullptr) {
        _length = (p.getLength());
        for (int i = 0; i < _capacity_Size_t; ++i) {
            this->_data[i] = p._data[i];
        }
    }

    Rna::~Rna() {
        delete[] _data;
    }

    Rna &Rna::split(size_t index) {
        size_t length = index + 1;
        if (this->_length < length) {
            throw std::length_error("Can't split RNA that haven't enough Nucleotides");
        }
        size_t capacity_Size_t = NucltoSize_T(length);
        this->_length = length;
        this->_capacity_Size_t = capacity_Size_t;
        auto *data = new size_t[capacity_Size_t];
        for (int i = 0; i < capacity_Size_t; ++i) {
            data[i] = this->_data[i];
        }
        delete[] this->_data;
        this->_data = data;
        return *this;
    }

    size_t Rna::getCapacity() const {
        return (this->_capacity_Size_t) * sizeof(size_t) / 4;
    }

    size_t Rna::getLength() const {
        return this->_length;
    }

    bool Rna::operator==(Rna const &right) const {
        if (this->_capacity_Size_t != right._capacity_Size_t) {
            return false;
        }
        if (this->_length != right._length) {
            return false;
        }
        int i;
        for (i = 0; i < right._capacity_Size_t - 1; ++i) {
            if (this->_data[i] != right._data[i])
                return false;
        }
        i = i * sizeof(size_t) / 4;
        for (int j = i; j < right._length; ++j) {
            if ((*this)[j] != right[j])
                return false;
        }
        return true;
    }

    bool Rna::operator!=(Rna const &right) const {
        return !(operator==(right));
    }

    std::unique_ptr<Rna> Rna::operator~() const {
        auto *temp = new size_t[this->_capacity_Size_t];
        for (int i = 0; i < this->_capacity_Size_t; ++i) {
            temp[i] = ~(this->_data[i]);
        }
        return std::make_unique<Rna>(this->_capacity_Size_t, this->getLength(), temp);
    }

    Rna &Rna::operator=(Rna const &right) {
        if (this != &right) {
            auto temp = new size_t[_capacity_Size_t]; //to throw bad_alloc without mem corruption
            delete[] _data;
            this->_capacity_Size_t = right._capacity_Size_t;
            this->_length = right._length;
            _data = temp;
            for (int i = 0; i < NucltoSize_T(_length); ++i) {
                _data[i] = right._data[i];
            }
        }
        return *this;
    }

    bool Rna::isComplementary(Rna const &right) const {
        return *~right == *this;
    }

    std::unique_ptr<Rna> Rna::operator+(Rna const &right) const {
        size_t new_length = this->_length + right._length;
        std::unique_ptr<Rna> result = std::make_unique<Rna>(new_length);
        *result = *this;
        for (size_t i = 0; i < right._length; ++i) {
            (*result)[result->_length + i] = right[i];
        }
        result->_length = new_length;
        return result;
    }

    Rna::_Nucleotide_Reference Rna::operator[](size_t const index){
        if (index < Size_TtoNucl(_capacity_Size_t)) {
            return _Nucleotide_Reference(_data + index / (sizeof(size_t) * 4), index % (sizeof(size_t) * 4));
        } else {
            throw std::out_of_range("Can't access unallocated memory.");
        }
    }

    Rna::Nucleotide Rna::operator[](size_t const index) const {
        if (index < _length) {
            return (Nucleotide) _Nucleotide_Reference(_data + index / (sizeof(size_t) * 4),
                                                            index % (sizeof(size_t) * 4));
        } else {
            throw std::out_of_range("Can't access unallocated memory.");
        }
    }

    Rna::operator std::string() {
        std::unique_ptr<char[]> result(new char[this->_length * 2]);
        size_t i;
        for (i = 0; i < _length * 2; i += 2) {
            (result)[i] = (*this)[i / 2];
            (result)[i + 1] = ' ';
        }
        return std::string(result.get(), i - 1);
    }

    void Rna::push(Rna::Nucleotide n) {
        if (_length >= Size_TtoNucl(_capacity_Size_t)) {
            size_t temp = Size_TtoNucl(_capacity_Size_t) * STD_GROWTH_RATE;
            this->resize(temp != 0 ? temp : STD_SIZE);
        }
        (*this)[_length] = n;
        ++_length;
    }

    Rna::Nucleotide Rna::pop() {
        return (*this)[--_length];
    }

    Rna &Rna::resize(size_t new_size) {
        if (new_size < _length) {
            throw std::length_error("Can't make capacity less than stored data.");
        }
        _capacity_Size_t = NucltoSize_T(new_size);
        auto new_data = new size_t[_capacity_Size_t];
        for (int i = 0; i < NucltoSize_T(_length); ++i) {
            new_data[i] = _data[i];
        }
        delete[] _data;
        _data = new_data;
        return *this;
    }

    Rna::_Nucleotide_Reference::_Nucleotide_Reference(size_t *blockdata, size_t place) : _datablock(blockdata),
                                                                                         _place_bit(place * 2) {}

    Rna::_Nucleotide_Reference::operator Nucleotide() const {
        return get();
    }

    void Rna::_Nucleotide_Reference::set(Rna::Nucleotide n) {
        size_t mask0 = ~((size_t) 0b11 << (_place_bit));
        size_t mask = static_cast<size_t>(n) << (_place_bit);
        *_datablock &= mask0;
        *_datablock |= mask;
    }

    Rna::Nucleotide Rna::_Nucleotide_Reference::get() const {
        size_t mask = (size_t) 0b11 << (_place_bit);
        size_t result = (*_datablock & mask) >> (_place_bit);
        assert(result >= 0 && result <= 3);
        return static_cast<Rna::Nucleotide>(result);
    }

    bool Rna::_Nucleotide_Reference::operator==(const Rna::_Nucleotide_Reference &right) const {
        return this->get() == right.get();
    }

    bool Rna::_Nucleotide_Reference::operator!=(const Rna::_Nucleotide_Reference &right) const {
        return this->get() != right.get();
    }

    Rna::_Nucleotide_Reference &Rna::_Nucleotide_Reference::operator=(const Rna::Nucleotide right) {
        this->set(right);
        return *this;
    }

    Rna::_Nucleotide_Reference &Rna::_Nucleotide_Reference::operator=(const Rna::_Nucleotide_Reference &right) {
        this->set(right.get());
        return *this;
    }

    Rna::_Nucleotide_Reference::operator char() const {
        switch (this->get()) {
            case Nucleotide::A:
                return 'A';
            case Nucleotide::G:
                return 'G';
            case Nucleotide::C:
                return 'C';
            case Nucleotide::T:
                return 'T';
            default:
                return NULL;
        }
    }
}
