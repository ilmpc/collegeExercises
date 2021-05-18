#include <gtest/gtest.h>
#include "String.hpp"


TEST(Construct, Default) {
    auto str = new String();
    EXPECT_EQ(str->countRef(), 1);
    delete str;
}

TEST(Construct, CStringNullptr) {
    String *str;
    EXPECT_ANY_THROW(str = new String(nullptr));
}

TEST(Construct, CharNull) {
    auto str = new String(10, '\0');
    EXPECT_EQ(str->capacity(), 11);
    EXPECT_EQ(str->size(), 0);
}

TEST(Size, Default) {
    auto str = new String();
    EXPECT_EQ(str->size(), 0);
    delete str;
}

TEST(Size, CString) {
    auto str = new String("123");
    EXPECT_EQ(str->size(), 3);
    delete str;
}

TEST(Size, CStringPart) {
    auto str = new String("12356", 2);
    EXPECT_EQ(str->size(), 2);
    delete str;
}

TEST(Size, String) {
    auto str = new String("12345");
    auto str2 = new String(*str);
    EXPECT_EQ(str->size(), str->size());
    delete str;
    delete str2;
}

TEST(replace, stringOverLen) {
    auto str = new String("mux");
    auto str2 = String();
    EXPECT_STREQ(str->replace(0, 10, str2).data(), "");
}

TEST(replace, stringStart) {
    auto str = new String("muxwri");
    auto str2 = String();
    EXPECT_STREQ(str->replace(0, 2, str2).data(), "xwri");
}

TEST(replace, stringMiddle) {
    auto str = new String("muxwri");
    auto str2 = String("qwe");
    EXPECT_STREQ(str->replace(1, 2, str2).data(), "mqwewri");
}

TEST(replace, CStringMiddle) {
    auto str = new String("muxwri");
    EXPECT_STREQ(str->replace(1, 2, "qwe").data(), "mqwewri");
}