#include "InventoryMapper.h"
//#include "ocilib.hpp"

using namespace std;
//using namespace ocilib;

namespace DataAccess
{
    void InventoryMapper::insertEntity(Inventory& entity)
    {
        Logger::instance().LogInfo("Entering InventoryMapper::insertEntity");

        int insertedKey {0};

        // OciLib::Statement::Bind can only bind to local variables!!!
        int vendorID = entity.getVendorId();
        string sku {entity.getVendorSku()};
        string description {entity.getItemDescription()};
        double unitCost {entity.getUnitCost()};
        double price {entity.getPrice()};
        int onhand {entity.getQuantityOnhand()};
        int reorder {entity.getReorderQuantity()};
        double weight {entity.getItemWeight()};

        auto calcStrLen = [] (const string& input) -> uint { return static_cast<uint >(input.length()); };

        string lastKeyStmt {"select inventory_id from inventory where rowid=(select max(rowid) from inventory)"};

        string sql = R"(
        INSERT INTO inventory
        (vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified)
        VALUES (:1, :2, :3, :4, :5, :6, :7, :8, :9)
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
            stmt.Bind(":1", vendorID , BindInfo::In);
            stmt.Bind(":2", sku, calcStrLen(sku), BindInfo::In);
            stmt.Bind(":3", description, calcStrLen(description), BindInfo::In);
            stmt.Bind(":4", unitCost, BindInfo::In);
            stmt.Bind(":5", price, BindInfo::In);
            stmt.Bind(":6", onhand, BindInfo::In);
            stmt.Bind(":7", reorder, BindInfo::In);
            stmt.Bind(":8", weight, BindInfo::In);
            stmt.Bind(":9", ociTimeStamp, BindInfo::In);

            stmt.ExecutePrepared();
            connection.Commit();

            // Get the key that was inserted for this new address record
            stmt.Execute(lastKeyStmt);
            Resultset rs = stmt.GetResultset();
            while (rs++)
            {
                insertedKey = rs.Get<int>(1);
            }

            // Update the InventoryId field with the new key
            entity.setID(insertedKey);

            // Update the timestamp field
            string timeStamp = ociTimeStamp.ToString("YYYY-MON-DD HH24:MI:SS:FF6");
            entity.setLastModified(time_from_string(timeStamp));

        }
        catch (exception &ex)
        {
            Logger::instance().LogError(ex.what());
        }

        Logger::instance().LogInfo("Leaving InventoryMapper::insertEntity");
    }

    void InventoryMapper::updateEntity(const Inventory& entity)
    {
        Logger::instance().LogInfo("Entering AddressMapper::updateEntity");

        int inventoryID = entity.getID();
        int vendorID = entity.getVendorId();
        string sku {entity.getVendorSku()};
        string description {entity.getItemDescription()};
        double unitCost {entity.getUnitCost()};
        double price {entity.getPrice()};
        int onhand {entity.getQuantityOnhand()};
        int reorder {entity.getReorderQuantity()};
        double weight {entity.getItemWeight()};

        auto calcStrLen = [] (const string& input) -> uint { return static_cast<uint >(input.length()); };

        string sql = R"(
        UPDATE inventory SET
        vendor_id = :1,
        vendor_sku = :2,
        item_desc = :3,
        unit_cost = :4,
        price = :5,
        qty_on_hand = :6,
        qty_reorder = :7,
        item_weight_lbs = :8
        last_modified = :9
        WHERE inventory_id = :10
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
            stmt.Bind(":1", vendorID , BindInfo::In);
            stmt.Bind(":2", sku, calcStrLen(sku), BindInfo::In);
            stmt.Bind(":3", description, calcStrLen(description), BindInfo::In);
            stmt.Bind(":4", unitCost, BindInfo::In);
            stmt.Bind(":5", price, BindInfo::In);
            stmt.Bind(":6", onhand, BindInfo::In);
            stmt.Bind(":7", reorder, BindInfo::In);
            stmt.Bind(":8", weight, BindInfo::In);
            stmt.Bind(":9", ociTimeStamp, BindInfo::In);
            stmt.Bind(":10", inventoryID , BindInfo::In);

            stmt.ExecutePrepared();
            connection.Commit();

        }
        catch (exception &ex)
        {
            Logger::instance().LogError(ex.what());
        }

        Logger::instance().LogInfo("Leaving AddressMapper::updateEntity");
    }

    shared_ptr<Inventory> InventoryMapper::load(Resultset& rs)
    {
        Logger::instance().LogInfo("Entering InventoryMapper::load");

        shared_ptr<Inventory> inventoryItem;

        try
        {

            while (rs.Next())
            {


                Timestamp tm = rs.Get<Timestamp>(kTimestamp);
                string timeStamp = tm.ToString("YYYY-MON-DD HH24:MI:SS:FF6");
                ptime timeStampObj = time_from_string(timeStamp);

                inventoryItem = make_shared<Inventory>(
                        rs.Get<int>(kInventoryID),
                        rs.Get<int>(kVendorID),
                        rs.Get<string>(kVendorSku),
                        rs.Get<string>(kItemDescription),
                        rs.Get<double>(kUnitCost),
                        rs.Get<double>(kPrice),
                        rs.Get<int>(kQtyOnhand),
                        rs.Get<int>(kReorderQty),
                        rs.Get<double>(kItemWeight),
                        timeStampObj
                );
            }

        }
        catch (exception &ex)
        {
            Logger::instance().LogError(ex.what());
        }

        Logger::instance().LogInfo("Leaving InventoryMapper::load");
        return inventoryItem;
    }

    vector<shared_ptr<Inventory>> InventoryMapper::loadAll(Resultset& rs)
    {
        Logger::instance().LogInfo("Entering InventoryMapper::loadAll");

        vector<shared_ptr<Inventory>> inventory;

        try
        {

            while (rs++)
            {
                Timestamp tm = rs.Get<Timestamp>(kTimestamp);
                string timeStamp = tm.ToString("YYYY-MON-DD HH24:MI:SS:FF6");
                ptime timeStampObj = time_from_string(timeStamp);

                shared_ptr<Inventory> inventoryItem = make_shared<Inventory>(
                        rs.Get<int>(kInventoryID),
                        rs.Get<int>(kVendorID),
                        rs.Get<string>(kVendorSku),
                        rs.Get<string>(kItemDescription),
                        rs.Get<double>(kUnitCost),
                        rs.Get<double>(kPrice),
                        rs.Get<int>(kQtyOnhand),
                        rs.Get<int>(kReorderQty),
                        rs.Get<double>(kItemWeight),
                        timeStampObj
                );

                inventory.push_back(inventoryItem);
            }

        }
        catch (exception &ex)
        {
            Logger::instance().LogError(ex.what());
        }

        Logger::instance().LogInfo("Leaving InventoryMapper::loadAll");
        return inventory;
    }

    const string& InventoryMapper::getFindStatement()
    {
        return _findStatement;
    }

    const string& InventoryMapper::getFindChildrenStatement()
    {
        return _findChildrenStatement;
    }

    const string& InventoryMapper::getFindAllStatement()
    {
        return _findAllStatement;
    }

    const string& InventoryMapper::getDeleteStatement()
    {
        return _deleteStatement;
    }

} // DataAccess


