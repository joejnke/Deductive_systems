#include "agent.hpp"
#include "room.hpp"
#include "world.hpp"
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

using namespace std;

agent::agent()
{
    throw "!!! agent() not yet implemented ...";
}

agent::agent(world arena)
{
    throw "!!! agent(world arena) not yet implemented ...";
}

std::vector<std::pair<int, int>> agent::get_perception_history()
{
    return this->perception_history;
}

bool agent::does_stench(std::pair<int, int> room_id)
{
    return this->grid[room_id.first][room_id.second].get_truth_value("stench");
}

bool agent::does_glitter(std::pair<int, int> room_id)
{
    return this->grid[room_id.first][room_id.second].get_truth_value("glitter");
}

bool agent::does_bump(std::pair<int, int> room_id)
{
    return room_id.first > 3 or room_id.first < 0 or room_id.second > 3 or room_id.second < 0;
}

bool agent::has_breeze(std::pair<int, int> room_id)
{
    return this->grid[room_id.first][room_id.second].get_truth_value("breeze");
}

bool agent::has_wumpus(std::pair<int, int> room_id)
{
    return this->grid[room_id.first][room_id.second].get_truth_value("wumpus");
}

bool agent::is_safe(std::pair<int, int> room_id)
{
    throw "!!! is_safe(std::pair<int, int> room_id) not yet implemented ...";   
}

bool agent::heared_scream()
{
    return this->wumpusRoom == std::pair<int, int>(-1, -1); // Because when wumpus is killed, its room will be changed to (-1, -1)
}

void agent::go_to(std::pair<int, int> room_id)
{
    throw "!!! go_to(std::pair<int, int> room_id) not yet implemented ...";
}

void agent::grab(std::pair<int, int> room_id)
{
    throw "!!! grab(std::pair<int, int> room_id) not yet implemented ...";
}

void agent::shoot(std::pair<int, int> room_id)
{               
    throw "!!! shoot(std::pair<int, int> room_id) not yet implemented ...";
}

void agent::move_forward()
{
    throw "!!! move_forward() not yet implemented ...";
}

void agent::turn_left()
{
    throw "!!! turn_left() not yet implemented ...";
}

void agent::turn_right()
{
    throw "!!! turn_right() not yet implemented ...";
}

void agent::signal_to_UI()
{
    throw "!!! signal_to_UI() not yet implemented ...";
}

void agent::rule_match()
{
    set<std::pair<int, int>> adjacentRooms = this->grid[this->roomId.first][this->roomId.second].get_adjacents();
    for (auto adjRoom : adjacentRooms)
    {
        // enclose the code below in try catch because "get_truth_value" 
        // might throw if the requiered state is not yet set.
        if(has_wumpus(adjRoom))
        {
            shoot(adjRoom);
        }

        else if (does_glitter(adjRoom))
        {
            grab(adjRoom);
        }

        else if (is_safe(adjRoom))
        {
            this->okRooms.push(adjRoom);
        }

        else
        {
            go_to(this->okRooms.top());
        }
    }
}

void agent::program_evaluator()
{
    throw "!!! program_evaluator() not yet implemented ...";
}

void agent::play()
{
    throw "!!! play() not yet implemented ...";
}
