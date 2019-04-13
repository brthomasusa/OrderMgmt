#pragma once

#include <string>
#include <memory>
#include <vector>
#include "DomainObject.h"
#include "Address.h"
#include "Telephone.h"

using namespace std;

namespace CommonLayer
{
    class Customer : public DomainObject
    {

    public:
        Customer();
        Customer(int id, const string& name, const string& website, const ptime& timeStamp);
        Customer(const Customer& src);
        Customer& operator=(const Customer& src);
        ~Customer() override;

        void setCustomerId(int val);
        int getCustomerId() const;
        void setCustomerName(const string& val);
        const string& getCustomerName() const;
        void setWebsite(const string& val);
        const string& getWebsite() const;
        void setAddresses(shared_ptr<vector<shared_ptr<Address>>> val);
        void setAddress(shared_ptr<Address> val);
        const shared_ptr<vector<shared_ptr<Address>>> getAddresses() const;
        void setTelephones(shared_ptr<vector<shared_ptr<Telephone>>> val);
        void setTelephone(shared_ptr<Telephone> val);
        const shared_ptr<vector<shared_ptr<Telephone>>> getTelephones() const;

    private:
        class Implementation;
        shared_ptr<Implementation> impl;
    };
}
