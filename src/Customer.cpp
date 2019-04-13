#include "Customer.h"
#include <utility>

namespace CommonLayer
{
    class Customer::Implementation
    {
    public:
        Implementation() = default;
        ~Implementation() = default;

        string _custName;
        string _website;
        shared_ptr<vector<shared_ptr<Address>>> _addresses {make_shared<vector<shared_ptr<Address>>>()};
        shared_ptr<vector<shared_ptr<Telephone>>> _telephones {make_shared<vector<shared_ptr<Telephone>>>()};
    };

    Customer::Customer()
        : DomainObject()
    {
        impl = make_shared<Implementation>();
    }

    Customer::Customer(int id, const string& name, const string& website, const ptime& timeStamp)
        : DomainObject(id, timeStamp)
    {
        impl = make_shared<Implementation>();

        impl->_custName = name;
        impl->_website = website;
    }

    Customer::Customer(const Customer& src)
        : Customer()
    {

        this->setID(src.getID());
        this->impl->_custName = src.impl->_custName;
        this->impl->_website = src.impl->_website;
        this->setLastModified(src.getLastModified());

        for (uint i = 0; i < src.impl->_addresses->size(); ++i)
        {
            shared_ptr<Address> address {make_shared<Address>(
                    src.impl->_addresses->at(i)->getID(),
                    src.impl->_addresses->at(i)->getEntityId(),
                    src.impl->_addresses->at(i)->getAddressLine1(),
                    src.impl->_addresses->at(i)->getAddressLine2(),
                    src.impl->_addresses->at(i)->getCity(),
                    src.impl->_addresses->at(i)->getStateCode(),
                    src.impl->_addresses->at(i)->getZipcode(),
                    src.impl->_addresses->at(i)->getLastModified()
            )};
            this->impl->_addresses->push_back(address);
        }

        for (uint i = 0; i < src.impl->_telephones->size(); ++i)
        {
            shared_ptr<Telephone> telephone {make_shared<Telephone>(
                    src.impl->_telephones->at(i)->getID(),
                    src.impl->_telephones->at(i)->getEntityId(),
                    src.impl->_telephones->at(i)->getTelephoneNumber(),
                    src.impl->_telephones->at(i)->getExtension(),
                    src.impl->_telephones->at(i)->getTelephoneType(),
                    src.impl->_telephones->at(i)->getLastModified()
            )};
            this->impl->_telephones->push_back(telephone);
        }
    }

    Customer::~Customer() {}

    Customer& Customer::operator=(const Customer& src)
    {
        if (this == &src)
        {
            return * this;
        }

        this->setID(src.getID());
        this->impl->_custName = src.impl->_custName;
        this->impl->_website = src.impl->_website;
        this->setLastModified(src.getLastModified());

        this->impl->_addresses->clear();
        this->impl->_telephones->clear();

        for (uint i = 0; i < src.impl->_addresses->size(); ++i)
        {
            shared_ptr<Address> address {make_shared<Address>(
                src.impl->_addresses->at(i)->getID(),
                src.impl->_addresses->at(i)->getEntityId(),
                src.impl->_addresses->at(i)->getAddressLine1(),
                src.impl->_addresses->at(i)->getAddressLine2(),
                src.impl->_addresses->at(i)->getCity(),
                src.impl->_addresses->at(i)->getStateCode(),
                src.impl->_addresses->at(i)->getZipcode(),
                src.impl->_addresses->at(i)->getLastModified()
            )};
            this->impl->_addresses->push_back(address);
        }

        for (uint i = 0; i < src.impl->_telephones->size(); ++i)
        {
            shared_ptr<Telephone> telephone {make_shared<Telephone>(
                src.impl->_telephones->at(i)->getID(),
                src.impl->_telephones->at(i)->getEntityId(),
                src.impl->_telephones->at(i)->getTelephoneNumber(),
                src.impl->_telephones->at(i)->getExtension(),
                src.impl->_telephones->at(i)->getTelephoneType(),
                src.impl->_telephones->at(i)->getLastModified()
            )};
            this->impl->_telephones->push_back(telephone);
        }

        return *this;
    }

    void Customer::setCustomerName(const string &val) { impl->_custName = val; }
    const string& Customer::getCustomerName() const { return impl->_custName; }

    void Customer::setWebsite(const string &val) { impl->_website = val; }
    const string& Customer::getWebsite() const { return impl->_website; }

    void Customer::setAddress(shared_ptr<Address> val) { impl->_addresses->push_back(val); }
    void Customer::setAddresses(shared_ptr<vector<shared_ptr<Address>>> val) { impl->_addresses = val; }
    const shared_ptr<vector<shared_ptr<Address>>> Customer::getAddresses() const { return impl->_addresses; }

    void Customer::setTelephone(shared_ptr<Telephone> val) { impl->_telephones->push_back(val); }
    void Customer::setTelephones(shared_ptr<vector<shared_ptr<Telephone>>> val) { impl->_telephones = val; }
    const shared_ptr<vector<shared_ptr<Telephone>>> Customer::getTelephones() const { return impl->_telephones; }

}

