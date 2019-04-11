#pragma once

#include <vector>
#include "DomainObject.h"
#include "IRepository.h"
#include <algorithm>

using namespace std;
using namespace CommonLayer;

namespace DataAccess
{
    class IUnitOfWork
    {

    public:
        IUnitOfWork(IRepository& repository) : _repository{repository} {}
        virtual ~IUnitOfWork() = default;

        void markforInsert(DomainObject& obj)
        {

            if ( std::find(_dirtyObjects.begin(), _dirtyObjects.end(), obj) != _dirtyObjects.end() )
            {
                return;
            }

            if ( std::find(_removedObjects.begin(), _removedObjects.end(), obj) != _removedObjects.end() )
            {
                return;
            }

            if ( std::find(_newObjects.begin(), _newObjects.end(), obj) == _newObjects.end() )
            {
                _newObjects.push_back(obj);
            }

        }

        void markForUpdate(DomainObject& obj)
        {

            if ( std::find(_removedObjects.begin(), _removedObjects.end(), obj) != _removedObjects.end() )
            {
                return;
            }

            if (std::find(_dirtyObjects.begin(), _dirtyObjects.end(), obj) == _dirtyObjects.end() &&
                std::find(_newObjects.begin(), _newObjects.end(), obj) == _newObjects.end())
            {
                _dirtyObjects.push_back(obj);
            }
        }

        void markForDelete(DomainObject& obj)
        {

            // If it's in the new list (to be inserted), just remove
            // it from the new list and we're done.
            if (std::find(_newObjects.begin(), _newObjects.end(), obj) == _newObjects.end())
            {
                // remove it from new list
                return;
            }

            // If it's in the dirty list (to be updated), remove it
            // from the dirty list and add it to the deleted list
            if (std::find(_dirtyObjects.begin(), _dirtyObjects.end(), obj) == _dirtyObjects.end())
            {
                // remove from dirty list
            }

            // Make sure it's not already in the to be deleted list.
            if (std::find(_removedObjects.begin(), _removedObjects.end(), obj) == _removedObjects.end())
            {
                _removedObjects.push_back(obj);
            }
        }

        virtual void saveChanges() = 0;

    protected:
        IRepository& _repository;

    private:
        vector<DomainObject> _newObjects;
        vector<DomainObject> _dirtyObjects;
        vector<DomainObject> _removedObjects;
    };
}
