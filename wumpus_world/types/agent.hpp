// implementation of an intelligent agent that will play in the wumpus world -*- C++ -*-

#ifndef AGENT_H_
#define AGENT_H_

#include "room.hpp"
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

/**
* An object representing an intelligent player that moves around in an
* environment and make decisions on what to do and not to do. 
*
* Its aim is to get the price in the environment while escaping from 
* danger and obstacles.
* It will continiously move around in the world then deduce and fill in
* all the knowledge contained in the grid of the world in to it's own
* version of the grid until it finds the price.
*/
class agent
{
private:
    int model;                                           // copy of the world's model attribute.
    room grid[4][4];                                     // 4X4 grid of room objects.
    int remainingArrow;                                  // remaining number of arrows.
    std::pair<int, int> roomId;                          // current room id. (-1, -1) if agent is dead.
    std::string facingToward;                            // agent's face  direction. Deafult is "Right".
    bool foundGold;                                      // "true" if agent got the gold.
    std::pair<int, int> wumpusRoom;                      // room id of where the wumpus is in. (-1, -1) if wumpus is killed.
    std::vector<std::pair<int, int>> perception_history; // Holds all the percived information by the agent in a sequential order as a list of visited rooms.
    std::stack<std::pair<int, int>> okRooms;            // Stack of safe rooms to go to.

public:
    /// Default constructor initializing all the
    agent();
};

#endif /*AGENT_H_*/