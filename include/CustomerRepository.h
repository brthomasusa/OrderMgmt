#pragma once

#include "IRepository.h"
#include "CustomerMapper.h"
#include "Customer.h"

using namespace CommonLayer;

namespace DataAccess
{
    class CustomerRepository : public IRepository<Customer>
    {
    public:
        CustomerRepository(IDataMapper<Customer>& customerMapper);
        ~CustomerRepository() = default;

        virtual Customer findById(int entityID) override ;
        virtual vector<shared_ptr<Customer>> findChildren(int parentID) override;
        virtual vector<shared_ptr<Customer>> findAll() override ;
        virtual void insertEntity(Customer& entity) override;
        virtual void updateEntity(const Customer& entity) override;
        virtual void deleteEntity(int entityID) override ;

    private:
        class Implementation;
        shared_ptr<Implementation> _impl;
    };
}
