#include "room.hpp"
#include <algorithm>
#include <string>

using namespace std;

int testCount = 0;
int passedTestCount = 0;
std::string testResult;

std::string test_parametrized_constructor()
{
    room testRoom(pair<int, int>(3, 2));

    // test if id is set correctly
    testCount++;
    testResult = ("\nTest room(room_id) for setting room_id: ");
    if (testRoom.get_room_id() == pair<int, int>(3, 2))
    {
        testResult += "\nPass ";
        passedTestCount++;
    }

    else
    {
        testResult += "\nFail";
    }

    // test if knowledge terms are set to default value of -1
    testCount++;
    testResult += ("\nTest room(room_id) for setting all knowledge terms to default value: ");
    if (!std::any_of(testRoom.get_knowledge().cbegin(),
                     testRoom.get_knowledge().cend(),
                     [](const auto &kTerm) { return kTerm.second != -1; })) 
    //this test fails because the std:any_of is iterating over [cbegin(), cend] instead of [cbegin(), cend)
    {
        testResult += "\nPass ";
        passedTestCount++;
    }
    else
    {
        testResult += "\nFail";
    }

    return testResult;
};

std::string test_get_room_id()
{
    room testRoom(pair<int, int>(3, 2));

    testCount++;
    testResult = ("\nTest get_room_id(): ");
    if (testRoom.get_room_id() == pair<int, int>(3, 2))
    {
        testResult += "\nPass ";
        passedTestCount++;
    }

    else
    {
        testResult += "\nFail";
    }

    return testResult;
};

std::string test_get_knowledge()
{
    room testRoom(pair<int, int>(3, 2));
    int default_tv = -1;
    std::map<std::string, int> knowledgeToCompare{{"breeze", default_tv},
                                                  {"glitter", default_tv},
                                                  {"pit", default_tv},
                                                  {"stench", default_tv},
                                                  {"visited", default_tv},
                                                  {"wumpus", default_tv}};

    testCount++;
    testResult = ("\nTest get_knowledge(): ");
    if (testRoom.get_knowledge() == knowledgeToCompare)
    {
        testResult += "\nPass ";
        passedTestCount++;
    }

    else
    {
        testResult += "\nFail";
    }

    return testResult;
};

std::string test_get_truth_value()
{
    room testRoom(pair<int, int>(3, 2));

    testRoom.set_truth_value("wumpus", true);
    testRoom.set_truth_value("pit", false);

    // check for "true" truth-value
    testCount++;
    testResult = ("\nTest get_truth_value(std::string knowledge_term) for returning \"true\" value: ");
    if (testRoom.get_truth_value("wumpus"))
    {
        testResult += "\nPass ";
        passedTestCount++;
    }
    else
    {
        testResult += "\nFail";
    }

    // check for "false" truth-value
    testCount++;
    testResult += ("\nTest get_truth_value(std::string knowledge_term) for returning \"false\" value: ");
    if (!testRoom.get_truth_value("pit"))
    {
        testResult += "\nPass ";
        passedTestCount++;
    }
    else
    {
        testResult += "\nFail";
    }

    // check for default truth-value which throws exception
    testCount++;
    testResult += ("\nTest get_truth_value(std::string knowledge_term) for returning default truth-value: ");
    try
    {
        bool _ = testRoom.get_truth_value("stench");
        testResult += "\nFail"; // fails if the above line does not throw exception
    }
    catch( ... )
    {
        testResult += "\nPass "; // passes if the expected exception is thrown
        passedTestCount++;        
    }
    // catch (std::string exceptionStr)
    // {
    //     if (exceptionStr == "truth value not yet set...")
    //     {
    //         testResult += "\nPass "; // passes if the expected exception is thrown
    //         passedTestCount++;
    //     }
    //     else
    //     {
    //         testResult += "\nFail -- throwing some other exception"; // fails if the expected exception is not thrown
    //     }
    // }

    return testResult;
};

std::string test_set_truth_value()
{
    room testRoom(pair<int, int>(3, 2));
    testRoom.set_truth_value("wumpus", true);

    testCount++;
    testResult = ("\nTest set_turth_value() for setting \"true\": ");
    if (testRoom.get_truth_value("wumpus"))
    {
        testResult += "\nPass ";
        passedTestCount++;
    }

    else
    {
        testResult += "\nFail";
    }

    testRoom.set_truth_value("wumpus", false);
    testCount++;
    testResult += ("\nTest set_turth_value() for setting \"false\": ");
    if (!testRoom.get_truth_value("wumpus"))
    {
        testResult += "\nPass ";
        passedTestCount++;
    }

    else
    {
        testResult += "\nFail";
    }

    return testResult;
};

std::string test_get_adjacents()
{
    room testCenterRoom(pair<int, int>(3, 2)); // room with four neigbours

    room testTopEdgeRoom(pair<int, int>(2, 4));    // room with three neigbours
    room testBottomEdgeRoom(pair<int, int>(3, 1)); // room with three neigbours
    room testLeftEdgeRoom(pair<int, int>(1, 3));   // room with three neigbours
    room testrightEdgeRoom(pair<int, int>(4, 2));  // room with three neigbours

    room testTopLeftRoom(pair<int, int>(1, 4));     // room with two neigbours
    room testTopRightRoom(pair<int, int>(4, 4));    // room with two neigbours
    room testBottomLeftRoom(pair<int, int>(1, 1));  // room with two neigbours
    room testBottomRightRoom(pair<int, int>(4, 1)); // room with two neigbours

    testCount++;
    testResult = ("\nTest get_room_id() for room with four neighbours: ");
    if (testCenterRoom.get_adjacents().size() == 4)
    {
        testResult += "\nPass ";
        passedTestCount++;
    }

    else
    {
        testResult += "\nFail";
    }

    testCount++;
    testResult += ("\nTest get_room_id() for rooms with three neighbours: ");
    if (testTopEdgeRoom.get_adjacents().size() == 3 and
        testBottomEdgeRoom.get_adjacents().size() == 3 and
        testLeftEdgeRoom.get_adjacents().size() == 3 and
        testrightEdgeRoom.get_adjacents().size() == 3)
    {
        testResult += "\nPass ";
        passedTestCount++;
    }

    else
    {
        testResult += "\nFail";
    }

    testCount++;
    testResult += ("\nTest get_room_id() for rooms with two neighbours: ");
    if (testTopLeftRoom.get_adjacents().size() == 2 and
        testTopRightRoom.get_adjacents().size() == 2 and
        testBottomLeftRoom.get_adjacents().size() == 2 and
        testBottomRightRoom.get_adjacents().size() == 2)
    {
        testResult += "\nPass ";
        passedTestCount++;
    }

    else
    {
        testResult += "\nFail";
    }

    return testResult;
};

int get_RoomTestCount()
{
    return testCount;
};

int get_RoomPassedTestCount()
{
    return passedTestCount;
};
