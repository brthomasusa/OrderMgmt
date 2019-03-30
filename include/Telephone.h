#pragma once

#include <string>
#include <memory>

using namespace std;

namespace CommonLayer
{
    enum class TelephoneType
    {
        CELL = 1,
        FAX = 2,
        OFFICE =3
    };

    class Telephone
    {
    public:
        Telephone();
        ~Telephone() = default;

        void setTelephoneId(int val);
        int getTelephoneId() const;
        void setEntityId(int val);
        int getEntityId() const;
        void setTelephoneNumber(const string& val);
        const string& getTelephoneNumber() const;
        void setExtension(const string val);
        const string& getExtension() const;
        void setTelephoneType(const TelephoneType& val);
        const TelephoneType& getTelephoneType() const;
        const string& getLastModified() const;

    private:
        class Implementation;
        shared_ptr<Implementation> impl;
    };
}
