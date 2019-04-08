#include "CustomerRepository.h"

namespace DataAccess
{
    CustomerRepository::CustomerRepository(CustomerMapper& customerMapper)
            : _customerMapper {customerMapper}
    {
    }

    shared_ptr<DomainObject> CustomerRepository::findById(int entityID)
    {
        shared_ptr<Customer> customer {_customerMapper.findById(entityID)};
        return customer;
    }

    vector<shared_ptr<DomainObject>> CustomerRepository::findChildren(int parentID)
    {
        vector<shared_ptr<DomainObject>> domainObjects;

        return domainObjects;
    }

    vector<shared_ptr<DomainObject>> CustomerRepository::findAll()
    {
        vector<shared_ptr<Customer>> customers = _customerMapper.findAll();
        vector<shared_ptr<DomainObject>> domainObjects;

        for (auto customer : customers)
        {
            domainObjects.push_back(customer);
        }

        return domainObjects;
    }

    void CustomerRepository::insertEntity(DomainObject& entity)
    {
        _customerMapper.insertEntity(dynamic_cast<Customer&>(entity));
    }

    void CustomerRepository::updateEntity(const DomainObject& entity)
    {
        _customerMapper.updateEntity(dynamic_cast<const Customer&>(entity));
    }

    void CustomerRepository::deleteEntity(int entityID)
    {
        _customerMapper.deleteEntity(entityID);
    }
}

