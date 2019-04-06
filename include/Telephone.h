#pragma once

#include <string>
#include <memory>
#include "DomainObject.h"

using namespace std;

namespace CommonLayer
{
    enum class TelephoneType
    {
        CELL = 1,
        FAX = 2,
        OFFICE =3
    };

    class Telephone : public DomainObject
    {
    public:
        Telephone();
        Telephone(int id, int entityId, const string& telNum, const string& extension, const TelephoneType& telType, const ptime& modified);
        ~Telephone() = default;

        void setEntityId(int val);
        int getEntityId() const;
        void setTelephoneNumber(const string& val);
        const string& getTelephoneNumber() const;
        void setExtension(const string val);
        const string& getExtension() const;
        void setTelephoneType(const TelephoneType& val);
        const TelephoneType& getTelephoneType() const;

    private:
        class Implementation;
        shared_ptr<Implementation> impl;
    };
}
