add_library(OrderManager_v1 SHARED
        ../include/Logger.h
        ../src/Logger.cpp
        ../include/IDataMapper.h
        ../include/Customer.h
        ../src/Customer.cpp
        ../include/Address.h
        ../src/Address.cpp
        ../include/Telephone.h
        ../src/Telephone.cpp
        ../include/AddressMapper.h
        ../src/AddressMapper.cpp
        ../include/DomainObject.h
        ../src/DomainObject.cpp
        ../include/IUnitOfWork.h
        ../include/Inventory.h
        ../src/Inventory.cpp
        ../include/InventoryMapper.h
        ../src/InventoryMapper.cpp
        ../include/MockDataMapper.h
        ../include/IRepository.h
        ../include/CustomerMapper.h
        ../src/CustomerMapper.cpp
        ../include/TelephoneMapper.h
        ../src/TelephoneMapper.cpp
        ../include/CustomerRepository.h ../src/CustomerRepository.cpp)
