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


    void Customer::setCustomerName(const string &val) { impl->_custName = val; }
    const string& Customer::getCustomerName() const { return impl->_custName; }

    void Customer::setWebsite(const string &val) { impl->_website = val; }
    const string& Customer::getWebsite() const { return impl->_website; }

}

