#ifndef BIOLOGIST_DNA_H
#define BIOLOGIST_DNA_H

#include "Rna.h"

namespace biologist {
    class Dna {
        Rna *_left_rna;
    public:
        Dna(const Rna &left, const Rna &right);

        Dna(const Dna &right);

        ~Dna();

        bool operator==(const Dna &right) const;

        Dna &operator=(const Dna &right);

        const Rna *getRight() const;

        const Rna *getLeft() const;
    };
}

#endif //BIOLOGIST_DNA_H
