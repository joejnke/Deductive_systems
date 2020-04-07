// Knowledge container implementation for a single wumpus world room -*- C++ -*-

#ifndef ROOM_H_
#define ROOM_H_

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>

/**
* Data structure to represent a single room that 
* contain all truth value based data associated 
* with a room.
* e.g.: pit, breeze, wumpus, stench, visited, gold
*/
class room
{
private:
    std::map<std::string, bool> knowledge; // truth values for knowledge contained in a room
    std::pair<int, int> room_id;          // room_id of the room. Assumes left-bottom corner as (x,y)=(1,1) and starting point.
public:
    /// Default constructor initializing the default_tv to -1 and all truth
    /// values to this deafult value
    room();
    /// Constructor initializing the default_tv to -1,
    /// room_id to input parameter and all truth values to this deafult value
    room(std::pair<int, int> room_id);
    /**
        *  @brief Getter of the room_id class attribute.
        *  @return pair<int, int>
        */
    std::pair<int, int> get_room_id();
    /**
        *  @brief Getter of the knowledge class attribute.
        *  @return map<std::string, bool> 
        */
    std::map<std::string, bool> get_knowledge();
    /**
        *  @brief Getter of the truth value associated with the given knowledge_term.
        *  @param knowledge_term String of the key of whose truth value is required. 
        *  @return Bool
        */
    bool get_truth_value(std::string knowledge_term);
    /**
        *  @brief Setter of the truth value associated with the given knowledge_term.
        *  @param knowledge_term String of the key of whose truth value is to be set. 
        *  @param tv Bool to set as truth value.
        * 
        *  Set the truth value of a knowledge term to the given truth value if the
        *  knowledge_term already exists, else it will create an entry in the
        *  knowledge attribute with knowledge_term as key and the tv as value.
        */
    void set_truth_value(std::string knowledge_term, bool tv);
    /**
        *  @brief Gets set of room_ids of valid neighbouring rooms.
        *  @return Set get_adjacents
        * 
        *  Find the room_id of all valid neighbouring rooms to the room and return
        *  a set of these room_ids.
        * 
        *  Invalid neighbours are those outside a 4X4 grid of rooms. (e.g.: (-1,2)) 
        */
    std::set<std::pair<int, int>> get_adjacents();
};

#endif /*ROOM_H_*/
