//Names: Benjamin Webber and Joshua Byers
//
//Execution:
#include <algorithm>	//std::remove
#include <fstream>	//std::ifstream
#include <iostream>	//std::cout
#include <string>		//std::string
#include <vector>		//std::vector

using namespace std;

//bfs
//Provides BFS search for max flow.
std::vector<int> bfs(std::vector< std::vector<int> > edges) {
	//Begin BFS
	std::vector<int> bfs_queue;
	std::vector<bool> visitied(edges.size(), false);

	std::vector<int> distances(edges.size(), 5);
	std::vector<int> past(edges.size(), -1);

	std::vector<int> path;

	int loc;

	for (int i = 0; i < edges.size(); i++)
		bfs_queue.push_back(i);

	distances[0] = 0;

	while (!bfs_queue.empty()) {
		loc = bfs_queue[0];

		for (int i = 1; i < bfs_queue.size(); i++) {
			if (distances[i] < distances[loc])
				loc = bfs_queue[i];
		}

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

	loc = 9;
	while(loc != -1) {
		path.insert(path.begin(), loc);
		loc = past[loc];
	}

	path.erase(path.begin());
	path.erase(path.begin() + (path.size()-1));

	for (int i = 0; i < path.size(); i++)
		std::cout << path[i] << ' ';
	std::cout << std::endl;

	return path;
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

	return dice_edges;
}//bfs

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

	for (int k = 0; k < 2; /*(int)words.size();*/ k++) {

		//Populate edge vector
		edges = get_edges(dice, words[k]);

		//=================================================================
		//Begin setup of edges vector
		std::vector<int> source_buff;

		//Number of dice in use
		int dice_size = edges.size();

		//Set up source node to connect to all dice nodes
		for (int i = 0; i < dice_size; i++)
			source_buff.push_back(i+1);
		
		//Add source node
		edges.insert(edges.begin(), source_buff);

		//Add word nodes that will point to sink
		//NOTE: sink is 1 + dice_size + word_size
		for (int i = 0; i < words[k].size(); i++)
			edges.push_back(std::vector<int>(1, 1 + dice_size + words[k].size()));
		
		//Add sink node for posterity.
		edges.push_back(std::vector<int>());

		//End setup of edges vector
		//=================================================================

		//Call bfs on gathered edges.
		bfs(edges);

	}

	return 0;
}//main
