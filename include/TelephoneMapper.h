#pragma once

#include "Telephone.h"
#include "IDataMapper.h"

using namespace CommonLayer;

namespace DataAccess
{
    class TelephoneMapper : public IDataMapper<Telephone>
    {

    public:
        TelephoneMapper() = default;
        ~TelephoneMapper() = default;

        void insertEntity(Telephone& entity) override;
        void updateEntity(const Telephone& entity) override;

    protected:
        shared_ptr<Telephone> load(Resultset& rs) override ;
        vector<shared_ptr<Telephone>> loadAll(Resultset& rs) override ;

        const string& getFindStatement() override;
        const string& getFindAllStatement() override;
        const string& getFindChildrenStatement() override;
        const string& getDeleteStatement() override;

    private:
        void convertTelephoneTypeToString(string& strTelephoneType, const TelephoneType& telephoneType);
        void convertStringToTelephoneType(TelephoneType& telephoneType, const string& strTelephoneType);

        const string COLUMNS {" telephone_id, entity_id, telephone_number, extension, telephone_type, last_modified "};
        const string _findStatement {"SELECT " + COLUMNS + " FROM telephones WHERE telephone_id = :1"};
        const string _findAllStatement {"SELECT " + COLUMNS + " FROM telephones"};
        const string _findChildrenStatement {"SELECT " + COLUMNS + " FROM telephones WHERE entity_id = :1"};
        const string _deleteStatement {"DELETE FROM telephones WHERE telephone_id = :1"};

        const uint kTelephoneID = 1;
        const uint kEntityID = 2;
        const uint kTelephoneNumber = 3;
        const uint kExtension = 4;
        const uint kTelephoneType = 5;
        const uint kLastModified = 6;
    };
}
