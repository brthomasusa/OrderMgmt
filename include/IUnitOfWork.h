#pragma once

#include <vector>
#include "DomainObject.h"
#include <cassert>
#include <algorithm>

using namespace std;

namespace CommonLayer
{
    class IUnitOfWork
    {

    public:
        void registerNew(DomainObject& obj)
        {
            assert(obj.getID() != NULL);

            // Assert not in _dirtyObjects
            assert( std::find(_dirtyObjects.begin(), _dirtyObjects.end(), obj) == _dirtyObjects.end() );

            // Assert not in removedObjects
            assert( std::find(_removedObjects.begin(), _removedObjects.end(), obj) == _removedObjects.end() );

            // Assert not in _newObjects
            assert( std::find(_newObjects.begin(), _newObjects.end(), obj) == _newObjects.end() );

            _newObjects.push_back(obj);
        }

        void registerDirty(DomainObject& obj)
        {
            assert(obj.getID() != NULL);
            assert( std::find(_removedObjects.begin(), _removedObjects.end(), obj) == _removedObjects.end() );

            if (std::find(_dirtyObjects.begin(), _dirtyObjects.end(), obj) == _dirtyObjects.end() &&
                std::find(_newObjects.begin(), _newObjects.end(), obj) == _newObjects.end())
            {
                _dirtyObjects.push_back(obj);
            }
        }

        void registerRemoved(DomainObject& obj)
        {
            assert(obj.getID() != NULL);

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

        void registerClean(DomainObject& obj)
        {
            // This would be where objects freshly pulled from
            // the database would be stored (until edited or deleted).

            assert(obj.getID() != NULL);
        }

    private:
        vector<DomainObject> _newObjects;
        vector<DomainObject> _dirtyObjects;
        vector<DomainObject> _removedObjects;
    };
}
