#include <iostream>
#include <cassert>

#include "src/Rna.h"

using namespace biologist;
using namespace std;
int main() {
    auto *o = new Rna(Rna::Nucleotide::T, 32);
    string temp = (string)*o;
    cout << (char)Rna::Nucleotide::G << endl;
}