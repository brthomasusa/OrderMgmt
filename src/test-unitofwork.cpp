#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include "Customer.h"
#include "Address.h"
#include "Telephone.h"
#include "MockRepository.h"
#include "CustomerUnitOfWork.h"

using namespace std;
using namespace testing;
using ::testing::AtLeast;
using namespace DataAccess;
using namespace CommonLayer;

int main(int argc, char** argv)
{
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(IUnitOfWork_Test, IUnitOfWork_markForInsert_valid_domainobj)
{
    int custID {-1};
    ptime nullTime;
    Customer customer{custID, "Test Customer", "www.testcustomer.com", nullTime};

    NiceMock<MockRepository> repository;
    CustomerUnitOfWork uow {repository};
    ASSERT_NO_THROW(uow.markforInsert(customer));

}

TEST(IUnitOfWork_Test, IUnitOfWork_markForInsert_invalid_duplicate_domainobj)
{
    int custID {-1};
    ptime nullTime;
    Customer customer{custID, "Test Customer", "www.testcustomer.com", nullTime};

    NiceMock<MockRepository> repository;
    CustomerUnitOfWork uow {repository};

    EXPECT_NO_THROW(uow.markforInsert(customer));
    ASSERT_THROW(uow.markforInsert(customer), invalid_argument);
}

TEST(IUnitOfWork_Test, IUnitOfWork_markForInsert_invalid_dirty_domainobj)
{
    int custID {1};
    ptime nullTime;
    Customer customer{custID, "Test Customer", "www.testcustomer.com", nullTime};

    NiceMock<MockRepository> repository;
    CustomerUnitOfWork uow {repository};

    EXPECT_NO_THROW(uow.markForUpdate(customer));
    ASSERT_THROW(uow.markforInsert(customer), invalid_argument);
}

TEST(IUnitOfWork_Test, IUnitOfWork_markForInsert_invalid_removed_domainobj)
{
    int custID {1};
    ptime nullTime;
    Customer customer{custID, "Test Customer", "www.testcustomer.com", nullTime};

    NiceMock<MockRepository> repository;
    CustomerUnitOfWork uow {repository};

    EXPECT_NO_THROW(uow.markForDelete(customer));
    ASSERT_THROW(uow.markforInsert(customer), invalid_argument);
}















TEST(IUnitOfWork_Test, IUnitOfWork_saveChanges_insertEntity_called_once)
{
    int custID {-1};
    ptime nullTime;
    Customer customer{custID, "Test Customer", "www.testcustomer.com", nullTime};

    NiceMock<MockRepository> repository;

    {
        InSequence s;  // A<DomainObject&>()
        EXPECT_CALL(repository, insertEntity(dynamic_cast<DomainObject&>(customer))).Times(1).WillOnce(Return());
    }

    CustomerUnitOfWork uof {repository};
    uof.markforInsert(customer);
    uof.saveChanges();
}

//TEST(IUnitOfWork_Test, IUnitOfWork_saveChanges_insertEntity_called_twice)
//{
//    //ASSERT_THROW(statement, exception_type);
//}