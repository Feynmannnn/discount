cmake_minimum_required(VERSION 3.10)
project(DiscountSystem)

set(CMAKE_CXX_STANDARD 17)

# Add Abseil
find_package(absl REQUIRED)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include(GoogleTest)

add_executable(discount_context_test discount_context_test.cc)
target_link_libraries(discount_context_test 
    ${GTEST_LIBRARIES} 
    pthread 
    absl::time
    discount_lib
)
target_include_directories(discount_context_test PRIVATE ${PROJECT_SOURCE_DIR})
gtest_discover_tests(discount_context_test)

add_executable(customer_service_test customer_service_test.cc)
target_link_libraries(customer_service_test 
    ${GTEST_LIBRARIES} 
    pthread
    discount_lib
)
target_include_directories(customer_service_test PRIVATE ${PROJECT_SOURCE_DIR})
gtest_discover_tests(customer_service_test)
