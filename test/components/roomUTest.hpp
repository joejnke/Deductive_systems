#ifndef ROOM_UTEST_H_
#define ROOM_UTEST_H_

#include "room.hpp"
#include <cxxtest/TestSuite.h>
#include <string>

using namespace std;

class RoomTest : public CxxTest::TestSuite
{
public:
    void test_get_room_id(void)
    {
        room testRoom(pair<int, int>(3, 2));
        std::pair<int, int> expected(3, 2);

        std::pair<int, int> actual = testRoom.get_room_id();

        TS_TRACE("Testing get_room_id()");
        TS_ASSERT_EQUALS(actual, expected);
        TS_TRACE("End of get_room_id() test");
    }

    void test_get_knowledge(void)
    {
        room testRoom(pair<int, int>(3, 2));
        std::map<std::string, bool> expected{};

        std::map<std::string, bool> actual = testRoom.get_knowledge();

        TS_TRACE("Testing get_knowledge()");
        TS_ASSERT_EQUALS(actual, expected);
        TS_TRACE("End of get_knowledge() test");
    }

    void test_set_truth_value(void)
    {
        room testRoom(pair<int, int>(3, 2));

        testRoom.set_truth_value("wumpus", true);
        testRoom.set_truth_value("pit", false);
        std::map<std::string, bool> actual = testRoom.get_knowledge();

        TS_TRACE("Testing set_truth_vaue(std::string knowledge_term, bool tv)");
        TS_ASSERT(actual.at("wumpus"));
        TS_ASSERT(!actual.at("pit"));
        TS_TRACE("End of set_truth_value(std::string knowledge_term, bool tv) test");
    }

    void test_get_truth_value(void)
    {
        room testRoom(pair<int, int>(3, 2));
        testRoom.set_truth_value("wumpus", true);
        testRoom.set_truth_value("pit", false);

        bool actualWumpus = testRoom.get_truth_value("wumpus");
        bool actualPit = testRoom.get_truth_value("pit");

        TS_TRACE("Testing get_truth_vaue(std::string knowledge_term)");
        TS_ASSERT(actualWumpus);
        TS_ASSERT(!actualPit);
        TS_TRACE("End of get_truth_value(std::string knowledge_term) test");
    }

    void test_get_adjacents(void)
    {
        typedef std::set<std::pair<int, int>> adjIDs;
        typedef std::pair<int, int> roomIdType;
        room testCenterRoom(pair<int, int>(2, 2));      // have four neigbours
        room testTopEdgeRoom(pair<int, int>(2, 3));     // have three neigbours
        room testBottomEdgeRoom(pair<int, int>(1, 0));  // have three neigbours
        room testLeftEdgeRoom(pair<int, int>(0, 2));    // have three neigbours
        room testrightEdgeRoom(pair<int, int>(3, 1));   // have three neigbours
        room testTopLeftRoom(pair<int, int>(0, 3));     // have two neigbours
        room testTopRightRoom(pair<int, int>(3, 3));    // have two neigbours
        room testBottomLeftRoom(pair<int, int>(0, 0));  // have two neigbours
        room testBottomRightRoom(pair<int, int>(3, 0)); // have two neigbours
        adjIDs expectedCenterRoomAdjs{roomIdType(2, 1),
                                      roomIdType(2, 3),
                                      roomIdType(1, 2),
                                      roomIdType(3, 2)};
        adjIDs expectedTopEdgeRoomAdjs{roomIdType(2, 2),
                                       roomIdType(1, 3),
                                       roomIdType(3, 3)};
        adjIDs expectedBottomEdgeRoomAdjs{roomIdType(1, 1),
                                          roomIdType(0, 0),
                                          roomIdType(2, 0)};
        adjIDs expectedLeftEdgeRoomAdjs{roomIdType(0, 1),
                                        roomIdType(0, 3),
                                        roomIdType(1, 2)};
        adjIDs expectedRightEdgeRoomAdjs{roomIdType(3, 0),
                                         roomIdType(3, 2),
                                         roomIdType(2, 1)};
        adjIDs expectedTopLeftRoomAdjs{roomIdType(0, 2),
                                       roomIdType(1, 3)};
        adjIDs expectedTopRightRoomAdjs{roomIdType(3, 2),
                                        roomIdType(2, 3)};
        adjIDs expectedBottomLeftRoomAdjs{roomIdType(0, 1),
                                          roomIdType(1, 0)};
        adjIDs expectedBottomRightRoomAdjs{roomIdType(3, 1),
                                           roomIdType(2, 0)};

        adjIDs actualCenterRoomAdjs = testCenterRoom.get_adjacents();
        adjIDs actualTopEdgeRoomAdjs = testTopEdgeRoom.get_adjacents();
        adjIDs actualBottomEdgeRoomAdjs = testBottomEdgeRoom.get_adjacents();
        adjIDs actualLeftEdgeRoomAdjs = testLeftEdgeRoom.get_adjacents();
        adjIDs actualRightEdgeRoomAdjs = testrightEdgeRoom.get_adjacents();
        adjIDs actualTopLeftRoomAdjs = testTopLeftRoom.get_adjacents();
        adjIDs actualTopRightRoomAdjs = testTopRightRoom.get_adjacents();
        adjIDs actualBottomLeftRoomAdjs = testBottomLeftRoom.get_adjacents();
        adjIDs actualBottomRightRoomAdjs = testBottomRightRoom.get_adjacents();

        TS_TRACE("Testing get_adjacents()");
        TS_ASSERT_EQUALS(actualCenterRoomAdjs, expectedCenterRoomAdjs);
        TS_ASSERT_EQUALS(actualTopEdgeRoomAdjs, expectedTopEdgeRoomAdjs);
        TS_ASSERT_EQUALS(actualBottomEdgeRoomAdjs, expectedBottomEdgeRoomAdjs);
        TS_ASSERT_EQUALS(actualLeftEdgeRoomAdjs, expectedLeftEdgeRoomAdjs);
        TS_ASSERT_EQUALS(actualRightEdgeRoomAdjs, expectedRightEdgeRoomAdjs);
        TS_ASSERT_EQUALS(actualTopLeftRoomAdjs, expectedTopLeftRoomAdjs);
        TS_ASSERT_EQUALS(actualTopRightRoomAdjs, expectedTopRightRoomAdjs);
        TS_ASSERT_EQUALS(actualBottomLeftRoomAdjs, expectedBottomLeftRoomAdjs);
        TS_ASSERT_EQUALS(actualBottomRightRoomAdjs, expectedBottomRightRoomAdjs);
        TS_TRACE("End of get_adjacents() test");
    }
};

#endif /*ROOM_UTEST_H_*/