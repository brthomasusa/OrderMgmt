#pragma once

#include <vector>
#include "Customer.h"
#include "Address.h"
#include "Telephone.h"
#include "IActionManager.h"

using namespace std;
using namespace CommonLayer;

namespace BusinessLayer
{

    class ICustomerManager : public IActionManager
    {
    public:
        ICustomerManager() = default;
        virtual ~ICustomerManager() = default;

    };

}