#pragma once

#include <memory>

using namespace std;

namespace CommonLayer
{
    class DomainObject
    {

    public:
        DomainObject();
        DomainObject(int id);
        virtual ~DomainObject() = default;

        bool operator==(const DomainObject& domainObject) const;
        bool operator!=(const DomainObject& domainObject) const;
        bool operator<(const DomainObject& domainObject) const;
        bool operator<=(const DomainObject& domainObject) const;
        bool operator>(const DomainObject& domainObject) const;
        bool operator>=(const DomainObject& domainObject) const;

        void setID(int val);
        int getID() const;

    private:
        class Implementation;
        shared_ptr<Implementation> _impl;
    };
}
