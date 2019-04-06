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

    find_program(MEMORYCHECK_COMMAND NAMES valgrind)
    set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")

    include(CTest)
    
    enable_testing()

    add_test(NAME address-mapper-integration_test COMMAND $<TARGET_FILE:address-mapper-integration_test>)


endif()
