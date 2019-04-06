#pragma once

#include "IDataMapper.h"
#include <gmock/gmock.h>

namespace DataAccess
{
    template <typename T>
    class MockDataMapper : public IDataMapper<T>
    {

    public:
        MOCK_METHOD1_T(findById, shared_ptr<T>(int));
        MOCK_METHOD1_T(findChildren, shared_ptr<vector<shared_ptr<T>>>(int));
        MOCK_METHOD0_T(findAll, shared_ptr<vector<shared_ptr<T>>>());
        MOCK_METHOD1_T(insertEntity, int(T));
        MOCK_METHOD1_T(updateEntity, void(T));
        MOCK_METHOD1_T(deleteEntity, void(int));
    };
}
