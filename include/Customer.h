#pragma once

#include <string>
#include <memory>

using namespace std;

namespace CommonLayer
{
    class Customer
    {

    public:
        Customer();
        ~Customer() = default;

        void setCustomerId(int val);
        int getCustomerId() const;
        void setCustomerName(const string& val);
        const string& getCustomerName() const;
        void setWebsite(const string& val);
        const string& getWebsite() const;
        const string& getLastModified() const;

    private:
        class Implementation;
        shared_ptr<Implementation> impl;
    };
}
