#pragma once

#include <gmock/gmock.h>
#include "IUnitOfWork.h"
#include "DomainObject.h"

using namespace CommonLayer;

namespace DataAccess
{
    class MockUnitOfWork : public IUnitOfWork
    {

    public:
        MOCK_METHOD1(markforInsert, void(DomainObject&));
        MOCK_METHOD1(markForUpdate, void(DomainObject&));
        MOCK_METHOD1(markForDelete, void(DomainObject&));
        MOCK_METHOD0(saveChanges, void());

    };
}
