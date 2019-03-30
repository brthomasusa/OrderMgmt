#include "Telephone.h"

namespace CommonLayer
{
    class Telephone::Implementation
    {
    public:
        Implementation() = default;
        ~Implementation() = default;

        int _telephoneID;
        int _entityID;
        string _telephoneNumber;
        string _extension;
        TelephoneType _telephoneType;
        string _lastModified;
    };

    Telephone::Telephone()
    {
        impl = make_shared<Implementation>();
    }

    void Telephone::setTelephoneId(int val) { impl->_telephoneID = val; }
    int Telephone::getTelephoneId() const { return impl->_telephoneID; }

    void Telephone::setEntityId(int val) { impl->_entityID = val; }
    int Telephone::getEntityId() const { return  impl->_entityID; }

    void Telephone::setTelephoneNumber(const string &val) { impl->_telephoneNumber = val; }
    const string& Telephone::getTelephoneNumber() const { return impl->_telephoneNumber; }

    void Telephone::setExtension(const string val) { impl->_extension = val; }
    const string& Telephone::getExtension() const { return impl->_extension; }

    void Telephone::setTelephoneType(const CommonLayer::TelephoneType &val) { impl->_telephoneType = val; }
    const TelephoneType& Telephone::getTelephoneType() const { return impl->_telephoneType; }

    const string& Telephone::getLastModified() const { return impl->_lastModified; }
}
