#include "room.hpp"
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

using namespace std;

room::room()
{
    this->default_tv = -1;
    this->knowledge = {{"breeze", this->default_tv},
                       {"glitter", this->default_tv},
                       {"pit", this->default_tv},
                       {"stench", this->default_tv},
                       {"visited", this->default_tv},
                       {"wumpus", this->default_tv}};
}

room::room(std::pair<int, int> room_id)
{
    this->room_id = room_id;

    this->default_tv = -1;
    this->knowledge = {{"breeze", this->default_tv},
                       {"glitter", this->default_tv},
                       {"pit", this->default_tv},
                       {"stench", this->default_tv},
                       {"visited", this->default_tv},
                       {"wumpus", this->default_tv}};
}

std::pair<int, int> room::get_room_id()
{
    return this->room_id;
}

std::map<std::string, int> room::get_knowledge()
{
    return this->knowledge;
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

void room::set_truth_value(std::string knowledge_term, bool tv)
{
    try
    {
        if (tv)
            this->knowledge.at(knowledge_term) = 1;
        else
            this->knowledge.at(knowledge_term) = 0;
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
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
