
#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include <cstdlib>
#include <bits/stdc++.h>
#include <set>
#include <ctime>
#include<cstdlib>
#include "Room.h"
#include <utility>

using namespace std;

class World
{
public:
    int model; // until modle implementation done considerd it as integer
	vector<vector<Room>> grid; //2d array of rooms
	//map to store agent status living(0 or 1 ), current_room_id(pair of points ) , remaining_arrow(0 or 1), found_gold(0 or 1 as boolean)
	map<int, pair<int, int>, int, int> agent_status; 
	//map to store wumpus status living(0 or 1 ), wumpus_room_id (pair of points ) 
	map<int, pair<int, int >> wumpus_status;

	//consutructor for World class 
    World();
   //Initialize the grid with random knowledge set to the rooms.
 	void grid_init();
	//since for now we consider model as int the method return int datatype
	int get_model();
	//return a copy of grid attribute
	vector get_grid();
	//return copy of the room object at the given room_id from the grid
	Room get_room<pair room_id);
	//return copy of agent_status
	map<int, pair<int, int>, int, int> get_agent_status();
	//or we can do  auto get_agent_status();
	
	//return copy of wumpus status
	enum Element {WUMPUS, PIT, GOLD}
	map<int, pair<int, int> > get_wumpus_status();
	//kill wumpus if it found in the specified room id

	void kill_wumpus_at(pair<int, int> room_id);
};
#endif
