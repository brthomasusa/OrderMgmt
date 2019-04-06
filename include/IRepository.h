#pragma once

#include "IDataMapper.h"

namespace DataAccess
{
    template <typename T>
    class IRepository
    {
    public:
        IRepository(const IDataMapper<T>& dataMapper);
        virtual ~IRepository() = default;

        virtual T findById(int entityID) = 0;
        virtual shared_ptr<T> findChildren(int parentID) = 0;
        virtual shared_ptr<T> findAll() = 0;
        virtual void insertEntity(T& entity) = 0;
        virtual void updateEntity(const T& entity) = 0;
        virtual void deleteEntity(int entityID) = 0;
    };
}