#include "room.hpp"
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

using namespace std;

room::room(std::pair<int, int> room_id)
{
    this->room_id = room_id;

    int default_tv = -1;
    this->knowledge = {{"breeze", default_tv},
                       {"glitter", default_tv},
                       {"pit", default_tv},
                       {"stench", default_tv},
                       {"visited", default_tv},
                       {"wumpus", default_tv}};
}

bool room::get_truth_value(std::string knowledge_term)
{
    if (this->knowledge.at(knowledge_term) == 0)
        return false;

    else if (this->knowledge.at(knowledge_term) == 1)
        return true;

    else
        throw "truth value not yet set...";
}

std::set<std::pair<int, int>> room::get_adjacents()
{
    std::set<std::pair<int, int>> adjacent_rooms_id;

    adjacent_rooms_id.insert(std::pair<int, int>(this->room_id.first, this->room_id.second + 1)); // insert upper neighbour room
    adjacent_rooms_id.insert(std::pair<int, int>(this->room_id.first, this->room_id.second - 1)); // insert lower neighbour room
    adjacent_rooms_id.insert(std::pair<int, int>(this->room_id.first - 1, this->room_id.second)); // insert left neighbour room
    adjacent_rooms_id.insert(std::pair<int, int>(this->room_id.first + 1, this->room_id.second)); // insert right neighbour room

    for (auto neighbour : adjacent_rooms_id)
    {
        // check if any of the neighbours is invalid (out of grid) and remove it from the set
        if (neighbour.first > 4 or neighbour.first < 1 or neighbour.second > 4 or neighbour.second < 1)
        {
            adjacent_rooms_id.erase(neighbour);
        }
    }

    return adjacent_rooms_id;
}
