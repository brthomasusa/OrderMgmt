#include "Address.h"

namespace CommonLayer
{
    class Address::Implementation
    {

    public:
        Implementation() = default;
        ~Implementation() = default;

        int _entityID;
        string _addressLine1;
        string _addressLine2;
        string _city;
        string _stateCode;
        string _zipcode;
        string _timestamp;

    };

    Address::Address(int id, int entityId, const string& line1, const string& line2, const string& city, const string& state, const string& zipcode, const ptime& timestamp)
            : DomainObject(id, timestamp)
    {
        impl = make_shared<Implementation>();

        impl->_entityID = entityId;
        impl->_addressLine1 = line1;
        impl->_addressLine2 = line2;
        impl->_city = city;
        impl->_stateCode = state;
        impl->_zipcode = zipcode;
    }

    int Address::getEntityId() const { return impl->_entityID; }
    const string& Address::getAddressLine1() const { return impl->_addressLine1; }
    const string& Address::getAddressLine2() const { return impl->_addressLine2; }
    const string& Address::getCity() const { return impl->_city; }
    const string& Address::getStateCode() const { return impl->_stateCode; }
    const string& Address::getZipcode() const { return impl->_zipcode; }

}

