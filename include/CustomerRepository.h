#pragma once

#include "IRepository.h"
#include "CustomerMapper.h"
#include "AddressMapper.h"
#include "TelephoneMapper.h"

using namespace CommonLayer;

namespace DataAccess
{
    class CustomerRepository : public IRepository
    {

    public:
        CustomerRepository(CustomerMapper& customerMapper, AddressMapper& addressMapper, TelephoneMapper& telephoneMapper);
        ~CustomerRepository() = default;

        shared_ptr<DomainObject> findById(int entityID) override ;
        vector<shared_ptr<DomainObject>> findAll() override ;
        void insertEntity(DomainObject& entity) override;
        void updateEntity(const DomainObject& entity) override;
        void deleteEntity(int entityID) override ;

    private:
        CustomerMapper& _customerMapper;
        AddressMapper& _addressMapper;
        TelephoneMapper& _telephoneMapper;
    };
}
