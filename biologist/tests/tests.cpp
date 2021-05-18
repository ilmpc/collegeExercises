#include <gtest/gtest.h>
#include "../src/Dna.h"
#include "../src/Rna.h"

using namespace biologist;
using namespace std;

TEST(BasicTests, CreateRna) {
    auto test = new Rna(Rna::Nucleotide::T, 32);
    EXPECT_EQ((string) *test, "T T T T T T T T T T T T T T T T T T T T T T T T T T T T T T T T");
    delete test;
    test = new Rna(Rna::Nucleotide::G, 100);
    auto test2 = new Rna(Rna::Nucleotide::A, 10);
    auto test3 = *test + *test2;
    for (size_t i = 0; i < test->getLength(); ++i) {
        EXPECT_EQ((Rna::Nucleotide) (*test3)[i], Rna::Nucleotide::G);
    }
    for (size_t i = test->getLength(); i < test->getLength() + test2->getLength(); ++i) {
        EXPECT_EQ((*test3)[i], Rna::Nucleotide::A);
    }
    delete test;
    delete test2;

}
TEST(BasicTests, RnaCheckEq){
    auto test = new Rna(0);
    for (size_t i = 0; i < 4'000'000; ++i) { //40s for 4*10^8
        test->push((Rna::Nucleotide)(i));
    }
    //cout << test->getLength() << '\n' << test->getCapacity() << endl;
    for (int j = 1; j < 100; ++j) {
        (*test)[j] = (*test)[0];
        EXPECT_EQ((*test)[j],Rna::Nucleotide::A);
    }
    test->split(1000);
    delete test;
}

TEST(BasicTests, CreateDna){
    auto dnaAT = new Dna(Rna(Rna::Nucleotide::A,128),Rna(Rna::Nucleotide::T, 128));
    auto rnaT = new Rna(Rna::Nucleotide::T, 128);
    auto dnaTA = new Dna(*rnaT,*~(*rnaT));
    EXPECT_EQ(*dnaAT,*dnaTA);
    delete dnaAT;
    delete dnaTA;
    delete rnaT;
}