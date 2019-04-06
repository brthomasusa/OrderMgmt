#pragma once

#include <string>
#include <memory>
#include "DomainObject.h"

using namespace std;

namespace CommonLayer
{
    class Customer : public DomainObject
    {

    public:
        Customer();
        Customer(int id, const string& name, const string& website, const ptime& timeStamp);
        ~Customer() = default;

        void setCustomerId(int val);
        int getCustomerId() const;
        void setCustomerName(const string& val);
        const string& getCustomerName() const;
        void setWebsite(const string& val);
        const string& getWebsite() const;
        void setLastModified(const string& val);

    private:
        class Implementation;
        shared_ptr<Implementation> impl;
    };
}
