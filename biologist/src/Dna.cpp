#include <iostream>
#include "Dna.h"

namespace biologist {
    Dna::Dna(const Rna &left, const Rna &right) {
        if (!left.isComplementary(right)) {
            throw std::invalid_argument("Can't create DNA from non-Complementary RNAs.");
        }
        _left_rna = new Rna(left);
    }

    Dna::Dna(const Dna &right) {
        delete _left_rna;
        this->_left_rna = new Rna(*right._left_rna);
    }

    Dna &Dna::operator=(const Dna &right) {
        if (&right != this) {
            delete _left_rna;
            _left_rna = new Rna(*right._left_rna);
        }
        return *this;
    }
    //TODO возможны утечки
    const Rna *Dna::getRight() const {
        return (~(*_left_rna)).release();
    }

    const Rna *Dna::getLeft() const {
        return _left_rna;
    }

    bool Dna::operator==(const Dna &right) const {
        bool result = false;
        if (*(this->getLeft()) == *(right.getLeft())) {
            result = true;
        } else {
            auto temp = right.getRight();
            if (*(this->getLeft()) == *temp) {
                result = true;
            }
            delete temp;
        }
        return result;
    }

    Dna::~Dna() {
        delete _left_rna;
    }
}