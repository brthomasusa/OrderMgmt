#include "gtest/gtest.h"
#include <memory>
#include <vector>
#include "Customer.h"
#include "CustomerMapper.h"
#include "CustomerRepository.h"

using namespace std;
using namespace testing;
using namespace DataAccess;
using namespace CommonLayer;

int main(int argc, char** argv)
{
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

