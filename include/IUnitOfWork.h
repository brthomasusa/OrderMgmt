#pragma once

namespace CommonLayer
{
    class DomainObject;
}

namespace DataAccess
{
    class IUnitOfWork
    {

    public:
        IUnitOfWork() = default;
        virtual ~IUnitOfWork() = default;

        virtual void markforInsert(CommonLayer::DomainObject& obj) = 0;
        virtual void markForUpdate(CommonLayer::DomainObject& obj) = 0;
        virtual void markForDelete(CommonLayer::DomainObject& obj) = 0;
        virtual void saveChanges() = 0;
    };
}
