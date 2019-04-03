#include "DomainObject.h"

namespace CommonLayer
{
    class DomainObject::Implementation
    {

    public:
        Implementation() = default;
        ~Implementation() = default;

        int _ID;
    };

    DomainObject::DomainObject() { _impl = std::make_shared<Implementation>(); }
    DomainObject::DomainObject(int id) : DomainObject() { _impl->_ID = id; }

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
}

