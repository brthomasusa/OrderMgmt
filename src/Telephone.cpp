#include "Telephone.h"

namespace CommonLayer
{
    class Telephone::Implementation
    {
    public:
        Implementation() = default;
        ~Implementation() = default;

        int _entityID;
        string _telephoneNumber;
        string _extension;
        TelephoneType _telephoneType;

    };

    Telephone::Telephone()
        : DomainObject()
    {
        impl = make_shared<Implementation>();
    }

    Telephone::Telephone(int id, int entityId, const string& telNum, const string& extension, const TelephoneType& telType, const ptime& modified)
        : DomainObject(id, modified)
    {
        impl = make_shared<Implementation>();

        impl->_entityID = entityId;
        impl->_telephoneNumber = telNum;
        impl->_extension = extension;
        impl->_telephoneType = telType;
    }

    void Telephone::setEntityId(int val) { impl->_entityID = val; }
    int Telephone::getEntityId() const { return  impl->_entityID; }

    void Telephone::setTelephoneNumber(const string &val) { impl->_telephoneNumber = val; }
    const string& Telephone::getTelephoneNumber() const { return impl->_telephoneNumber; }

    void Telephone::setExtension(const string val) { impl->_extension = val; }
    const string& Telephone::getExtension() const { return impl->_extension; }

    void Telephone::setTelephoneType(const CommonLayer::TelephoneType &val) { impl->_telephoneType = val; }
    const TelephoneType& Telephone::getTelephoneType() const { return impl->_telephoneType; }

}
