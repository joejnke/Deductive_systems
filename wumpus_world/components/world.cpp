#include "room.hpp"
#include "world.hpp"
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <string>
#include <utility>

using namespace std;

world::world()
{
    _agentRoomId = roomIdType(0, 0);
    _agentIsAlive = true;
    _agentRemainingArrow = 1;
    _agentFoundGold = false;
    _wumpusIsAlive = true;
}

roomIdType world::uniqueRandomRoomIdGenrator(std::set<roomIdType> forbiddenRoomIds)
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, 3);
    roomIdType uniqueRoomId(distr(eng), distr(eng));

    while (forbiddenRoomIds.find(roomIdType(0, 0)) !=
           forbiddenRoomIds.end())
    {
        uniqueRoomId = roomIdType(distr(eng), distr(eng));
    }

    return uniqueRoomId;
}

void world::grid_init()
{
    std::set<roomIdType> forbiddenRoomIds{roomIdType(0, 0),
                                          roomIdType(0, 1),
                                          roomIdType(1, 0)};

    // place the wumpus
    // generate random and unique room Id for the wumpus
    _wumpusRoomId = uniqueRandomRoomIdGenrator(forbiddenRoomIds);
    // update the knowledge in the wumpus' room
    _grid[_wumpusRoomId.first][_wumpusRoomId.second].set_truth_value("wumpus",
                                                                     true);
    // insert the wumpus' room Id into forbidden room IDs                                                                     
    forbiddenRoomIds.insert(_wumpusRoomId);
    // update the knowledge in the neighbouring rooms to wumpus' room
    for (auto adjs : _grid[_wumpusRoomId.first][_wumpusRoomId.second].get_adjacents())
    {
        _grid[adjs.first][adjs.second].set_truth_value("stench", true);
    }

    // place gold
    // generate random and unique room Id for the gold
    roomIdType goldRoomId = uniqueRandomRoomIdGenrator(forbiddenRoomIds);
    // update the knowledge in the gold's room
    _grid[goldRoomId.first][goldRoomId.second].set_truth_value("glitter", true);
    // insert the gold's room Id into forbidden room IDs                                                                     
    forbiddenRoomIds.insert(goldRoomId);

    // place the pits
    for (int i = 0; i < 3; i++)
    {
        // generate random and unique room Id for a pit
        roomIdType pitRoomId = uniqueRandomRoomIdGenrator(forbiddenRoomIds);
        // update the knowledge in the pit's room
        _grid[pitRoomId.first][pitRoomId.second].set_truth_value("pit", true);
        // insert the pit's room Id into forbidden room IDs                                                                     
        forbiddenRoomIds.insert(pitRoomId);
        // update the knowledge in the neighbouring rooms to pits' room
        for (auto adjs : _grid[pitRoomId.first][pitRoomId.second].get_adjacents())
        {
            _grid[adjs.first][adjs.second].set_truth_value("breeze", true);
        }        
    }
}

vector<vector<room>> world::get_grid()
{
    return _grid;
}

int world::get_model()
{
    return _model;
}

room world::get_room(roomIdType roomId)
{
    return _grid[roomId.first][roomId.second];
}

roomIdType world::get_agentRoomId()
{
    return _agentRoomId;
}

int world::get_agentRemainingArrow()
{
    return _agentRemainingArrow;
}

bool world::isAgentAlive()
{
    return _agentIsAlive;
}

bool world::doesAgentFoundGold()
{
    return _agentFoundGold;
}

roomIdType world::get_wumpusRoomId()
{
    return _wumpusRoomId;
}

bool world::isWumpusAlive()
{
    return _wumpusIsAlive;
}

bool world::kill_wumpus_at(roomIdType room_id)
{
    room wumpus_room = _grid[room_id.first][room_id.second]; // update to the room at room_id in the grid

    // if there is wumpus in the room and the agent has arrow to use
    if (wumpus_room.get_truth_value("wumpus") and _agentRemainingArrow > 0)
    {
        wumpus_room.set_truth_value("wumpus", false); // change the truth-value to "false"
        _wumpusIsAlive = false;                       // record that the wumpus is dead
        _agentRemainingArrow--;                       // decrement the _agentRemainingArrow

        return true;
    }

    // if there is no wumpus in the room
    else
    {
        _agentRemainingArrow--; // decrement the _agentRemainingArrow
        return false;
    }
}
