#include <gtest/gtest.h>
#include <experimental/filesystem>
#include <cstdio>
#include <cstring>

extern "C" {
#include "../lib/de_base64.h"
#include "../exlib/b64/b64.h"
}

TEST(BasicTests, DISABLED_EncodeFunction) {
    for (unsigned int i = 0; i < UINT32_MAX; ++i) {
        unsigned int my_temp, ext_temp;
        encode(&i, &my_temp);
        lencodeblock((unsigned char *) &i, (unsigned char *) &ext_temp, 3);
        EXPECT_EQ(my_temp, ext_temp);
    }
}


TEST(BasicTests, EncodeFile) {
    std::string path = "../tests/test_files/";
    char *temp = (char *) malloc(sizeof(char) * 100000), *temp2 = (char *) malloc(sizeof(char) * 100000);
    for (int i = 0; i <= 5; ++i) {
        FILE *output_my = fmemopen(temp, 100000, "w");
        FILE *output_lib = fmemopen(temp2, 100000, "w");
        FILE *input = fopen((path + std::to_string(i)).c_str(), "r");
        encode_file(input, output_my);
        fclose(input);
        input = fopen((path + std::to_string(i)).c_str(), "r");
        lencode(input, output_lib, 72);
        fclose(output_my);
        fclose(output_lib);
        EXPECT_STREQ(temp, temp2);
    }
}

TEST(BasicTests, Decode) {
    FILE *input = fopen("../tests/test_files/d_6", "r");
    const char *example = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
    unsigned char result[269];
    for (int i = 0; i < 91; ++i) {
        unsigned int temp;
        unsigned char out[3];
        if (i!= 0 && i % 18 == 0) { //хак провтив переносов строк
            fseek(input, ftell(input) + 1, SEEK_SET);
        }
        fread(&temp, 1, sizeof(int), input);

        decode(&temp, out);
        for (int j = 0; j < 3; ++j) {
            result[i * 3 + j] = out[j];
        }
    }
    EXPECT_STREQ(const_cast<char*>(example), (char *)result);
}
TEST(BasicTests,DecodeFile){
    std::string path = "../tests/test_files/d_";
    char *temp = (char *) malloc(sizeof(char) * 100000), *temp2 = (char *) malloc(sizeof(char) * 100000);
    for (int i = 0; i <= 5; ++i) {
        FILE *output_my = fmemopen(temp, 100000, "w");
        FILE *output_lib = fmemopen(temp2, 100000, "w");
        FILE *input = fopen((path + std::to_string(i)).c_str(), "r");
        decode_file(input, output_my);
        fclose(input);
        input = fopen((path + std::to_string(i)).c_str(), "r");
        ldecode(input, output_lib);
        fclose(output_my);
        fclose(output_lib);
        EXPECT_STREQ(temp, temp2);
    }
}

