#include <gtest/gtest.h>
#include "String.hpp"

class TestStr : public ::testing::Test
{
protected:
    void SetUp()
    {
        str = new String("Mate!123");
    }
    void TearDown()
    {
        delete str;
    }
    size_t npos = (size_t) -1;
    String *str;
};


TEST_F(TestStr, Constructor) {
    EXPECT_EQ(str->size(),8);
    EXPECT_STREQ(str->data(),"Mate!123");
    
}
TEST_F(TestStr, Erase){
    str->erase(2,1);
    EXPECT_STREQ(str->data(),"Mae!123");
    auto str_c = *str;
    str->erase();
    EXPECT_STREQ(str->data(),"");
    str_c.erase(3);
    EXPECT_STREQ(str_c.data(),"Mae");
}

TEST_F(TestStr, InsertChar) {
    str->insert(2,3,'&');
    EXPECT_STREQ(str->data(),"Ma&&&te!123");
}

TEST_F(TestStr, InsertCString) {
    str->insert(2,"&&&");
    EXPECT_STREQ(str->data(),"Ma&&&te!123");
}
TEST_F(TestStr, InsertString) {
    auto andStr = new String("&&&");
    str->insert(2,*andStr);
    EXPECT_STREQ(str->data(),"Ma&&&te!123");
    delete andStr;
}
TEST_F(TestStr, FindString){
    auto subStr = new String("te!");
    EXPECT_EQ(str->find(*subStr),2);
    delete subStr;
}
TEST_F(TestStr, FindStringNothing){
    auto subStr = new String("teX");
    EXPECT_EQ(str->find(*subStr),npos); //Почему-то компилятор не видит эту константу в классе.
    delete subStr;
}
TEST_F(TestStr, FindCString){
    char arr[] = "te!";
    EXPECT_EQ(str->find(arr),2);
}
TEST_F(TestStr, FindCStringNothing){
    char arr[] = "teX";
    EXPECT_EQ(str->find(arr),npos);
}
TEST_F(TestStr, FindChar){
    EXPECT_EQ(str->find('!'),4);
}
TEST_F(TestStr,FindCharNothing){
    EXPECT_EQ(str->find('X'),npos);
}

TEST_F(TestStr, Swap) {
    auto anotherStr = new String("ququ");
    str->swap(*anotherStr);
    EXPECT_STREQ(anotherStr->data(),"Mate!123");
    EXPECT_STREQ(str->data(),"ququ");
    String andAnotherStr = *str;
    andAnotherStr.swap(*anotherStr);
    EXPECT_STREQ(str->data(),"ququ");
    EXPECT_STREQ(anotherStr->data(),"ququ");
    EXPECT_STREQ(andAnotherStr.data(),"Mate!123");
    delete anotherStr;
}
TEST_F(TestStr,CompareString){
    auto anotherStr = new String("MateA");
    EXPECT_EQ(str->compare(*anotherStr),-1);
    *anotherStr = "Mate!12";
    EXPECT_EQ(str->compare(*anotherStr),1);
    delete anotherStr;
}
TEST_F(TestStr,CompareCString){
    EXPECT_EQ(str->compare("MateA"),-1);
    EXPECT_EQ(str->compare("Mate!12"),1);
}

TEST_F(TestStr,ReplaceString){
    str->replace(0,1,*(new String("Mem")));
    EXPECT_STREQ(str->data(),"Memate!123");
}
