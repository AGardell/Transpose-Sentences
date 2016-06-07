//Simple program that takes in one or multiple lines of text and reprints them transposed. Ie. rows become columns
//columns become rows.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <queue>

std::vector <std::queue<char>> lettersMapping;
std::queue <char> rows;

void clearQ(std::queue<char>& q) {
	std::queue<char> empty;
	std::swap(q, empty);
}

void Transpose(std::string& str, int& longestLine) {
//put the text into a stringstream in order to extract each character including white space.
	std::stringstream ss;
	char ch;
	int lineLength = 0;
	
	ss << str;

	while (ss >> std::noskipws >> ch) { //push each line into a new queue in the vector.
		rows.push(ch);
		lineLength++;
	}

	if (lineLength > longestLine) {
		//record the longest line, or biggest queue to know how many times to iterate through the vector.
		longestLine = lineLength;
	}
	//push back the queue into the vector, clear the queue for the next line fo text and clear and stringstream.
	lettersMapping.push_back(rows);
	clearQ(rows);
	ss.clear();

}

void printVector(std::vector<std::queue<char>>& lettersMapping, int& longestLine) {
	//iterate through the vector of queues and print the front of each queue and pop it off. Repeat based on the length
	//of the longest line of text. Print a space if that queue in the vector is empty.
	int i = 0;

	while (i < longestLine) {
		for (auto it = lettersMapping.begin(); it != lettersMapping.end(); ++it) {
			if ((*it).empty()) {
				std::cout << ' ';
			}
			else {
				std::cout << (*it).front();
				(*it).pop();
			}
		}
		std::cout << std::endl;
		++i;
	}
}

int main() {
	std::ifstream input;
	std::string str;
	int longestLine = 0;

	input.open("Text.txt"); //open the text file containing the text to be transposed.

	while (std::getline(input, str)) {
		Transpose(str, longestLine);
	}

	printVector(lettersMapping, longestLine);

	return 0;
}