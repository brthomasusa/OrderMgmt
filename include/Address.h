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
        Address(int id, int entityId, const string& line1, const string& line2, const string& city,
                const string& state, const string& zipcode, const ptime& timestamp);
        ~Address() = default;


        int getEntityId() const;
        const string& getAddressLine1() const;
        const string& getAddressLine2() const;
        const string& getCity() const;
        const string& getStateCode() const;
        const string& getZipcode() const;

    private:
        class Implementation;
        shared_ptr<Implementation> impl;

    };
}
