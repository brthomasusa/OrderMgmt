#include "CustomerUnitOfWork.h"
#include "Logger.h"
#include <boost/algorithm/string/predicate.hpp>
#include <algorithm>
#include <stdexcept>

using namespace ServiceLayer;

namespace DataAccess
{
    CustomerUnitOfWork::~CustomerUnitOfWork() {}

    void CustomerUnitOfWork::markforInsert(DomainObject& obj)
    {
        Logger::instance().LogInfo("Entering CustomerUnitOfWork::markforInsert");

        checkObjectCaches(obj);
        int tempPrimaryKey {static_cast<int>(_newObjects.size() + 1)};
        obj.setID(tempPrimaryKey);
        _newObjects.push_back(dynamic_cast<Customer&>(obj));

        Logger::instance().LogInfo("Leaving CustomerUnitOfWork::markforInsert");
    }

    void CustomerUnitOfWork::markForUpdate(DomainObject& obj)
    {
        Logger::instance().LogInfo("Entering CustomerUnitOfWork::markforUpdate");

        checkObjectCaches(obj);
        _dirtyObjects.push_back(dynamic_cast<Customer&>(obj));

        Logger::instance().LogInfo("Leaving CustomerUnitOfWork::markforUpdate");
    }

    void CustomerUnitOfWork::markForDelete(DomainObject& obj)
    {
        Logger::instance().LogInfo("Entering CustomerUnitOfWork::markforDelete");

        checkObjectCaches(obj);
        _removedObjects.push_back(dynamic_cast<Customer&>(obj));

        Logger::instance().LogInfo("Leaving CustomerUnitOfWork::markforDelete");
    }

    void CustomerUnitOfWork::saveChanges()
    {
        Logger::instance().LogInfo("Entering CustomerUnitOfWork::saveChanges");

        // Do inserts
        for (Customer& entity : _newObjects)
        {
            _repository.insertEntity(entity);
        }
        _newObjects.clear();

        // Do updates and then clear cache
        for (const Customer& entity : _dirtyObjects)
        {
            _repository.updateEntity(entity);
        }
        _dirtyObjects.clear();

        // Do deletes and then clear cache
        for (const Customer& entity : _removedObjects)
        {
            _repository.deleteEntity(entity.getID());
        }
        _removedObjects.clear();

        Logger::instance().LogInfo("Leaving CustomerUnitOfWork::saveChanges");
    }

    bool CustomerUnitOfWork::checkNewObjectCache(const Customer& customer) const
    {
        Logger::instance().LogInfo("Entering CustomerUnitOfWork::isInNewObjectCache");

        bool retVal {false};

        for (const Customer& objectInCache : _newObjects)
        {
            if (boost::iequals(customer.getCustomerName(), objectInCache.getCustomerName()) )
            {
                retVal = true;
                break;
            }
        }

        Logger::instance().LogInfo("Leaving CustomerUnitOfWork::isInNewObjectCache");

        return retVal;
    }

    void CustomerUnitOfWork::checkObjectCaches(const DomainObject& obj) const
    {
        Logger::instance().LogInfo("Entering CustomerUnitOfWork::isInAnyObjectCache");

        if (checkNewObjectCache(dynamic_cast<const Customer&>(obj)))
        {
            Logger::instance().LogError("This object is already in the new object cache.");
            throw invalid_argument("This object is already in new object cache.");
        }

        if ( std::find(_dirtyObjects.begin(), _dirtyObjects.end(), obj) != _dirtyObjects.end() )
        {
            Logger::instance().LogError("This object is already in modified object cache.");
            throw invalid_argument("This object is already in modified object cache.");
        }

        if ( std::find(_removedObjects.begin(), _removedObjects.end(), obj) != _removedObjects.end() )
        {
            Logger::instance().LogError("This object is already in delete object cache.");
            throw invalid_argument("This object is already in delete object cache.");
        }

        Logger::instance().LogInfo("Leaving CustomerUnitOfWork::isInAnyObjectCache");
    }
}


