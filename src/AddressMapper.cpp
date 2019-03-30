#include "AddressMapper.h"
#include "ocilib.hpp"
#include <iostream>

using namespace std;
using namespace ocilib;

namespace DataAccess
{
    void AddressMapper::insertEntity(Address& entity)
    {
        Logger::instance().LogInfo("Entering AddressMapper::insertEntity");

        int insertedKey {0};

        // OciLib::Statement::Bind to a string requires local variables only!!!
        int entityID {entity.getEntityId()};
        string line1 {entity.getAddressLine1()};
        string line2 {entity.getAddressLine2()};
        string city {entity.getCity()};
        string stateCode {entity.getStateCode()};
        string zipcode {entity.getZipcode()};

        auto calcStrLen = [] (const string& input) -> uint { return static_cast<uint >(input.length()); };

        string lastKeyStmt {"select address_id from addresses where rowid=(select max(rowid) from addresses)"};

        string sql = R"(
        INSERT INTO addresses
        (entity_id, address_line1, address_line2, city, state_code, zipcode)
        VALUES (:1, :2, :3, :4, :5, :6)
        )";

        try
        {

            Environment::Initialize();
            Connection connection("oracle18db/xepdb1", "cust_orders", "Info77Gum");
            Statement stmt(connection);

            stmt.Prepare(sql);
            string test {"Hello"};
            stmt.Bind(":1", entityID , BindInfo::In);
            stmt.Bind(":2", line1, calcStrLen(line1), BindInfo::In);
            stmt.Bind(":3", line2, calcStrLen(line2), BindInfo::In);
            stmt.Bind(":4", city, calcStrLen(city), BindInfo::In);
            stmt.Bind(":5", stateCode, calcStrLen(stateCode), BindInfo::In);
            stmt.Bind(":6", zipcode, calcStrLen(zipcode), BindInfo::In);

            stmt.ExecutePrepared();
            connection.Commit();

            // Get the key that was inserted for this new address record
            stmt.Execute(lastKeyStmt);
            Resultset rs = stmt.GetResultset();
            while (rs++)
            {
                insertedKey = rs.Get<int>(1);
            }

            // Update the AddressId field with the new key
            entity.setAddressId(insertedKey);

        }
        catch (exception &ex)
        {
            Logger::instance().LogError(ex.what());
        }

        Logger::instance().LogInfo("Leaving AddressMapper::insertEntity");
    }

    void AddressMapper::updateEntity(const Address& entity)
    {
        Logger::instance().LogInfo("Entering AddressMapper::updateEntity");

        int addressID {entity.getAddressId()};
        int entityID {entity.getEntityId()};

        // OciLib::Statement::Bind to a string requires local variables only!!!
        string line1 {entity.getAddressLine1()};
        string line2 {entity.getAddressLine2()};
        string city {entity.getCity()};
        string stateCode {entity.getStateCode()};
        string zipcode {entity.getZipcode()};

        auto calcStrLen = [] (const string& input) -> uint { return static_cast<uint >(input.length()); };

        string sql = R"(
        UPDATE addresses SET
        entity_id = :1,
        address_line1 = :2,
        address_line2 = :3,
        city = :4,
        state_code = :5,
        zipcode = :6
        WHERE address_id = :7
        )";

        try
        {

            Environment::Initialize();
            Connection connection("oracle18db/xepdb1", "cust_orders", "Info77Gum");
            Statement stmt(connection);

            stmt.Prepare(sql);

            stmt.Bind(":1", entityID , BindInfo::In);
            stmt.Bind(":2", line1, calcStrLen(line1), BindInfo::In);
            stmt.Bind(":3", line2, calcStrLen(line2), BindInfo::In);
            stmt.Bind(":4", city, calcStrLen(city), BindInfo::In);
            stmt.Bind(":5", stateCode, calcStrLen(stateCode), BindInfo::In);
            stmt.Bind(":6", zipcode, calcStrLen(zipcode), BindInfo::In);
            stmt.Bind(":7", addressID , BindInfo::In);

            stmt.ExecutePrepared();
            connection.Commit();

        }
        catch (exception &ex)
        {
            Logger::instance().LogError(ex.what());
        }

        Logger::instance().LogInfo("Leaving AddressMapper::updateEntity");
    }

    shared_ptr<Address> AddressMapper::load(Resultset& rs)
    {
        Logger::instance().LogInfo("Entering AddressMapper::load");

        shared_ptr<Address> address;

        try
        {

            while (rs.Next())
            {

                Timestamp tm = rs.Get<Timestamp>(kTimestamp);
                // string timeStamp = tm.ToString("DD/MM/YYYY HH24:MI:SS:FF6");
                string timeStamp = tm.ToString("DD/MM/YYYY HH:MI:SS:FF6 AM");

                address = make_shared<Address>(
                    rs.Get<int>(kAddressID),
                    rs.Get<int>(kEntityID),
                    rs.Get<string>(kLine1),
                    rs.Get<string>(kLine2),
                    rs.Get<string>(kCity),
                    rs.Get<string>(kState),
                    rs.Get<string>(kZipcode),
                    timeStamp
                );
            }

        }
        catch (exception &ex)
        {
            Logger::instance().LogError(ex.what());
        }

        Logger::instance().LogInfo("Leaving AddressMapper::load");
        return address;
    }

    vector<shared_ptr<Address>> AddressMapper::loadAll(Resultset& rs)
    {
        Logger::instance().LogInfo("Entering AddressMapper::loadAll");

        vector<shared_ptr<Address>> addresses;

        try
        {

            while (rs++)
            {
                Timestamp tm = rs.Get<Timestamp>(kTimestamp);
                string timeStamp = tm.ToString("DD/MM/YYYY HH24:MI:SS:FF6");

                shared_ptr<Address> address = make_shared<Address>(
                    rs.Get<int>(kAddressID),
                    rs.Get<int>(kEntityID),
                    rs.Get<string>(kLine1),
                    rs.Get<string>(kLine2),
                    rs.Get<string>(kCity),
                    rs.Get<string>(kState),
                    rs.Get<string>(kZipcode),
                    timeStamp
                );

                addresses.push_back(address);
            }

        }
        catch (exception &ex)
        {
            Logger::instance().LogError(ex.what());
        }

        Logger::instance().LogInfo("Leaving AddressMapper::loadAll");
        return addresses;
    }

    const string& AddressMapper::getFindStatement()
    {
        return _findStatement;
    }

    const string& AddressMapper::getFindChildrenStatement()
    {
        return _findChildrenStatement;
    }

    const string& AddressMapper::getFindAllStatement()
    {
        return _findAllStatement;
    }

    const string& AddressMapper::getDeleteStatement()
    {
        return _deleteStatement;
    }
}

