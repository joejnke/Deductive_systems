// Implementation of the universe of the game-*- C++ -*-

#ifndef WORLD_H_
#define WORLD_H_

#include "room.hpp"
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

typedef std::pair<int, int> roomIdType;

/**
* Data structure to represent a universe where all the game components will
* interact with one another. The basic facts and axioms by which the universe
* is governed, will be defined here. 
*/
class world
{
private:
    int _model;               // dummy variable to hold facts
    vector<vector<room>> _grid;         // grid of rooms.
    roomIdType _agentRoomId;  // agent's current location.
                              // (-1, -1) if agent is dead
    bool _agentIsAlive;       // life status of the agent (MIGHT BE REDUNDANT)
    int _agentRemainingArrow; // remaining arrows the agent have
    bool _agentFoundGold;     // whether or not the agent has the gold
    roomIdType _wumpusRoomId; // wumpus' current location
                              // (-1, -1) if wumpus is dead
    bool _wumpusIsAlive;      // life status of the wumpus (MIGHT BE REDUNDANT)

public:
    /// Default constructor initializing few attributes with default values
    /// and grid of 4X4 array of rooms.
    world();
    /**
        *  @brief Generate unique pair of integers to be used as room ID in a
        *         room grid of 4X4 excluding those IDs in @param
        *  @param forbiddenRoomIds set of integer pairs to be excluded when
        *         generating room ID to be used in the 4X4 room grid
        */
    roomIdType uniqueRandomRoomIdGenrator(std::set<roomIdType> forbiddenRoomIds);
    /**
        *  @brief Initialize the grid of rooms with wumpus, pit and other
        *         components at random rooms in the grid and set rooms' states
        *         acordingly.
        */
    void grid_init();
    /**
        *  @brief Getter of the _grid attribute.
        *  @return 2D vector of room objects.
        */
    vector<vector<room>> get_grid();
    /**
        *  @brief Getter of the _model attribute.
        *  @return int (to be changed later)
        */
    int get_model();
    /**
        *  @brief Getter of the room object at the given id.
        *  @param roomId id of the room of whose copy will be returned.
        *  @return room copy of the room object found at roomId in the _grid.
        * 
        *  Find and return copy of the room object found at roomId in the _grid
        *  attribute. This will expose all the internal states of the knowledge
        *  contained in the room. It assumes that this method is invoked by the
        *  agent being inside the room at roomId. It will also update current
        *  room and life status of the agent.
        */
    room get_room(roomIdType roomId);
    /**
        *  @brief Getter of the _agentRoomId attribute.
        *  @return roomIdType
        */
    roomIdType get_agentRoomId();
    /**
        *  @brief Getter of the _agentRemainingArrow attribute.
        *  @return int
        */
    int get_agentRemainingArrow();
    /**
        *  @brief Getter of the _agentIsAlive attribute.
        *  @return bool
        */
    bool isAgentAlive();
    /**
        *  @brief Getter of the _agentFoundGold attribute.
        *  @return bool
        */
    bool doesAgentFoundGold();
    /**
        *  @brief Getter of the _wumpusRoomId attribute.
        *  @return roomIdType
        */
    roomIdType get_wumpusRoomId();
    /**
        *  @brief Getter of the _wumpusIsAlive attribute.
        *  @return bool
        */
    bool isWumpusAlive();
    /**
        *  @brief Kill the wumpus if it is found in the given room_id and
        *  update  _agentRemainingArrow _wumpusRoomId _wumpusIsAlive attributes
        *  accordingly. 
        * 
        *  @return bool "true" if the wumpus is found and killed or "false" if
        *  the wumpus is not found in the given room.
        */
    bool kill_wumpus_at(roomIdType room_id);
};

#endif /*WORLD_H_*/
