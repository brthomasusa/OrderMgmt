//
#pragma once

#include <string>
#include <memory>
#include "DomainObject.h"

using namespace std;

namespace CommonLayer
{
    class Address : public DomainObject
    {

    public:
        Address();
        Address(int id, int entityId, const string& line1, const string& line2, const string& city,
                const string& state, const string& zipcode, const string& timestamp);
        ~Address() = default;

        void setEntityId(int val);
        int getEntityId() const;
        void setAddressLine1(const string& val);
        const string& getAddressLine1() const;
        void setAddressLine2(const string& val);
        const string& getAddressLine2() const;
        void setCity(const string& val);
        const string& getCity() const;
        void setStateCode(const string& val);
        const string& getStateCode() const;
        void setZipcode(const string& val);
        const string& getZipcode() const;
        const string& getTimestamp() const;

    private:
        class Implementation;
        shared_ptr<Implementation> impl;

    };
}
