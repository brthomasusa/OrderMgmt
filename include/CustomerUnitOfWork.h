#pragma once

#include "IUnitOfWork.h"

namespace DataAccess
{
    class CustomerUnitOfWork : public IUnitOfWork
    {

    public:
        CustomerUnitOfWork(IRepository& repository) : IUnitOfWork(repository) {}
        virtual ~CustomerUnitOfWork() = default;

        virtual void saveChanges() override;
    };
}
