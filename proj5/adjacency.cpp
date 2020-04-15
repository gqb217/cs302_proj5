#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

std::vector< std::vector<int> > get_edges(std::vector<std::string> dice, std::vector<std::string> words) {
	std::vector< std::vector<int> > dice_edges;
	std::vector<int> dice_word_edge_buff;

	bool dice_word_conn = false;

	//For all dice,						(i)
	// For all words,						(j)
	//	 For all letters in word j		(k)
	//	  For all letters in die i		(l)
	//
	//Dice is on the outermost level so the amount of edges added to the dice_edges
	// vector is the same as the number of dice.

	for (int i = 0; i < (int)dice.size(); i++) {
		for (int j = 0; j < (int)words.size(); j++) {
			for (int k = 0; k < (int)words[j].size(); k++) {
				for (int l = 0; l < (int)dice[i].size(); l++) {
					if (dice[i][l] == words[j][k]) {
						dice_word_conn = true;
						break;
					}
				}
				if (dice_word_conn) {
					dice_word_edge_buff.push_back(j);
					dice_word_conn = false;
					break;
				}
			}
		}
		dice_edges.push_back(dice_word_edge_buff);
		dice_word_edge_buff.clear();
	}

	return dice_edges;
}

std::vector<std::string> get_lines(char* filename) {
	std::ifstream i_f(filename);
	std::string line_buff;
	std::vector<std::string> lines;

	while (i_f >> line_buff)
		lines.push_back(line_buff);

	return lines;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> dice,
								  words;
	std::vector< std::vector<int> > dice_edges;

	if (argc != 3) {
		std::cout << "Usage: " << argv[0] << " [Dice file] [Word file]\n";
		return 1;
	}

	dice = get_lines(argv[1]);
	words = get_lines(argv[2]);

	std::cout << "Dice:" << std::endl;
	for (int i = 0; i < (int)dice.size(); i++)
		std::cout << '\t' << i << ' ' << dice[i] << std::endl;
	std::cout << "Words:" << std::endl;
	for (int i = 0; i < (int)words.size(); i++)
		std::cout << '\t' << i << ' ' << words[i] << std::endl;

	dice_edges = get_edges(dice, words);

	for (int i = 0; i < (int)dice_edges.size(); i++) {
		std::cout << "Dice " << i << " (" << dice[i] <<')' << std::endl;
		for (int j = 0; j < (int)dice_edges[i].size(); j++)
			std::cout << '\t' << dice_edges[i][j] << " (" << words[dice_edges[i][j]] << ')' << std::endl;
	}
}
