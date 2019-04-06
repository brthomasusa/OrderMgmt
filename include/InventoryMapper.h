#pragma once

#include "Inventory.h"
#include "IDataMapper.h"

using namespace CommonLayer;

namespace DataAccess
{
    class InventoryMapper : public IDataMapper<Inventory>
    {

    public:
        InventoryMapper()  = default;
        ~InventoryMapper() = default;

        void insertEntity(Inventory& entity) override;
        void updateEntity(const Inventory& entity) override;

    protected:
        shared_ptr<Inventory> load(Resultset& rs) override ;
        vector<shared_ptr<Inventory>> loadAll(Resultset& rs) override ;

        const string& getFindStatement() override;
        const string& getFindAllStatement() override;
        const string& getFindChildrenStatement() override;
        const string& getDeleteStatement() override;

    private:
        const string COLUMNS {" inventory_id, vendor_id, vendor_sku, item_desc, unit_cost, price, qty_on_hand, qty_reorder, item_weight_lbs, last_modified "};
        const string _findStatement {"SELECT " + COLUMNS + " FROM inventory WHERE inventory_id = :1"};
        const string _findAllStatement {"SELECT " + COLUMNS + " FROM inventory"};
        const string _findChildrenStatement {"SELECT " + COLUMNS + " FROM inventory WHERE vendor_id = :1"};
        const string _deleteStatement {"DELETE FROM inventory WHERE inventory_id = :1"};

        const uint kInventoryID = 1;
        const uint kVendorID = 2;
        const uint kVendorSku = 3;
        const uint kItemDescription = 4;
        const uint kUnitCost = 5;
        const uint kPrice = 6;
        const uint kQtyOnhand = 7;
        const uint kReorderQty = 8;
        const uint kItemWeight = 9;
        const uint kTimestamp = 10;

    };

} // DataAccess




