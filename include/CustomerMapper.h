#pragma once

#include "Customer.h"
#include "IDataMapper.h"

using namespace CommonLayer;

namespace DataAccess
{
    class CustomerMapper : public IDataMapper<Customer>
    {

    public:
        CustomerMapper() = default;
        ~CustomerMapper() = default;

        void insertEntity(Customer& entity) override;
        void updateEntity(const Customer& entity) override;

    protected:
        shared_ptr<Customer> load(Resultset& rs) override ;
        vector<shared_ptr<Customer>> loadAll(Resultset& rs) override ;

        const string& getFindStatement() override;
        const string& getFindAllStatement() override;
        const string& getFindChildrenStatement() override;
        const string& getDeleteStatement() override;

    private:
        const string COLUMNS {" cust_id, cust_name, website, last_modified "};
        const string _findStatement {"SELECT " + COLUMNS + " FROM customers WHERE cust_id = :1"};
        const string _findAllStatement {"SELECT " + COLUMNS + " FROM customers"};
        const string _findChildrenStatement {"SELECT " + COLUMNS + " FROM customers"};
        const string _deleteStatement {"DELETE FROM customers WHERE cust_id = :1"};

        const uint kCustomerID = 1;
        const uint kCustomerName = 2;
        const uint kWebsite = 3;
        const uint kLastModified = 4;
    };
}
