#pragma once

#include <memory>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

using namespace std;
using namespace boost::posix_time;

namespace CommonLayer
{
    class DomainObject
    {

    public:
        DomainObject();
        DomainObject(int id, const ptime& timeStamp);
        virtual ~DomainObject() = default;

        bool operator==(const DomainObject& domainObject) const;
        bool operator!=(const DomainObject& domainObject) const;
        bool operator<(const DomainObject& domainObject) const;
        bool operator<=(const DomainObject& domainObject) const;
        bool operator>(const DomainObject& domainObject) const;
        bool operator>=(const DomainObject& domainObject) const;

        void setID(int val);
        int getID() const;
        void setLastModified(const ptime& val);
        const ptime& getLastModified() const;

    private:
        class Implementation;
        shared_ptr<Implementation> _impl;
    };
}
