#include "CustomerManager.h"
#include "Logger.h"

using namespace ServiceLayer;

namespace BusinessLayer
{

    void CustomerManager::Create(DomainObject& entity)
    {
        Logger::instance().LogInfo("Entering BusinessLayer::Create");

        _unitOfWork.markforInsert(entity);

        Logger::instance().LogInfo("Leaving AddressMapper::insertEntity");
    }

    void CustomerManager::Update(DomainObject& entity)
    {
        Logger::instance().LogInfo("Entering BusinessLayer::Update");

        _unitOfWork.markForUpdate(entity);

        Logger::instance().LogInfo("Leaving BusinessLayer::Update");
    }

    void CustomerManager::Delete(DomainObject& entity)
    {
        Logger::instance().LogInfo("Entering BusinessLayer::Delete");

        _unitOfWork.markForDelete(entity);

        Logger::instance().LogInfo("Leaving BusinessLayer::Delete");
    }

    shared_ptr<vector<shared_ptr<DomainObject>>> CustomerManager::getAll()
    {
        Logger::instance().LogInfo("Entering BusinessLayer::getAll");

        vector<shared_ptr<DomainObject>> domainObjs {_repository.findAll()};
        shared_ptr<vector<shared_ptr<DomainObject>>> customers;

        for (const auto& domainObjPtr : domainObjs)
        {
            customers->push_back(domainObjPtr);
        }

        Logger::instance().LogInfo("Leaving BusinessLayer::getAll");
        return customers;
    }

    shared_ptr<DomainObject> CustomerManager::getById(int entityID)
    {
        Logger::instance().LogInfo("Entering BusinessLayer::getById");

        shared_ptr<DomainObject> customer {_repository.findById(entityID)};

        Logger::instance().LogInfo("Leaving BusinessLayer::getById");
        return customer;
    }

    void CustomerManager::saveChanges()
    {
        Logger::instance().LogInfo("Entering BusinessLayer::saveChanges");



        Logger::instance().LogInfo("Leaving BusinessLayer::saveChanges");
    }

}

