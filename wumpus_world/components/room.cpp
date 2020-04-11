#include "room.hpp"
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

using namespace std;

typedef std::pair<int, int> roomIdType;

room::room()
{
    _room_id = roomIdType(-1, -1); // default room id which is out of grid
}

room::room(roomIdType room_id)
{
    _room_id = room_id;
}

roomIdType room::get_room_id()
{
    return _room_id;
}

std::map<std::string, bool> room::get_knowledge()
{
    return _knowledge;
}

bool room::get_truth_value(std::string knowledge_term)
{
    return _knowledge.at(knowledge_term);
}

void room::set_truth_value(std::string knowledge_term, bool tv)
{
    if (_knowledge.find(knowledge_term) == _knowledge.end())
    {
        _knowledge.emplace(knowledge_term, tv);
    }

    else
    {
        _knowledge.at(knowledge_term) = tv;
    }
}

std::set<std::pair<int, int>> room::get_adjacents()
{
    std::set<roomIdType> adjacent_rooms_id;

    if (_room_id.second + 1 < 4)
    {
        // insert upper neighbouring room
        adjacent_rooms_id.insert(roomIdType(_room_id.first,
                                            _room_id.second + 1));
    }

    if (_room_id.second - 1 > -1)
    {
        // insert lower neighbour room
        adjacent_rooms_id.insert(roomIdType(_room_id.first,
                                            _room_id.second - 1));
    }

    if (_room_id.first + 1 < 4)
    {
        // insert right neighbour room
        adjacent_rooms_id.insert(roomIdType(_room_id.first + 1,
                                            _room_id.second));
    }

    if (_room_id.first - 1 > -1)
    {
        // insert left neighbour room
        adjacent_rooms_id.insert(roomIdType(_room_id.first - 1,
                                            _room_id.second));
    }

    return adjacent_rooms_id;
}
