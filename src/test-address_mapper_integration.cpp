#include "gtest/gtest.h"
#include <memory>
#include <vector>
#include "ocilib.hpp"
#include "AddressMapper.h"

using namespace std;
using namespace testing;
using namespace ocilib;
using namespace DataAccess;

void prepareDbForTesting()
{
    try
    {
        ocilib::Environment::Initialize();

        ocilib::Connection conn("oracle18db/xepdb1", "cust_orders", "Info77Gum");

        string sql {"begin sp_test_data_setup; end;"};
        ocilib::Statement stmt(conn);
        stmt.Execute(sql);

    }
    catch (std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }

    ocilib::Environment::Cleanup();
}

int main(int argc, char** argv)
{
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(AddressMapperIntegration_Test, AddressMapper_findById)
{
    prepareDbForTesting();

    int addressID {1};

    AddressMapper addressMapper;
    shared_ptr<Address> address {addressMapper.findById(addressID)};

    EXPECT_NE(address, nullptr);
    ASSERT_EQ(address->getAddressId(), 1);
}
