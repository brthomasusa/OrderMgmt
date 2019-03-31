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

    Address::Address()
        : DomainObject()
    {
        impl = make_shared<Implementation>();
    }

    Address::Address(int id, int entityId, const string& line1, const string& line2, const string& city, const string& state, const string& zipcode, const string& timestamp)
            : DomainObject(id)
    {
        impl = make_shared<Implementation>();

        impl->_entityID = entityId;
        impl->_addressLine1 = line1;
        impl->_addressLine2 = line2;
        impl->_city = city;
        impl->_stateCode = state;
        impl->_zipcode = zipcode;
        impl->_timestamp = timestamp;
    }

    void Address::setEntityId(int val) { impl->_entityID = val; }
    int Address::getEntityId() const { return impl->_entityID; }

    void Address::setAddressLine1(const string& val) { impl->_addressLine1 = val; }
    const string& Address::getAddressLine1() const { return impl->_addressLine1; }

    void Address::setAddressLine2(const string& val) { impl->_addressLine2 = val; }
    const string& Address::getAddressLine2() const { return impl->_addressLine2; }

    void Address::setCity(const string& val) { impl->_city = val; }
    const string& Address::getCity() const { return impl->_city; }

    void Address::setStateCode(const string& val) { impl->_stateCode = val; }
    const string& Address::getStateCode() const { return impl->_stateCode; }

    void Address::setZipcode(const string& val) { impl->_zipcode = val; }
    const string& Address::getZipcode() const { return impl->_zipcode; }

    const string& Address::getTimestamp() const { return impl->_timestamp; }
}

