#pragma once

#include <vector>
#include <memory>
#include <gmock/gmock.h>
#include "DomainObject.h"

using namespace CommonLayer;
namespace BusinessLayer
{

    class MockActionManager
    {

    public:
        MOCK_METHOD1(Create, void(DomainObject&));
        MOCK_METHOD1(Update, void(DomainObject&));
        MOCK_METHOD1(Delete, void(DomainObject&));
        MOCK_METHOD0(getAll, shared_ptr<vector<shared_ptr<DomainObject>>>());
        MOCK_METHOD1(getById, shared_ptr<DomainObject>(int));
        MOCK_METHOD0(saveChanges, void());
    };
}
