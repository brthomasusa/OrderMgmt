#include "gtest/gtest.h"
#include <memory>
#include <vector>
#include "ocilib.hpp"
#include "Inventory.h"
#include "InventoryMapper.h"

using namespace std;
using namespace testing;
using namespace ocilib;
using namespace DataAccess;
using namespace CommonLayer;

void prepareDbForTesting()
{
    try
    {
        ocilib::Environment::Initialize();

        ocilib::Connection conn("oracle18db/xepdb1", "cust_orders", "Info77Gum");

        string sql {"begin sp_test_data_setup; end;"};
        ocilib::Statement stmt(conn);
        stmt.Execute(sql);

    }
    catch (std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    ocilib::Environment::Cleanup();
}

int main(int argc, char** argv)
{
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Misc_Test, Inventory_InventoryMapper_findById)
{
    prepareDbForTesting();
    int inventoryID {22};

    InventoryMapper inventoryMapper;
    shared_ptr<Inventory> inventoryItem {inventoryMapper.findById(inventoryID)};

    ASSERT_EQ(inventoryItem->getID(), inventoryID);
}

TEST(Misc_Test, Inventory_InventoryMapper_findChildren)
{
    prepareDbForTesting();

    int vendorID {5};

    InventoryMapper inventoryMapper;
    vector<shared_ptr<Inventory>> inventoryItems {inventoryMapper.findChildren(vendorID)};

    uint records {9};
    ASSERT_EQ(records, inventoryItems.size());
}

TEST(Misc_Test, Inventory_InventoryMapper_findAll)
{
    prepareDbForTesting();

    InventoryMapper inventoryMapper;
    vector<shared_ptr<Inventory>> inventoryItems {inventoryMapper.findAll()};

    uint records {22};
    ASSERT_EQ(records, inventoryItems.size());
}

TEST(Misc_Test, Inventory_InventoryMapper_insertEntity)
{
    prepareDbForTesting();

    InventoryMapper inventoryMapper;
    ptime createdAt {second_clock::local_time()};

    Inventory inventoryItem
    {
        -1,
        6,
        "91788",
        "Curtain Rod, Brass",
        7.0,
        12.0,
        98,
        25,
        1.5,
        createdAt
    };

    inventoryMapper.insertEntity(inventoryItem);
    int expectedResult {23};
    ASSERT_EQ(expectedResult, inventoryItem.getID());
    ASSERT_NE(createdAt, inventoryItem.getLastModified());
}

TEST(Misc_Test, Inventory_InventoryMapper_updateEntity)
{

}