#pragma once

#include <memory>
#include <vector>
#include "DomainObject.h"

using namespace CommonLayer;

namespace DataAccess
{
    class IRepository
    {

    public:
        IRepository() = default;
        virtual ~IRepository() = default;

        virtual shared_ptr<DomainObject> findById(int entityID) = 0;
        virtual vector<shared_ptr<DomainObject>> findAll() = 0;
        virtual void insertEntity(DomainObject& entity) = 0;
        virtual void updateEntity(const DomainObject& entity) = 0;
        virtual void deleteEntity(int entityID) = 0;
    };
}