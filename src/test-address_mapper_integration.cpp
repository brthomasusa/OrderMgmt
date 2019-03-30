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

    ASSERT_EQ(address->getAddressId(), 1);
}

TEST(AddressMapperIntegration_Test, AddressMapper_findChildren)
{
    prepareDbForTesting();

    int entityID {3};

    AddressMapper addressMapper;
    vector<shared_ptr<Address>> addresses {addressMapper.findChildren(entityID)};

    uint records {1};
    ASSERT_EQ(records, addresses.size());
}

TEST(AddressMapperIntegration_Test, AddressMapper_findAll)
{
    prepareDbForTesting();

    AddressMapper addressMapper;
    vector<shared_ptr<Address>> addresses {addressMapper.findAll()};

    uint records {3};
    ASSERT_EQ(records, addresses.size());
}

TEST(AddressMapperIntegration_Test, AddressMapper_insertEntity)
{
    prepareDbForTesting();

    AddressMapper addressMapper;

    Address newAddress{
        -1,
        1,
        "XXX",
        "Ste X",
        "Arlington",
        "TX",
        "76222",
        "30-03-2019"
    };

    addressMapper.insertEntity(newAddress);
    int expectedResult {4};
    ASSERT_EQ(expectedResult, newAddress.getAddressId());
}

TEST(AddressMapperIntegration_Test, AddressMapper_updateEntity)
{
    prepareDbForTesting();

    AddressMapper addressMapper;

    Address edited{
            3,
            1,
            "XXX",
            "Ste X",
            "Arlington",
            "TX",
            "76222",
            "30-03-2019"
    };

    addressMapper.updateEntity(edited);
    shared_ptr<Address> address {addressMapper.findById(edited.getAddressId())};

    EXPECT_EQ(address->getAddressId(), edited.getAddressId());
    ASSERT_EQ(address->getAddressLine1(), edited.getAddressLine1());
}

TEST(AddressMapperIntegration_Test, AddressMapper_deleteEntity)
{
    prepareDbForTesting();

    int deletedAddressID{3};
    AddressMapper addressMapper;
    addressMapper.deleteEntity(deletedAddressID);
    shared_ptr<Address> address {addressMapper.findById(deletedAddressID)};

    ASSERT_EQ(address, nullptr);
}