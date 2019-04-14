#pragma once

#include "IRepository.h"
#include "IUnitOfWork.h"
#include "IActionManager.h"

using namespace DataAccess;

namespace BusinessLayer
{

    class CustomerManager : public IActionManager
    {

    public:
        explicit CustomerManager(IUnitOfWork& uow, IRepository& repository) : _unitOfWork{uow}, _repository{repository} {}
        virtual ~CustomerManager() = default;

        void Create(DomainObject& entity) override;
        void Update(DomainObject& entity) override;
        void Delete(DomainObject& entity) override;
        shared_ptr<vector<shared_ptr<DomainObject>>> getAll() override;
        shared_ptr<DomainObject> getById(int entityID) override;
        void saveChanges() override;

        const IUnitOfWork& getUnitOfWork() const { return _unitOfWork; }

    private:
        IUnitOfWork& _unitOfWork;
        IRepository& _repository;
    };
}
