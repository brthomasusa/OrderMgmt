#include "DomainObject.h"

namespace CommonLayer
{
    class DomainObject::Implementation
    {

    public:
        Implementation() = default;
        ~Implementation() = default;

        int _ID;
        ptime _timestamp;
    };

    DomainObject::DomainObject()
    {
        _impl = std::make_shared<Implementation>();
        ptime p;
        _impl->_ID = -1;
        _impl->_timestamp = p;
    }

    DomainObject::DomainObject(int id, const ptime& timeStamp) : DomainObject()
    {
        _impl->_ID = id;
        _impl->_timestamp;
    }

    bool DomainObject::operator==(const DomainObject& domainObject) const
    {
        return _impl->_ID == domainObject._impl->_ID;
    }

    bool DomainObject::operator!=(const DomainObject& domainObject) const
    {
        return _impl->_ID != domainObject._impl->_ID;
    }

    bool DomainObject::operator<(const DomainObject& domainObject) const
    {
        return _impl->_ID < domainObject._impl->_ID;
    }

    bool DomainObject::operator<=(const DomainObject& domainObject) const
    {
        return _impl->_ID <= domainObject._impl->_ID;
    }

    bool DomainObject::operator>(const DomainObject& domainObject) const
    {
        return _impl->_ID > domainObject._impl->_ID;
    }

    bool DomainObject::operator>=(const DomainObject& domainObject) const
    {
        return _impl->_ID >= domainObject._impl->_ID;
    }

    void DomainObject::setID(int val) { _impl->_ID = val; }
    int DomainObject::getID() const { return _impl->_ID; }

    void DomainObject::setLastModified(const ptime& val) { _impl->_timestamp = val; }
    const ptime& DomainObject::getLastModified() const { return _impl->_timestamp; }
}

