//Names: Benjamin Webber and Joshua Byers
//
//Execution:
#include <algorithm>	//std::remove
#include <fstream>	//std::ifstream
#include <iostream>	//std::cout
#include <string>		//std::string
#include <vector>		//std::vector

#include "matrix.h"

//bfs
//Provides BFS search for max flow.
std::vector<int> bfs(std::vector< std::vector<int> > edges) {
	//Begin BFS
	std::vector<int> bfs_queue;
	std::vector<int> distances(edges.size(), 5);
	std::vector<int> past(edges.size(), -1);

	int loc;

	for (int i = 0; i < edges.size(); i++)
		bfs_queue.push_back(i);

	//Set distance to source as 0
	distances[0] = 0;

	//While there's still more nodes in the queue,
	while (!bfs_queue.empty()) {
		loc = bfs_queue[0];

		//Find the minimum distance node in the queue
		for (int i = 1; i < bfs_queue.size(); i++) {
			if (distances[i] < distances[loc])
				loc = bfs_queue[i];
		}

		//Delete the minimum distance node in the queue
		for(std::vector<int>::iterator it = bfs_queue.begin(); it != bfs_queue.end(); it++) {
			if(*it == loc) {
				bfs_queue.erase(it);
				break;
			}
		}

		//For all nodes adjacent to loc,
		for (int i = 0; i < edges[loc].size(); i++) {
			//Check if the distance is overall shorter by taking the current node
			//	to that node.
			if ((distances[loc] + 1) < distances[edges[loc][i]]) {
				distances[edges[loc][i]] = distances[loc] + 1;
				past[edges[loc][i]] = loc;
			}
		}//for (i < edges[loc].size())
	}//while (!bfs_queue.empty())

	//Return parentage vector.
	return past;
}

//get_edges
//Returns vector that has as many elements as the dice vector that contains the
//	indices for the connected letters of the given word.
std::vector< std::vector<int> > get_edges(std::vector<std::string> dice, std::string word) {
	std::vector< std::vector<int> > dice_edges;
	std::vector<int> dice_edges_buff;

	bool dice_letter_conn = false;

	//For all dice,
	// For all letters in word,
	//  For all letters in dice,
	for (int i = 0; i < (int)dice.size(); i++) {
		for (int j = 0; j < (int)word.size(); j++) {
			for (int k = 0; k < (int)dice[i].size(); k++) {
				//If connection between current current dice and word letter found,
				//	break to next letter.
				if (dice[i][k] == word[j]) {
					dice_letter_conn = true;
					break;	
				}
			}
			//If a connection between current dice and current letter has been found,
			//	add it to adjancency vector
			if (dice_letter_conn) {
				dice_edges_buff.push_back(j + 1 + dice.size());
				dice_letter_conn = false;
			}
		}
		dice_edges.push_back(dice_edges_buff);
		dice_edges_buff.clear();
	}

	//Creating the graph
	//=================================================================
	//Begin setup of edges vector
	std::vector<int> source_buff;

	//Number of dice in use
	int dice_size = dice_edges.size();

	//Set up source node to connect to all dice nodes
	for (int i = 0; i < dice_size; i++)
		source_buff.push_back(i+1);
	
	//Add source node
	dice_edges.insert(dice_edges.begin(), source_buff);

	//Add word nodes that will point to sink
	//NOTE: sink is 1 + dice_size + word_size
	for (int i = 0; i < word.size(); i++)
		dice_edges.push_back(std::vector<int>(1, 1 + dice_size + word.size()));
	
	//Add sink node for posterity.
	dice_edges.push_back(std::vector<int>());

	//End setup of edges vector
	//=================================================================

	for (int i = 0; i < dice_edges.size(); i++) {
		std::cout << "Node " << i << ": ";
		if (i == 0)
			std::cout << "SOURCE";
		else if (i == (dice_edges.size() - 1))
			std::cout << "SINK";
		else
			std::cout << word;
		std::cout << " Edges to ";
		for (int j = 0; j < dice_edges[i].size(); j++)
			std::cout << dice_edges[i][j] << ' ';
		std::cout << std::endl;
	}

	return dice_edges;
}//get_edges

//get_lines
//gets all lines of a given file(name) in the form of a vector
std::vector<std::string> get_lines(char* filename) {
	std::ifstream i_f(filename);
	std::string line_buff;
	std::vector<std::string> lines;

	//For all available lines in given file,
	//	push to lines vector.
	while (i_f >> line_buff)
		lines.push_back(line_buff);

	return lines;
}//get_lines

int main(int argc, char* argv[]) {
	std::vector<std::string> dice,
									 words;
	std::vector< std::vector<int> > edges;

	//Make sure program was called correctly!
	if (argc != 3) {
		std::cout << "Usage: " << argv[0] << " [Dice file] [Word file]\n";
		return 1;
	}

	//Get all dice and words and input in their reespective vectors.
	dice = get_lines(argv[1]);
	words = get_lines(argv[2]);

	for (int k = 0; k < (int)words.size(); k++) {

		//Populate edge vector
		edges = get_edges(dice, words[k]);

	}//for (k < words.size())

	return 0;
}//main
