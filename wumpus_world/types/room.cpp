#include "room.hpp"
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

using namespace std;

room::room()
{
    room_id = std::pair<int,int> (-1, -1); // default room id which is out of grid
}

room::room(std::pair<int, int> room_id)
{
    this->room_id = room_id;
}

std::pair<int, int> room::get_room_id()
{
    return this->room_id;
}

std::map<std::string, bool> room::get_knowledge()
{
    return this->knowledge;
}      

bool room::get_truth_value(std::string knowledge_term)
{
    return this->knowledge.at(knowledge_term);
}

void room::set_truth_value(std::string knowledge_term, bool tv)
{
    if (knowledge.find(knowledge_term) == knowledge.end())
    {
        knowledge.emplace(knowledge_term, tv);
    }

    else
    {
        this->knowledge.at(knowledge_term) = tv;
    }    
}

std::set<std::pair<int, int>> room::get_adjacents()
{
    std::set<std::pair<int, int>> adjacent_rooms_id;

    if (this->room_id.second + 1 < 4)
    {
        // insert upper neighbouring room
        adjacent_rooms_id.insert(std::pair<int, int>(this->room_id.first, this->room_id.second + 1));
    }

    if (this->room_id.second - 1 > -1)
    {
        // insert lower neighbour room
        adjacent_rooms_id.insert(std::pair<int, int>(this->room_id.first, this->room_id.second - 1));
    }

    if (this->room_id.first + 1 < 4)
    {
        // insert right neighbour room
        adjacent_rooms_id.insert(std::pair<int, int>(this->room_id.first + 1, this->room_id.second));
    }

    if (this->room_id.first - 1 > -1)
    {
        // insert left neighbour room
        adjacent_rooms_id.insert(std::pair<int, int>(this->room_id.first - 1, this->room_id.second));
    }

    return adjacent_rooms_id;
}
