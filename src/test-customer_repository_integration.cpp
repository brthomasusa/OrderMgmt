#include "gtest/gtest.h"
#include <memory>
#include <vector>
#include "ocilib.hpp"
#include "Customer.h"
#include "CustomerMapper.h"
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
    CustomerMapper mapper;
    CustomerRepository repository(mapper);
    shared_ptr<DomainObject> customer {repository.findById(custID)};

    ASSERT_EQ(custID, customer->getID());
}

TEST(CustomerRepositoryIntegration_Test, CustomerRepository_findChildren)
{
    prepareDbForTesting();

    CustomerMapper mapper;
    CustomerRepository repository(mapper);

    vector<shared_ptr<DomainObject>> customers {repository.findChildren(1)};
    uint allCustomers {0};
    ASSERT_EQ(allCustomers, customers.size());
}

TEST(CustomerRepositoryIntegration_Test, CustomerRepository_findAll)
{
    prepareDbForTesting();

    CustomerMapper mapper;
    CustomerRepository repository(mapper);

    vector<shared_ptr<DomainObject>> customers {repository.findAll()};
    uint allCustomers {3};
    ASSERT_EQ(allCustomers, customers.size());
}

TEST(CustomerRepositoryIntegration_Test, CustomerRepository_insertEntity)
{
    prepareDbForTesting();

    Customer customer{-1, "Testing", "www", second_clock::local_time()};

    CustomerMapper mapper;
    CustomerRepository repository(mapper);
    repository.insertEntity(customer);

    shared_ptr<DomainObject> newCustomer {repository.findById(customer.getID())};
    ASSERT_EQ(customer.getID(), newCustomer->getID());
}

TEST(CustomerRepositoryIntegration_Test, CustomerRepository_updateEntity)
{
    prepareDbForTesting();

    Customer customer{3, "Update Testing", "test", second_clock::local_time()};

    CustomerMapper mapper;
    CustomerRepository repository(mapper);
    repository.updateEntity(customer);

    shared_ptr<DomainObject> result {repository.findById(customer.getID())};
    ASSERT_EQ("Update Testing", customer.getCustomerName());
}

TEST(CustomerRepositoryIntegration_Test, CustomerRepository_deleteEntity)
{
    prepareDbForTesting();

    Customer customer{-1, "Testing", "www", second_clock::local_time()};

    CustomerMapper mapper;
    CustomerRepository repository(mapper);
    repository.insertEntity(customer);

    shared_ptr<DomainObject> newCustomer {repository.findById(customer.getID())};
    EXPECT_EQ(customer.getID(), newCustomer->getID());

    repository.deleteEntity(customer.getID());

    shared_ptr<DomainObject> result {repository.findById(customer.getID())};
    ASSERT_EQ(result, nullptr);
}