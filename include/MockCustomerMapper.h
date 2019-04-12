#pragma once

#include <gmock/gmock.h>
#include "Customer.h"
#include "CustomerMapper.h"

using namespace CommonLayer;

namespace DataAccess
{

    class MockCustomerMapper : public CustomerMapper
    {

    public:
        MOCK_METHOD1(findById, shared_ptr<Customer>(int));
        MOCK_METHOD1(findChildren,vector<shared_ptr<Customer>>(int));
        MOCK_METHOD0(findAll, vector<shared_ptr<Customer>>());
        MOCK_METHOD1(insertEntity, void(Customer&));
        MOCK_METHOD1(updateEntity, void(const Customer&));
        MOCK_METHOD1(deleteEntity, void(int));
    };
}
