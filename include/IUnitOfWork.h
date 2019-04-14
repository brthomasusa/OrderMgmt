#pragma once

#include "DomainObject.h"

using namespace CommonLayer;

namespace DataAccess
{
    class IUnitOfWork
    {

    public:
        IUnitOfWork() = default;
        virtual ~IUnitOfWork() = default;

        virtual void markforInsert(DomainObject& obj) = 0;
        virtual void markForUpdate(DomainObject& obj) = 0;
        virtual void markForDelete(DomainObject& obj) = 0;
        virtual void saveChanges() = 0;
    };
}
