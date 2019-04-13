#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include "Customer.h"
#include "Address.h"
#include "Telephone.h"

using namespace std;
using namespace testing;
using namespace CommonLayer;

int main(int argc, char** argv)
{
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Customer_Test, Customer_ctor)
{
    int custID {-1};
    ptime nullTime;
    Customer customer{custID, "Test Customer", "www.testcustomer.com", nullTime};

    ASSERT_EQ(custID, customer.getID());
}

TEST(Customer_Test, Customer_copy_ctor)
{
    int custID {-1};
    ptime nullTime;
    Customer customer{custID, "Test Customer", "www.testcustomer.com", nullTime};

    ASSERT_EQ(custID, customer.getID());

    Customer customerCopy{customer};
    ASSERT_EQ(customer.getCustomerName(), customerCopy.getCustomerName());
}

TEST(Customer_Test, Customer_copy_assignment_operator)
{
    int custID {999};
    ptime nullTime;
    Customer customer{custID, "Test Customer", "www.testcustomer.com", nullTime};

    EXPECT_EQ(custID, customer.getID());

    Customer customerAssign{1, "Assigned Customer", "www.assignment.com", nullTime};
    EXPECT_EQ(1, customerAssign.getID());
    EXPECT_NE(customer.getCustomerName(), customerAssign.getCustomerName());

    customerAssign = customer;
    ASSERT_EQ(customer.getID(), customerAssign.getID());
    ASSERT_EQ(customer.getCustomerName(), customerAssign.getCustomerName());
    ASSERT_EQ(customer.getWebsite(), customerAssign.getWebsite());

}