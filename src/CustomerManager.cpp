#include "CustomerManager.h"
#include "Logger.h"

using namespace ServiceLayer;

namespace BusinessLayer
{

    void CustomerManager::Create(DomainObject& entity)
    {
        Logger::instance().LogInfo("Entering CustomerManager::Create");

        _unitOfWork.markforInsert(entity);

        Logger::instance().LogInfo("Leaving CustomerManager::insertEntity");
    }

    void CustomerManager::Update(DomainObject& entity)
    {
        Logger::instance().LogInfo("Entering CustomerManager::Update");

        _unitOfWork.markForUpdate(entity);

        Logger::instance().LogInfo("Leaving CustomerManager::Update");
    }

    void CustomerManager::Delete(DomainObject& entity)
    {
        Logger::instance().LogInfo("Entering CustomerManager::Delete");

        _unitOfWork.markForDelete(entity);

        Logger::instance().LogInfo("Leaving CustomerManager::Delete");
    }

    shared_ptr<vector<shared_ptr<DomainObject>>> CustomerManager::getAll()
    {
        Logger::instance().LogInfo("Entering CustomerManager::getAll");

        vector<shared_ptr<DomainObject>> domainObjs {_repository.findAll()};
        shared_ptr<vector<shared_ptr<DomainObject>>> customers {make_shared<vector<shared_ptr<DomainObject>>>()};

        for (const auto& domainObjPtr : domainObjs)
        {
            customers->push_back(domainObjPtr);
        }

        Logger::instance().LogInfo("Leaving CustomerManager::getAll");
        return customers;
    }

    shared_ptr<DomainObject> CustomerManager::getById(int entityID)
    {
        Logger::instance().LogInfo("Entering CustomerManager::getById");

        shared_ptr<DomainObject> customer {_repository.findById(entityID)};

        Logger::instance().LogInfo("Leaving CustomerManager::getById");
        return customer;
    }

    void CustomerManager::saveChanges()
    {
        Logger::instance().LogInfo("Entering CustomerManager::saveChanges");

        _unitOfWork.saveChanges();

        Logger::instance().LogInfo("Leaving CustomerManager::saveChanges");
    }

}

