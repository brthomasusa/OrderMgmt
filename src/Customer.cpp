#include "Customer.h"

namespace CommonLayer
{
    class Customer::Implementation
    {
    public:
        Implementation() = default;
        ~Implementation() = default;

        int _custID;
        string _custName;
        string _website;
        string _lastModified;
    };

    Customer::Customer()
    {
        impl = make_shared<Implementation>();
    }

    void Customer::setCustomerId(int val) { impl->_custID = val; }
    int Customer::getCustomerId() const { return impl->_custID; }

    void Customer::setCustomerName(const string &val) { impl->_custName = val; }
    const string& Customer::getCustomerName() const { return impl->_custName; }

    void Customer::setWebsite(const string &val) { impl->_website = val; }
    const string& Customer::getWebsite() const { return impl->_website; }

    const string& Customer::getLastModified() const { return impl->_lastModified; }
}

