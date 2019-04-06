#include "Inventory.h"

namespace CommonLayer
{
    class Inventory::Implementation
    {

    public:
        Implementation() = default;
        ~Implementation() = default;

        int _vendorID;
        string _vendorSku;
        string _itemDescription;
        double _unitCost;
        double _price;
        int _qtyOnhand;
        int _qtyReorder;
        double _itemWeight;
    };

    Inventory::Inventory() : DomainObject() { _impl = make_shared<Implementation>(); }

    Inventory::Inventory(int id, int vendorId, const string& sku, const string& desc, double ucost,
                         double price, int onhand, int reorder, double weight, const ptime& timeStamp)
            : DomainObject(id, timeStamp)
    {
        _impl = make_shared<Implementation>();

        _impl->_vendorID = vendorId;
        _impl->_vendorSku = sku;
        _impl->_itemDescription = desc;
        _impl->_unitCost = ucost;
        _impl->_price = price;
        _impl->_qtyOnhand = onhand;
        _impl->_qtyReorder = reorder;
        _impl->_itemWeight = weight;
    }

    void Inventory::setVendorId(int val) { _impl->_vendorID = val; }
    int Inventory::getVendorId() const { return _impl->_vendorID; }
    void Inventory::setVendorSku(const string& val) { _impl->_vendorSku = val; }
    const string& Inventory::getVendorSku() const { return _impl->_vendorSku; }
    void Inventory::setItemDescription(const string& val) { _impl->_itemDescription = val; }
    const string& Inventory::getItemDescription() const { return _impl->_itemDescription; }
    void Inventory::setUnitCost(double val) { _impl->_unitCost = val; }
    double Inventory::getUnitCost() const { return _impl->_unitCost; }
    void Inventory::setPrice(double val) { _impl->_price = val; }
    double Inventory::getPrice() const { return _impl->_price; }
    void Inventory::setQuantityOnhand(int val) { _impl->_qtyOnhand = val; }
    int Inventory::getQuantityOnhand() const { return _impl->_qtyOnhand; }
    void Inventory::setReorderQuantity(int val) { _impl->_qtyReorder = val; }
    int Inventory::getReorderQuantity() const { return _impl->_qtyReorder; }
    void Inventory::setItemWeight(double val) { _impl->_itemWeight = val; }
    double Inventory::getItemWeight() const { return _impl->_itemWeight; }


}

