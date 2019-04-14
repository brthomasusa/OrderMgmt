#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include "Customer.h"
#include "CustomerManager.h"
#include "MockRepository.h"
#include "MockUnitOfWork.h"

using namespace std;
using namespace testing;
using namespace CommonLayer;
using namespace BusinessLayer;

int main(int argc, char** argv)
{
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(CustomerManager_Test, CustomerManager_getById)
{
    NiceMock<MockRepository> mockRepo;
    NiceMock<MockUnitOfWork> mockUow;

    int custID {3};
    ptime nullTime;
    shared_ptr<Customer> customerObj {make_shared<Customer>(custID, "Test Customer", "www.testcustomer.com", nullTime)};

    {
        InSequence s;
        EXPECT_CALL(mockRepo, findById(An<int>())).Times(1).WillOnce(Return(customerObj));
    }

    CustomerManager customerMgr {mockUow, mockRepo};
    shared_ptr<DomainObject> customer {customerMgr.getById(custID)};
}

TEST(CustomerManager_Test, CustomerManager_getAll)
{
    NiceMock<MockRepository> mockRepo;
    NiceMock<MockUnitOfWork> mockUow;

    ptime nullTime;
    shared_ptr<Customer> customer1 {make_shared<Customer>(1, "Test Customer", "www.testcustomer.com", nullTime)};
    shared_ptr<Customer> customer2 {make_shared<Customer>(2, "Test Customer", "www.testcustomer.com", nullTime)};
    shared_ptr<Customer> customer3 {make_shared<Customer>(3, "Test Customer", "www.testcustomer.com", nullTime)};

    vector<shared_ptr<DomainObject>> customers {customer1, customer2, customer3};

    {
        InSequence s;
        EXPECT_CALL(mockRepo, findAll()).Times(1).WillOnce(Return(customers));
    }

    CustomerManager customerMgr {mockUow, mockRepo};
    shared_ptr<vector<shared_ptr<DomainObject>>> domainObjects {customerMgr.getAll()};
}

TEST(CustomerManager_Test, CustomerManager_Create)
{
    NiceMock<MockRepository> mockRepo;
    NiceMock<MockUnitOfWork> mockUow;

    ptime nullTime;
    Customer customer{-1, "New Customer", "www.newcustomer.net", nullTime};

    {
        InSequence s;
        EXPECT_CALL(mockUow, markforInsert(customer)).Times(1).WillOnce(Return());
    }

    CustomerManager customerMgr {mockUow, mockRepo};
    customerMgr.Create(customer);
}

TEST(CustomerManager_Test, CustomerManager_Update)
{
    NiceMock<MockRepository> mockRepo;
    NiceMock<MockUnitOfWork> mockUow;

    ptime nullTime;
    Customer customer{1, "New Customer", "www.newcustomer.net", nullTime};

    {
        InSequence s;
        EXPECT_CALL(mockUow, markForUpdate(customer)).Times(1).WillOnce(Return());
    }

    CustomerManager customerMgr {mockUow, mockRepo};
    customerMgr.Update(customer);
}

TEST(CustomerManager_Test, CustomerManager_Delete)
{
    NiceMock<MockRepository> mockRepo;
    NiceMock<MockUnitOfWork> mockUow;

    ptime nullTime;
    Customer customer{1, "New Customer", "www.newcustomer.net", nullTime};

    {
        InSequence s;
        EXPECT_CALL(mockUow, markForDelete(customer)).Times(1).WillOnce(Return());
    }

    CustomerManager customerMgr {mockUow, mockRepo};
    customerMgr.Delete(customer);
}