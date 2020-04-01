#ifndef ROOM_UTEST_H_
#define ROOM_UTEST_H_

#include <string>

using namespace std;

std::string test_parametrized_constructor();
std::string test_get_room_id();
std::string test_get_knowledge();
std::string test_get_truth_value();
std::string test_set_truth_value();
std::string test_get_adjacents();


int get_RoomTestCount();
int get_RoomPassedTestCount();

#endif /*ROOM_UTEST_H_*/