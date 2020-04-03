// implementation of an intelligent agent that will play in the wumpus world -*- C++ -*-

#ifndef AGENT_H_
#define AGENT_H_

#include "room.hpp"
#include "world.hpp"
#include <iostream>
#include <map>
#include <stack>
#include <string>
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
    std::stack<std::pair<int, int>> okRooms;             // Stack of safe rooms to go to.

public:
    /// Default constructor initializing all the attributes to their default values
    /// except for those to be obtained from the world.
    agent();
    /// Default constructor initializing all the attributes to their default values
    agent(world arena);
    /**
        *  @brief Getter of the agent's perception history.
        *  @return std::vector<std::pair<int, int>>
        */
    std::vector<std::pair<int, int>> get_perception_history();
    /**
        *  @brief Stench sensor
        *  @param room_id id of the room to sense from.
        *  @return bool
        * 
        *  Returns "stench" status of the room.
        */
    bool does_stench(std::pair<int, int> room_id);
    /**
        *  @brief Glitter sensor
        *  @param room_id id of the room to sense from.
        *  @return bool
        * 
        *  Returns "glitter" status of the room.
        */
    bool does_glitter(std::pair<int, int> room_id);
    /**
        *  @brief Bump sensor
        *  @param room_id id of the room to sense from.
        *  @return bool
        * 
        *  Checks if the given room_id is valid room and then 
        *  returns "true" if the room at the given room_id is
        *  valid, otherwise returns "false".
        */
    bool does_bump(std::pair<int, int> room_id);    
    /**
        *  @brief Breeze sensor
        *  @param room_id id of the room to sense from.
        *  @return bool
        * 
        *  Returns "breeze" status of the room.
        */
    bool has_breeze(std::pair<int, int> room_id);
    /**
        *  @brief Wumpus sensor
        *  @param room_id id of the room to sense from.
        *  @return bool
        * 
        *  Returns "wumpus" status of the room.
        */
    bool has_wumpus(std::pair<int, int> room_id);
    /**
        *  @brief Check if the room is safe
        *  @param room_id id of the room to sense from.
        *  @return bool
        * 
        *  Returns "true" if "wumpus" and "pit" states of
        *  the given room are set and their truth value
        *  is "false". Otherwise, if either their truth
        *  value is not set or they are set and have
        *  truth value of "true", it will returns "false".
        */    
    bool is_safe(std::pair<int, int> room_id);
    /**
        *  @brief Scream sensor
        *  @param room_id id of the room to sense from.
        *  @return bool
        * 
        *  Returns ```true``` if wumpus is dead by checking the
        *  record in the ```wumpus_status``` attribute.
        */
    bool heared_scream();
    /**
        *  @brief Determine and execute sequence of actions to move to a room
        *  @param room_id id of the room to go to.
        * 
        *  Determine and execute sequence of actions inorder to go to the given
        *  room and then update states of rooms visited during execution of
        *  actions and the status of the agent and the wumpus accordingly.
        */
    void go_to(std::pair<int, int> room_id);
    /**
        *  @brief Grab reward found in the room
        *  @param room_id id of the room to grab reward from.
        * 
        *  Grab reward, if there is any, kept in the given room.
        *  Then update status of the room located at the room_id
        *  and also the agents status of having the reward (gold).
        */
    void grab(std::pair<int, int> room_id);
        /**
        *  @brief Shot an arrow into the given room
        *  @param room_id id of the room to shoot at.
        * 
        *  Call the "world.kill_wumpus_at(room_id)" function and
        *  update the agents status and the wumpus status. If the 
        *  wumpus is found and killed at the room given by the
        *  room_id, then it will also update the states of the
        *  room the wumpus is in and the neighbouring rooms to the
        *  wumpus' room.
        */
    void shoot(std::pair<int, int> room_id);
    /**
        *  @brief Move the agent one step in the "facing_toward" direction
        * 
        *  Moves the agent one step in the direction of the
        *  agent as specified by the "facing_toward" attribute.
        *  It then updates the "roomId" attribute to the id of
        *  the room reached after moving one step.
        */
    void move_forward();
    /**
        *  @brief Rotate the agent one step in anti-clockwise direction.
        * 
        *  Change the "facing_toward" attribute of the agent to the
        *  next direction the agent will be facing toward when it
        *  rotates one step in anti-clockwise direction.
        */
    void turn_left();
    /**
        *  @brief Rotate the agent one step in clockwise direction.
        * 
        *  Change the "facing_toward" attribute of the agent to the
        *  next direction the agent will be facing toward when it
        *  rotates one step in clockwise direction.
        */
    void turn_right();
    /**
        *  @brief Send signal and notify the UI that the agent has made an action
        */
    void signal_to_UI();
    /**
        *  @brief Determine and execute action commands.
        *  
        *  Determine and execute action commands based on the current
        *  knowledge of the agent.
        */
    void rule_match();
    /**
        *  @brief Make deduction about unvisited neighbouring rooms.
        * 
        *  Use the "perception history", "model" and the "current room"
        *  of the agent to make deduction about the states of unvisited
        *  neighbouring rooms of the current room the agent is in.
        *  Finally it updates the knowledge in every unvisited neighbouring
        *  rooms accordingly.
        *  This will be done by iterating over every undetermined state of
        *  every unvisited neighbouring room.
        */    
    void program_evaluator();
    /**
        *  @brief Make the agent play in the world.
        * 
        *  Define and execute iterrative steps that the agent will follow in playing the game.
        */    
    void play();
};

#endif /*AGENT_H_*/