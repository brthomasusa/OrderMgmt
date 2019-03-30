#pragma once

#include "IDataMapper.h"
#include "Address.h"

using namespace CommonLayer;

namespace DataAccess
{
    class AddressMapper : public IDataMapper<Address>
    {
    public:
        AddressMapper() = default;
        virtual ~AddressMapper() = default;

        void insertEntity(Address& entity) override;
        void updateEntity(const Address& entity) override;

    protected:
        shared_ptr<Address> load(Resultset& rs) override ;
        vector<shared_ptr<Address>> loadAll(Resultset& rs) override ;

        const string& getFindStatement() override;
        const string& getFindAllStatement() override;
        const string& getFindChildrenStatement() override;
        const string& getDeleteStatement() override;

    private:
        const string _findStatement {"SELECT * FROM addresses WHERE address_id = :1"};
        const string _findAllStatement {"SELECT * FROM addresses"};
        const string _findChildrenStatement {"SELECT * FROM addresses WHERE entity_id = :1"};
        const string _deleteStatement {"DELETE FROM addresses WHERE address_id = :1"};

        const uint kAddressID = 1;
        const uint kEntityID = 2;
        const uint kLine1 = 3;
        const uint kLine2 = 4;
        const uint kCity = 5;
        const uint kState = 6;
        const uint kZipcode = 7;
        const uint kTimestamp = 8;
    };
}
