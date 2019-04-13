#pragma once

#include <gmock/gmock.h>
#include "IRepository.h"
#include "DomainObject.h"

using namespace CommonLayer;

namespace DataAccess
{
    class MockRepository : public IRepository
    {

    public:
        MOCK_METHOD1(findById, shared_ptr<DomainObject>(int));
        MOCK_METHOD1(findChildren,vector<shared_ptr<DomainObject>>(int));
        MOCK_METHOD0(findAll, vector<shared_ptr<DomainObject>>());
        MOCK_METHOD1(insertEntity, void(DomainObject&));
        MOCK_METHOD1(updateEntity, void(const DomainObject&));
        MOCK_METHOD1(deleteEntity, void(int));
    };
}
