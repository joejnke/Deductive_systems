
#ifndef world_H_
#define world_H_

#include <string>
#include <vector>
#include <cstdlib>
#include <bits/stdc++.h>
#include <set>
#include <ctime>
#include <cstdlib>
#include "room.hpp"
#include <utility>

using namespace std;

class world
{
private:
	int model; // until modle implementation done considerd it as integer
	pair<int, int> agent_room;
	pair<int, int> wumpus_room;
	pair<int, int> gold_room;
	room grid[5][5]; //2d array of rooms segementation fault happens if we use 4*4
public:
	//map to store agent status  current_room_id(pair of points ) ,living(0 or 1 ),  remaining_arrow(0 or 1), found_gold(0 or 1 as boolean)
	map<pair<int, int>, vector<int>> agent_status;
	//map to store wumpus status living(0 or 1 ), wumpus_room_id (pair of points )
	map<pair<int, int>, int> wumpus_status;
	//consutructor for world class
	world();
	//Initialize the grid with random knowledge set to the rooms.
	void grid_init();
	//since for now we consider model as int the method return int datatype
	int get_model();
	//return a copy of grid attribute
	auto get_grid();
	//return copy of the room object at the given room_id from the grid
	room get_room(pair<int, int> room_id);
	//return copy of agent_status
	map<pair<int, int>, vector<int>> get_agent_status();
	//or we can do  auto get_agent_status();

	//return copy of wumpus status
	map<pair<int, int>, int> get_wumpus_status();
	//kill wumpus if it found in the specified room id
	pair<int, int> get_wumpus_room();
	pair<int, int> get_agent_room();
	pair<int, int> get_gold_room();
	void put_pit(pair<int, int>);
	void put_gold(pair<int, int>);
	void put_wumpus(pair<int, int>);
	void kill_wumpus_at(pair<int, int> room_id);
};
#endif
