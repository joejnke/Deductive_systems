#include "room.hpp"
#include "roomUTest.hpp"
#include <algorithm>
#include <string>
/*
 * add includes here 
 */

using namespace std;

int main()
{
    cout << "\n<<<<<<<<<<<<<<< Test room class >>>>>>>>>>>>>>>>\n";
    cout << test_parametrized_constructor() << "\n";
    cout << test_get_room_id() << "\n";
    cout << test_get_knowledge() << "\n";
    cout << test_get_truth_value() << "\n";
    cout << test_set_truth_value() << "\n";
    cout << test_get_adjacents();
    cout << "\n\nPassed " << get_RoomPassedTestCount() << "/" << get_RoomTestCount() << " tests";
    cout << "\n<<<<<<<<<<< end of room class test >>>>>>>>>>>>>\n";
    // Run and display all tests from here
}
