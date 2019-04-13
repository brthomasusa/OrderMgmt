#pragma once

#include <vector>
#include "IUnitOfWork.h"
#include "IRepository.h"
#include "Customer.h"

using namespace std;
using namespace CommonLayer;

namespace DataAccess
{
    class CustomerUnitOfWork : public IUnitOfWork
    {

    public:
        explicit CustomerUnitOfWork(IRepository& repository) : _repository(repository) {}
        ~CustomerUnitOfWork() override;

        void markforInsert(DomainObject& obj) override;
        void markForUpdate(DomainObject& obj) override;
        void markForDelete(DomainObject& obj) override;
        void saveChanges() override;

    private:
        bool checkNewObjectCache(const Customer& customer) const;
        void checkObjectCaches(const DomainObject& obj) const;

        IRepository& _repository;
        vector<Customer> _newObjects;
        vector<Customer> _dirtyObjects;
        vector<Customer> _removedObjects;
    };
}
