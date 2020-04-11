find_package(CxxTest)
if(CXXTEST_FOUND)
        include_directories(${CXXTEST_INCLUDE_DIR})
        include_directories(${CMAKE_SOURCE_DIR}/wumpus_world/components/)

        enable_testing()
        CXXTEST_ADD_TEST(wumpusTest components_test.cpp 
                         ${CMAKE_CURRENT_SOURCE_DIR}/roomUTest.hpp)
                
        target_link_libraries(wumpusTest room)

        install(TARGETS wumpusTest
                RUNTIME DESTINATION bin)
endif()
