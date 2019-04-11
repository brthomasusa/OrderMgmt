#pragma once

#include <memory>
#include "DomainObject.h"

using namespace CommonLayer;

namespace BusinessLayer
{
    class IActionManager
    {

    public:
        IActionManager() = default;
        virtual ~IActionManager() = default;

        virtual void Create(DomainObject& entity) = 0;
        virtual void Update(DomainObject& entity) = 0;
        virtual void Delete(DomainObject& entity) = 0;
        virtual shared_ptr<vector<shared_ptr<DomainObject>>> getAll() = 0;
        virtual shared_ptr<DomainObject> getById(int entityID) = 0;
        virtual void saveChanges() = 0;

    };
}
