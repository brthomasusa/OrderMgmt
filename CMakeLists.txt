cmake_minimum_required(VERSION 3.12)
project(OrderManager_v1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -g3 -Wall -O0 -m64 --coverage -DBOOST_LOG_DYN_LINK -DOCI_IMPORT_LINKAGE -DOCI_CHARSET_ANSI")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(DBUILD_SHARED_LIB ON)
cmake_policy(SET CMP0079 NEW)

include_directories(
    include
    /home/bthomas/include
    /usr/local/include        
)

link_directories(lib /home/bthomas/lib /usr/local/lib /usr/lib /usr/lib/oracle/12.2/client64/lib)

add_subdirectory(lib)

target_link_libraries(OrderManager_v1
    boost_date_time
    boost_filesystem 
    boost_log 
    boost_log_setup 
    boost_thread 
    clntsh
    ocilib    
    m
    pthread
)

set_target_properties(OrderManager_v1 PROPERTIES LINKER_LANGUAGE CXX)

################################
# Test Libraries & Executables
################################

option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
message(STATUS "Enable testing: ${ENABLE_UNIT_TESTS}")

if(ENABLE_UNIT_TESTS)

    add_executable(address-mapper-integration_test "" include/MockDataMapper.h)
    target_sources(address-mapper-integration_test PRIVATE src/test-address_mapper_integration.cpp)
    target_link_libraries(address-mapper-integration_test PRIVATE OrderManager_v1 gcov boost_filesystem boost_log boost_log_setup boost_thread gmock gtest clntsh ocilib m pthread)
    set_target_properties(address-mapper-integration_test PROPERTIES LINKER_LANGUAGE CXX)

    add_executable(inventory-mapper_test "" src/test-inventory_mapper.cpp)
    target_sources(inventory-mapper_test PRIVATE src/test-inventory_mapper.cpp)
    target_link_libraries(inventory-mapper_test PRIVATE OrderManager_v1 gcov boost_filesystem boost_log boost_log_setup boost_thread gmock gtest clntsh ocilib m pthread)
    set_target_properties(inventory-mapper_test PROPERTIES LINKER_LANGUAGE CXX)

    add_executable(customer-repository_test "" src/test-customer_repository.cpp)
    target_sources(customer-repository_test PRIVATE src/test-customer_repository.cpp)
    target_link_libraries(customer-repository_test PRIVATE OrderManager_v1 gcov boost_filesystem boost_log boost_log_setup boost_thread gmock gtest clntsh ocilib m pthread)
    set_target_properties(customer-repository_test PROPERTIES LINKER_LANGUAGE CXX)

    add_executable(customer-repository-integration_test "" src/test-customer_repository_integration.cpp)
    target_sources(customer-repository-integration_test PRIVATE src/test-customer_repository_integration.cpp)
    target_link_libraries(customer-repository-integration_test PRIVATE OrderManager_v1 gcov boost_filesystem boost_log boost_log_setup boost_thread gmock gtest clntsh ocilib m pthread)
    set_target_properties(customer-repository-integration_test PROPERTIES LINKER_LANGUAGE CXX)

    add_executable(unit-of-work_test "" src/test-unitofwork.cpp src/test-unitofwork.cpp)
    target_sources(unit-of-work_test  PRIVATE src/test-unitofwork.cpp)
    target_link_libraries(unit-of-work_test  PRIVATE OrderManager_v1 gcov boost_filesystem boost_log boost_log_setup boost_thread gmock gtest clntsh ocilib m pthread)
    set_target_properties(unit-of-work_test  PROPERTIES LINKER_LANGUAGE CXX)

    add_executable(customer_test "" src/test-customer.cpp src/test-customer.cpp)
    target_sources(customer_test  PRIVATE src/test-customer.cpp)
    target_link_libraries(customer_test  PRIVATE OrderManager_v1 gcov boost_filesystem boost_log boost_log_setup boost_thread gmock gtest clntsh ocilib m pthread)
    set_target_properties(customer_test  PROPERTIES LINKER_LANGUAGE CXX)

    add_executable(customer-manager_test "" src/test-customer_manager.cpp src/test-customer_manager.cpp)
    target_sources(customer-manager_test  PRIVATE src/test-customer_manager.cpp)
    target_link_libraries(customer-manager_test  PRIVATE OrderManager_v1 gcov boost_filesystem boost_log boost_log_setup boost_thread gmock gtest clntsh ocilib m pthread)
    set_target_properties(customer-manager_test  PROPERTIES LINKER_LANGUAGE CXX)

    find_program(MEMORYCHECK_COMMAND NAMES valgrind)
    set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")

    include(CTest)
    
    enable_testing()

    add_test(NAME address-mapper-integration_test COMMAND $<TARGET_FILE:address-mapper-integration_test>)
    add_test(NAME inventory-mapper_test COMMAND $<TARGET_FILE:inventory-mapper_test>)
    add_test(NAME customer-repository_test COMMAND $<TARGET_FILE:customer-repository_test>)
    add_test(NAME customer-repository-integration_test COMMAND $<TARGET_FILE:customer-repository-integration_test>)
    add_test(NAME unit-of-work_test COMMAND $<TARGET_FILE:unit-of-work_test>)
    add_test(NAME customer_test COMMAND $<TARGET_FILE:customer_test>)
    add_test(NAME ccustomer-manager_test COMMAND $<TARGET_FILE:customer-manager_test>)


endif()
