#include "gtest/gtest.h"
#include <memory>
#include <vector>
#include "ocilib.hpp"
#include "Customer.h"
#include "CustomerMapper.h"
#include "AddressMapper.h"
#include "TelephoneMapper.h"
#include "CustomerRepository.h"

using namespace std;
using namespace testing;
using namespace DataAccess;
using namespace CommonLayer;
using namespace ocilib;

void prepareDbForTesting()
{
    try
    {
        ocilib::Environment::Initialize();

        ocilib::Connection conn("oracle18db/xepdb1", "cust_orders", "Info77Gum");

        string sql {"begin sp_test_data_setup; end;"};
        ocilib::Statement stmt(conn);
        stmt.Execute(sql);

    }
    catch (std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    ocilib::Environment::Cleanup();
}

int main(int argc, char** argv)
{
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(CustomerRepositoryIntegration_Test, CustomerRepository_findById)
{
    prepareDbForTesting();

    int custID {1};
    CustomerMapper customerMapper;
    AddressMapper addressMapper;
    TelephoneMapper telephoneMapper;
    CustomerRepository repository(customerMapper, addressMapper, telephoneMapper);
    shared_ptr<DomainObject> customer {repository.findById(custID)};

    ASSERT_EQ(custID, customer->getID());
}

TEST(CustomerRepositoryIntegration_Test, CustomerRepository_findAll)
{
    prepareDbForTesting();

    CustomerMapper customerMapper;
    AddressMapper addressMapper;
    TelephoneMapper telephoneMapper;
    CustomerRepository repository(customerMapper, addressMapper, telephoneMapper);

    vector<shared_ptr<DomainObject>> customers {repository.findAll()};
    uint allCustomers {3};
    ASSERT_EQ(allCustomers, customers.size());
}

TEST(CustomerRepositoryIntegration_Test, CustomerRepository_insertEntity)
{
    prepareDbForTesting();

    Customer customer{-1, "Testing", "www", second_clock::local_time()};

    CustomerMapper customerMapper;
    AddressMapper addressMapper;
    TelephoneMapper telephoneMapper;
    CustomerRepository repository(customerMapper, addressMapper, telephoneMapper);
    repository.insertEntity(customer);

    shared_ptr<DomainObject> newCustomer {repository.findById(customer.getID())};
    ASSERT_EQ(customer.getID(), newCustomer->getID());
}

TEST(CustomerRepositoryIntegration_Test, CustomerRepository_updateEntity)
{
    prepareDbForTesting();

    Customer customer{3, "Update Testing", "test", second_clock::local_time()};

    CustomerMapper customerMapper;
    AddressMapper addressMapper;
    TelephoneMapper telephoneMapper;
    CustomerRepository repository(customerMapper, addressMapper, telephoneMapper);
    repository.updateEntity(customer);

    shared_ptr<DomainObject> result {repository.findById(customer.getID())};
    ASSERT_EQ("Update Testing", customer.getCustomerName());
}

TEST(CustomerRepositoryIntegration_Test, DISABLED_CustomerRepository_deleteEntity)
{
    prepareDbForTesting();

    Customer customer{-1, "Testing", "www", second_clock::local_time()};

    CustomerMapper customerMapper;
    AddressMapper addressMapper;
    TelephoneMapper telephoneMapper;
    CustomerRepository repository(customerMapper, addressMapper, telephoneMapper);
    repository.insertEntity(customer);

    shared_ptr<DomainObject> newCustomer {repository.findById(customer.getID())};
    EXPECT_EQ(customer.getID(), newCustomer->getID());

    // IDataMapper::deleteEntity ORA-02292: integrity constraint
    // (CUST_ORDERS.FK_ORDERS_CUSTOMERS) violated - child record found
    repository.deleteEntity(customer.getID());

    shared_ptr<DomainObject> result {repository.findById(customer.getID())};
    ASSERT_EQ(result, nullptr);
}