#include "CustomerRepository.h"

namespace DataAccess
{
    CustomerRepository::CustomerRepository(CustomerMapper& customerMapper, AddressMapper& addressMapper, TelephoneMapper& telephoneMapper)
            : _customerMapper {customerMapper}
            , _addressMapper {addressMapper}
            , _telephoneMapper {telephoneMapper}
    {
    }

    shared_ptr<DomainObject> CustomerRepository::findById(int entityID)
    {
        shared_ptr<Customer> customer {_customerMapper.findById(entityID)};
        int entID {customer->getID()};
        vector<shared_ptr<Address>> addressBuffer {_addressMapper.findChildren(entID)};
        vector<shared_ptr<Telephone>> telephoneBuffer {_telephoneMapper.findChildren(customer->getID())};

        shared_ptr<vector<shared_ptr<Address>>> addresses {make_shared<vector<shared_ptr<Address>>>()};
        for (const shared_ptr<Address>& address : addressBuffer)
        {
            addresses->push_back(address);
        }

        shared_ptr<vector<shared_ptr<Telephone>>> telephones {make_shared<vector<shared_ptr<Telephone>>>()};
        for (const shared_ptr<Telephone>& telephone : telephoneBuffer)
        {
            telephones->push_back(telephone);
        }

        customer->setAddresses(addresses);
        customer->setTelephones(telephones);

        return customer;
    }

    vector<shared_ptr<DomainObject>> CustomerRepository::findChildren(int parentID)
    {
        // findChildren is implemented and used in IDataMapper and its derived classes
        // but not in the IRepository classes
        vector<shared_ptr<DomainObject>> domainObjects;
        return domainObjects;
    }

    vector<shared_ptr<DomainObject>> CustomerRepository::findAll()
    {
        vector<shared_ptr<Customer>> customers = _customerMapper.findAll();
        vector<shared_ptr<DomainObject>> domainObjects;

        for (const auto& customer : customers)
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

