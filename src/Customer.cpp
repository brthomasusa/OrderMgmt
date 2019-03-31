#include "Customer.h"

namespace CommonLayer
{
    class Customer::Implementation
    {
    public:
        Implementation() = default;
        ~Implementation() = default;

        string _custName;
        string _website;
        string _lastModified;
    };

    Customer::Customer()
        : DomainObject()
    {
        impl = make_shared<Implementation>();
    }

    Customer::Customer(int id, const string& name, const string& website, const string& timeStamp)
        : DomainObject(id)
    {
        impl = make_shared<Implementation>();

        impl->_custName = name;
        impl->_website = website;
        impl->_lastModified = timeStamp;
    }


    void Customer::setCustomerName(const string &val) { impl->_custName = val; }
    const string& Customer::getCustomerName() const { return impl->_custName; }

    void Customer::setWebsite(const string &val) { impl->_website = val; }
    const string& Customer::getWebsite() const { return impl->_website; }

    void Customer::setLastModified(const string &val) { impl->_lastModified = val; }
    const string& Customer::getLastModified() const { return impl->_lastModified; }
}

