#pragma once

#include "CustomerMapper.h"
#include "IRepository.h"
#include "Customer.h"

using namespace CommonLayer;

namespace DataAccess
{
    class CustomerRepository : public IRepository
    {

    public:
        CustomerRepository(CustomerMapper& customerMapper);
        ~CustomerRepository() = default;

        shared_ptr<DomainObject> findById(int entityID) override ;
        vector<shared_ptr<DomainObject>> findChildren(int parentID) override;
        vector<shared_ptr<DomainObject>> findAll() override ;
        void insertEntity(DomainObject& entity) override;
        void updateEntity(const DomainObject& entity) override;
        void deleteEntity(int entityID) override ;

    private:
        CustomerMapper& _customerMapper;
    };
}
