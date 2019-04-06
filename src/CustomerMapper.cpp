#include "CustomerMapper.h"
#include "ocilib.hpp"

using namespace ocilib;

namespace DataAccess
{
    void CustomerMapper::insertEntity(Customer& entity)
    {
        Logger::instance().LogInfo("Entering CustomerMapper::insertEntity");

        int insertedKey {0};

        // OciLib::Statement::Bind can only bind to local variables!!!
        string custName {entity.getCustomerName()};
        string website {entity.getWebsite()};

        auto calcStrLen = [] (const string& input) -> uint { return static_cast<uint >(input.length()); };

        string lastKeyStmt {"select cust_id from customers where rowid=(select max(rowid) from customers)"};

        string sql = R"(
        INSERT INTO customers
        (cust_name, website, last_modified)
        VALUES (:1, :2, :3)
        )";

        try
        {

            Environment::Initialize();
            Connection connection("oracle18db/xepdb1", "cust_orders", "Info77Gum");
            Statement stmt(connection);

            // Can only be initialized after call to Environment::Initialize()
            Timestamp ociTimeStamp(Timestamp::NoTimeZone);
            ociTimeStamp = Timestamp::SysTimestamp();

            stmt.Prepare(sql);
            stmt.Bind(":1", custName, calcStrLen(custName), BindInfo::In);
            stmt.Bind(":2", website, calcStrLen(website), BindInfo::In);
            stmt.Bind(":3", ociTimeStamp, BindInfo::In);

            stmt.ExecutePrepared();
            connection.Commit();

            // Get the key that was inserted for this new address record
            stmt.Execute(lastKeyStmt);
            Resultset rs = stmt.GetResultset();
            while (rs++)
            {
                insertedKey = rs.Get<int>(1);
            }

            // Update the setID field with the new key
            entity.setID(insertedKey);

            // Update the timestamp field
            string timeStamp = ociTimeStamp.ToString("YYYY-MON-DD HH24:MI:SS:FF6");
            entity.setLastModified(time_from_string(timeStamp));

        }
        catch (exception &ex)
        {
            Logger::instance().LogError(ex.what());
        }

        Logger::instance().LogInfo("Leaving CustomerMapper::insertEntity");
    }

    void CustomerMapper::updateEntity(const Customer& entity)
    {
        Logger::instance().LogInfo("Entering CustomerMapper::updateEntity");

        // OciLib::Statement::Bind to a string requires local variables only!!!
        int custID {entity.getID()};
        string custName {entity.getCustomerName()};
        string website {entity.getWebsite()};

        auto calcStrLen = [] (const string& input) -> uint { return static_cast<uint >(input.length()); };

        string sql = R"(
        UPDATE customers SET
        cust_name = :1,
        website = :2,
        last_modified = :3
        WHERE cust_id = :4
        )";

        try
        {

            Environment::Initialize();
            Connection connection("oracle18db/xepdb1", "cust_orders", "Info77Gum");
            Statement stmt(connection);

            // Can only be initialized after call to Environment::Initialize()
            Timestamp ociTimestamp(Timestamp::NoTimeZone);
            ociTimestamp = Timestamp::SysTimestamp();

            stmt.Prepare(sql);

            stmt.Bind(":1", custName, calcStrLen(custName), BindInfo::In);
            stmt.Bind(":2", website, calcStrLen(website), BindInfo::In);
            stmt.Bind(":3", ociTimestamp, BindInfo::In);
            stmt.Bind(":4", custID , BindInfo::In);

            stmt.ExecutePrepared();
            connection.Commit();

        }
        catch (exception &ex)
        {
            Logger::instance().LogError(ex.what());
        }

        Logger::instance().LogInfo("Leaving CustomerMapper::updateEntity");
    }

    shared_ptr<Customer> CustomerMapper::load(Resultset& rs)
    {
        Logger::instance().LogInfo("Entering CustomerMapper::load");

        shared_ptr<Customer> customer;

        try
        {

            while (rs.Next())
            {
                Timestamp tm = rs.Get<Timestamp>(kLastModified);
                string timeStamp = tm.ToString("YYYY-MON-DD HH24:MI:SS:FF6");
                ptime timeStampObj = time_from_string(timeStamp);

                customer = make_shared<Customer>(
                    rs.Get<int>(kCustomerID),
                    rs.Get<string>(kCustomerName),
                    rs.Get<string>(kWebsite),
                    timeStampObj
                );
            }

        }
        catch (exception &ex)
        {
            Logger::instance().LogError(ex.what());
        }

        Logger::instance().LogInfo("Leaving CustomerMapper::load");
        return customer;
    }

    vector<shared_ptr<Customer>> CustomerMapper::loadAll(Resultset& rs)
    {
        Logger::instance().LogInfo("Entering CustomerMapper::loadAll");

        vector<shared_ptr<Customer>> customers;

        try
        {

            while (rs++)
            {
                Timestamp tm = rs.Get<Timestamp>(kLastModified);
                string timeStamp = tm.ToString("YYYY-MON-DD HH24:MI:SS:FF6");
                ptime timeStampObj = time_from_string(timeStamp);

                shared_ptr<Customer> customer = make_shared<Customer>(
                    rs.Get<int>(kCustomerID),
                    rs.Get<string>(kCustomerName),
                    rs.Get<string>(kWebsite),
                    timeStampObj
                );

                customers.push_back(customer);
            }

        }
        catch (exception &ex)
        {
            Logger::instance().LogError(ex.what());
        }

        Logger::instance().LogInfo("Leaving CustomerMapper::loadAll");
        return customers;
    }

    const string& CustomerMapper::getFindStatement()
    {
        return _findStatement;
    }

    const string& CustomerMapper::getFindChildrenStatement()
    {
        return _findChildrenStatement;
    }

    const string& CustomerMapper::getFindAllStatement()
    {
        return _findAllStatement;
    }

    const string& CustomerMapper::getDeleteStatement()
    {
        return _deleteStatement;
    }

}

