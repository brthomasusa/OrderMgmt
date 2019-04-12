#pragma once

#include <gmock/gmock.h>
#include "Telephone.h"
#include "TelephoneMapper.h"

using namespace CommonLayer;

namespace DataAccess
{

    class MockTelephoneMapper : public TelephoneMapper
    {

    public:
        MOCK_METHOD1(findById, shared_ptr<Telephone>(int));
        MOCK_METHOD1(findChildren,vector<shared_ptr<Telephone>>(int));
        MOCK_METHOD0(findAll, vector<shared_ptr<Telephone>>());
        MOCK_METHOD1(insertEntity, void(Telephone&));
        MOCK_METHOD1(updateEntity, void(const Telephone&));
        MOCK_METHOD1(deleteEntity, void(int));
    };
}
