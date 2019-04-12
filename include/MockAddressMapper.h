#pragma once

#include <gmock/gmock.h>
#include "Address.h"
#include "AddressMapper.h"

using namespace CommonLayer;

namespace DataAccess
{

    class MockAddressMapper : public AddressMapper
    {

    public:
        MOCK_METHOD1(findById, shared_ptr<Address>(int));
        MOCK_METHOD1(findChildren,vector<shared_ptr<Address>>(int));
        MOCK_METHOD0(findAll, vector<shared_ptr<Address>>());
        MOCK_METHOD1(insertEntity, void(Address&));
        MOCK_METHOD1(updateEntity, void(const Address&));
        MOCK_METHOD1(deleteEntity, void(int));
    };
}
