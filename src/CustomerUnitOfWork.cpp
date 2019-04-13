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

        Customer& customer {dynamic_cast<Customer&>(obj)};

        if (isInNewObjectCache(customer))
        {
            Logger::instance().LogError("This object is already in the new object cache.");
            throw invalid_argument("This object is already in new object cache.");
        }

        if ( std::find(_dirtyObjects.begin(), _dirtyObjects.end(), obj) != _dirtyObjects.end() )
        {
            Logger::instance().LogError("Can not add to new object cache, object is already in modified object cache.");
            throw invalid_argument("Can not add to new object cache, object is already in modified object cache.");
        }

        if ( std::find(_removedObjects.begin(), _removedObjects.end(), obj) != _removedObjects.end() )
        {
            Logger::instance().LogError("Can not add to new object cache, object is already in delete object cache.");
            throw invalid_argument("Can not add to new object cache, object is already in delete object cache.");
        }

        int tempPrimaryKey {static_cast<int>(_newObjects.size() + 1)};
        obj.setID(tempPrimaryKey);
        _newObjects.push_back(customer);

        Logger::instance().LogInfo("Leaving CustomerUnitOfWork::markforInsert");
    }

    void CustomerUnitOfWork::markForUpdate(DomainObject& obj)
    {
        Logger::instance().LogInfo("Entering CustomerUnitOfWork::markforUpdate");

        if ( std::find(_dirtyObjects.begin(), _dirtyObjects.end(), obj) != _dirtyObjects.end() )
        {
            Logger::instance().LogError("This object is already in the dirty object cache.");
            throw invalid_argument("This object is already in the dirty object cache.");
        }

        if (std::find(_removedObjects.begin(), _removedObjects.end(), obj) != _removedObjects.end())
        {
            Logger::instance().LogError("Can not add to dirty object cache, object is already in the delete object cache.");
            throw invalid_argument("Can not add to dirty object cache, object is already in the delete object cache.");
        }

        _dirtyObjects.push_back(dynamic_cast<Customer&>(obj));

        Logger::instance().LogInfo("Leaving CustomerUnitOfWork::markforUpdate");
    }

    void CustomerUnitOfWork::markForDelete(DomainObject& obj)
    {
        Logger::instance().LogInfo("Entering CustomerUnitOfWork::markforDelete");

        if ( std::find(_dirtyObjects.begin(), _dirtyObjects.end(), obj) != _dirtyObjects.end() )
        {
            Logger::instance().LogError("Can not add to dirty object cache, object is already in the dirty object cache.");
            throw invalid_argument("Can not add to dirty object cache, object is already in the dirty object cache.");
        }

        if (std::find(_removedObjects.begin(), _removedObjects.end(), obj) != _removedObjects.end())
        {
            Logger::instance().LogError("This object is already in the delete object cache.");
            throw invalid_argument("This object is already in the delete object cache.");
        }

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

    bool CustomerUnitOfWork::isInNewObjectCache(const Customer& customer) const
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
}


