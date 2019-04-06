#pragma once
#include <string>
#include <memory>
#include "DomainObject.h"

using namespace std;

namespace CommonLayer
{
    class Inventory : public DomainObject
    {

    public:
        Inventory();

        Inventory(int id, int vendorId, const string& sku, const string& desc, double ucost,
                  double price, int onhand, int reorder, double weight, const ptime& timeStamp);

        virtual ~Inventory() = default;

        void setVendorId(int val);
        int getVendorId() const;
        void setVendorSku(const string& val);
        const string& getVendorSku() const;
        void setItemDescription(const string& val);
        const string& getItemDescription() const;
        void setUnitCost(double val);
        double getUnitCost() const;
        void setPrice(double val);
        double getPrice() const;
        void setQuantityOnhand(int val);
        int getQuantityOnhand() const;
        void setReorderQuantity(int val);
        int getReorderQuantity() const;
        void setItemWeight(double val);
        double getItemWeight() const;

    private:
        class Implementation;
        shared_ptr<Implementation> _impl;

    };
}