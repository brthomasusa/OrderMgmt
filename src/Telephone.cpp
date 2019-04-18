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

    Telephone::Telephone(int id, int entityId, const string& telNum, const string& extension, const TelephoneType& telType, const ptime& modified)
        : DomainObject(id, modified)
    {
        impl = make_shared<Implementation>();

        impl->_entityID = entityId;
        impl->_telephoneNumber = telNum;
        impl->_extension = extension;
        impl->_telephoneType = telType;
    }

    int Telephone::getEntityId() const { return  impl->_entityID; }
    const string& Telephone::getTelephoneNumber() const { return impl->_telephoneNumber; }
    const string& Telephone::getExtension() const { return impl->_extension; }
    const TelephoneType& Telephone::getTelephoneType() const { return impl->_telephoneType; }

}
