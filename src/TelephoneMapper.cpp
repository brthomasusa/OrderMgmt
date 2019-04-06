#include "TelephoneMapper.h"

using namespace std;

namespace DataAccess
{
    void TelephoneMapper::insertEntity(Telephone& entity)
    {
        Logger::instance().LogInfo("Entering TelephoneMapper::insertEntity");

        int insertedKey {0};

        // OciLib::Statement::Bind can only bind to local variables!!!
        int entityID = entity.getEntityId();
        string telephoneNumber {entity.getTelephoneNumber()};
        string extension {entity.getExtension()};
        string telephoneType;
        convertTelephoneTypeToString(telephoneType, entity.getTelephoneType());

        auto calcStrLen = [] (const string& input) -> uint { return static_cast<uint >(input.length()); };

        string lastKeyStmt {"select telephone_id from telephones where rowid=(select max(rowid) from telephones)"};

        string sql = R"(
        INSERT INTO telephones
        (entity_id, telephone_number, extension, telephone_type, last_modified)
        VALUES (:1, :2, :3, :4, :5)
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
            stmt.Bind(":1", entityID , BindInfo::In);
            stmt.Bind(":2", telephoneNumber, calcStrLen(telephoneNumber), BindInfo::In);
            stmt.Bind(":3", extension, calcStrLen(extension), BindInfo::In);
            stmt.Bind(":4", telephoneType, calcStrLen(telephoneType), BindInfo::In);
            stmt.Bind(":5", ociTimeStamp, BindInfo::In);

            stmt.ExecutePrepared();
            connection.Commit();

            // Get the key that was inserted for this new address record
            stmt.Execute(lastKeyStmt);
            Resultset rs = stmt.GetResultset();
            while (rs++)
            {
                insertedKey = rs.Get<int>(1);
            }

            // Update the TelephoneId field with the new key
            entity.setID(insertedKey);

            // Update the timestamp field
            string timeStamp = ociTimeStamp.ToString("YYYY-MON-DD HH24:MI:SS:FF6");
            entity.setLastModified(time_from_string(timeStamp));

        }
        catch (exception &ex)
        {
            Logger::instance().LogError(ex.what());
        }

        Logger::instance().LogInfo("Leaving TelephoneMapper::insertEntity");
    }

    void TelephoneMapper::updateEntity(const Telephone& entity)
    {
        Logger::instance().LogInfo("Entering Telephone::updateEntity");

        int telephoneID = entity.getID();
        int entityID = entity.getEntityId();
        string telephoneNumber {entity.getTelephoneNumber()};
        string extension {entity.getExtension()};
        string telephoneType;
        convertTelephoneTypeToString(telephoneType, entity.getTelephoneType());

        auto calcStrLen = [] (const string& input) -> uint { return static_cast<uint >(input.length()); };

        string sql = R"(
        UPDATE telephones SET
        entity_id = :1,
        telephone_number = :2,
        extension = :3,
        telephone_type = :4,
        last_modified = :5
        WHERE telephone_id = :6
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
            stmt.Bind(":1", entityID , BindInfo::In);
            stmt.Bind(":2", telephoneNumber, calcStrLen(telephoneNumber), BindInfo::In);
            stmt.Bind(":3", extension, calcStrLen(extension), BindInfo::In);
            stmt.Bind(":4", telephoneType, calcStrLen(telephoneType), BindInfo::In);
            stmt.Bind(":5", ociTimeStamp, BindInfo::In);
            stmt.Bind(":6", telephoneID , BindInfo::In);

            stmt.ExecutePrepared();
            connection.Commit();

        }
        catch (exception &ex)
        {
            Logger::instance().LogError(ex.what());
        }

        Logger::instance().LogInfo("Leaving TelephoneMapper::updateEntity");
    }

    shared_ptr<Telephone> TelephoneMapper::load(Resultset& rs)
    {
        Logger::instance().LogInfo("Entering TelephoneMapper::load");

        shared_ptr<Telephone> telephone;

        try
        {

            while (rs.Next())
            {

                Timestamp tm = rs.Get<Timestamp>(kLastModified);
                string timeStamp = tm.ToString("YYYY-MON-DD HH24:MI:SS:FF6");
                ptime timeStampObj = time_from_string(timeStamp);

                TelephoneType telephoneType;
                convertStringToTelephoneType(telephoneType, rs.Get<string>(kTelephoneType));

                telephone = make_shared<Telephone>(
                    rs.Get<int>(kTelephoneID),
                    rs.Get<int>(kEntityID),
                    rs.Get<string>(kTelephoneNumber),
                    rs.Get<string>(kExtension),
                    telephoneType,
                    timeStampObj
                );
            }

        }
        catch (exception &ex)
        {
            Logger::instance().LogError(ex.what());
        }

        Logger::instance().LogInfo("Leaving TelephoneMapper::load");
        return telephone;
    }

    vector<shared_ptr<Telephone>> TelephoneMapper::loadAll(Resultset& rs)
    {
        Logger::instance().LogInfo("Entering TelephoneMapper::loadAll");

        vector<shared_ptr<Telephone>> telephones;


        Logger::instance().LogInfo("Leaving TelephoneMapper::loadAll");
        return telephones;
    }

    void TelephoneMapper::convertTelephoneTypeToString(string& strTelephoneType, const TelephoneType& telephoneType)
    {
        switch (telephoneType)
        {
            case TelephoneType::CELL :
                strTelephoneType = "CELL";
                break;

            case TelephoneType::FAX :
                strTelephoneType = "FAX";
                break;

            case TelephoneType::OFFICE :
                strTelephoneType = "OFFICE";
                break;
        }

    }

    void TelephoneMapper::convertStringToTelephoneType(TelephoneType& telephoneType, const string& strTelephoneType)
    {
        if (strTelephoneType == "CELL")
        {
            telephoneType = TelephoneType::CELL;
        }
        else if (strTelephoneType == "FAX")
        {
            telephoneType = TelephoneType::FAX;
        }
        else if (strTelephoneType == "OFFICE")
        {
            telephoneType = TelephoneType::OFFICE;
        }
    }

    const string& TelephoneMapper::getFindStatement()
    {
        return _findStatement;
    }

    const string& TelephoneMapper::getFindChildrenStatement()
    {
        return _findChildrenStatement;
    }

    const string& TelephoneMapper::getFindAllStatement()
    {
        return _findAllStatement;
    }

    const string& TelephoneMapper::getDeleteStatement()
    {
        return _deleteStatement;
    }
}

