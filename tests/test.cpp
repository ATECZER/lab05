#include <gtest/gtest.h>
#include "gmock/gmock.h"
#include <Transaction.h>
#include <Account.h>


class MockAccount: public Account{
public:
    MockAccount(int id, int balance):Account(id, balance){}
    MOCK_METHOD(void, Unlock, ());
};
TEST(Account, Init){
    MockAccount test(1,100);
    EXPECT_EQ(test.GetBalance(),100);
    EXPECT_EQ(test.id(),1);
}

class MockTransaction: public Transaction{
public:
    MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};

TEST(Account, GetBalance){
MockAccount acc(1,100);
EXPECT_EQ(acc.Account::GetBalance(), 100);
}
