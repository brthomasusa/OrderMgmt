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
        Telephone(int id, int entityId, const string& telNum, const string& extension, const TelephoneType& telType, const ptime& modified);
        ~Telephone() = default;

        int getEntityId() const;
        const string& getTelephoneNumber() const;
        const string& getExtension() const;
        const TelephoneType& getTelephoneType() const;

    private:
        class Implementation;
        shared_ptr<Implementation> impl;
    };
}
