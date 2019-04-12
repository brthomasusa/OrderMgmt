#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include "Customer.h"
#include "Address.h"
#include "Telephone.h"
#include "MockCustomerMapper.h"
#include "MockAddressMapper.h"
#include "MockTelephoneMapper.h"
#include "CustomerRepository.h"

using namespace std;
using namespace testing;
using ::testing::AtLeast;
using namespace DataAccess;
using namespace CommonLayer;

shared_ptr<Customer> createNewCustomer(int custid)
{
    ptime p;
    shared_ptr<Customer> customer {make_shared<Customer>(custid, "New Customer", "www.newcustomer.com", p)};
    return customer;
}

int main(int argc, char** argv)
{
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(CustomerRepository_Test, CustomerRepository_findById)
{
    int custID {1};
    ptime nullTime;
    shared_ptr<Customer> customerObj {make_shared<Customer>(custID, "Test Customer", "www.testcustomer.com", nullTime)};

    vector<shared_ptr<Address>> addresses;
    addresses.push_back(make_shared<Address>(1, 1, "123 South Main Road", "Ste 10", "Logan", "UT", "84321", nullTime));
    addresses.push_back(make_shared<Address>(2, 1, "123 South Main Blvd", "Ste 1", "Logan", "UT", "84321", nullTime));

    vector<shared_ptr<Telephone>> telephones;
    telephones.push_back(make_shared<Telephone>(1, 1, "435-745-9999", "55555",  TelephoneType::OFFICE, nullTime));
    telephones.push_back(make_shared<Telephone>(2, 1, "435-745-9998", "55555",  TelephoneType::CELL, nullTime));

    NiceMock<MockCustomerMapper>  customerMapper;
    NiceMock<MockAddressMapper>  addressMapper;
    NiceMock<MockTelephoneMapper>  telephoneMapper;

    {
        InSequence s;
        EXPECT_CALL(customerMapper, findById(An<int>())).Times(1).WillOnce(Return(customerObj));

        EXPECT_CALL(addressMapper, findChildren(An<int>())).Times(1).WillOnce(Return(addresses));

        EXPECT_CALL(telephoneMapper, findChildren(An<int>())).Times(1).WillOnce(Return(telephones));
    }

    CustomerRepository repo(customerMapper, addressMapper, telephoneMapper);

    shared_ptr<DomainObject> customerDomainObj {repo.findById(custID)};
    EXPECT_NE(customerDomainObj, nullptr);
    uint expectSize{2};

    ASSERT_EQ(expectSize, dynamic_cast<Customer&>(*customerDomainObj).getAddresses()->size());
    ASSERT_EQ(expectSize, dynamic_cast<Customer&>(*customerDomainObj).getTelephones()->size());
}

TEST(CustomerRepository_Test, CustomerRepository_findAll)
{
    ptime nullTime;
    vector<shared_ptr<Customer>> customers;
    customers.push_back(make_shared<Customer>(1, "Fred's Auto Shop", "http://www.fredsautoshop.com", nullTime));
    customers.push_back(make_shared<Customer>(2, "Alex's Music Store", "https://www.alexmusic.com", nullTime));
    customers.push_back(make_shared<Customer>(3, "Update Testing", "test", nullTime));

    NiceMock<MockCustomerMapper>  customerMapper;
    NiceMock<MockAddressMapper>  addressMapper;
    NiceMock<MockTelephoneMapper>  telephoneMapper;

    {
        InSequence s;
        EXPECT_CALL(customerMapper, findAll()).Times(1).WillOnce(Return(customers));
    }

    CustomerRepository repo(customerMapper, addressMapper, telephoneMapper);
    vector<shared_ptr<DomainObject>> domainObjs {repo.findAll()};

    uint expectSize{3};
    ASSERT_EQ(expectSize, domainObjs.size());
}

TEST(CustomerRepository_Test, CustomerRepository_insertEntity)
{
    ptime nullTime;
    Customer customer{-1, "New Customer", "www.newcustomer.net", nullTime};

    NiceMock<MockCustomerMapper>  customerMapper;
    NiceMock<MockAddressMapper>  addressMapper;
    NiceMock<MockTelephoneMapper>  telephoneMapper;

    {
        InSequence s;
        EXPECT_CALL(customerMapper, insertEntity(Ref(customer))).Times(1);
    }

    CustomerRepository repo(customerMapper, addressMapper, telephoneMapper);
    repo.insertEntity(customer);
}

TEST(CustomerRepository_Test, CustomerRepository_updateEntity)
{
    ptime nullTime;
    Customer customer{3, "Edit Customer", "www.editcustomer.net", nullTime};

    NiceMock<MockCustomerMapper>  customerMapper;
    NiceMock<MockAddressMapper>  addressMapper;
    NiceMock<MockTelephoneMapper>  telephoneMapper;

    {
        InSequence s;
        EXPECT_CALL(customerMapper, updateEntity(Ref(customer))).Times(1);
    }

    CustomerRepository repo(customerMapper, addressMapper, telephoneMapper);
    repo.updateEntity(customer);
}

TEST(CustomerRepository_Test, CustomerRepository_deleteEntity)
{
    int custID{3};
    NiceMock<MockCustomerMapper>  customerMapper;
    NiceMock<MockAddressMapper>  addressMapper;
    NiceMock<MockTelephoneMapper>  telephoneMapper;

    {
        InSequence s;
        EXPECT_CALL(customerMapper, deleteEntity(An<int>())).Times(1);
    }

    CustomerRepository repo(customerMapper, addressMapper, telephoneMapper);
    repo.deleteEntity(custID);
}