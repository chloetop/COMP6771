/*
 * File: WordLadder.cpp
 * --------------------
 * Name: Subramanya Vajiraya, z5081713
 * This file is the starter project for the word ladder problem on Assignment #1.
 */
#include <algorithm>
#include "lexicon.h"
#include <string.h>
#include <queue>
#include <vector>
#include <iostream>
#include <map> //easier to handle ladders as it can be mapped with integers
#define large_num 100000000 //to calculate minimum length of wordladder. Keeping the value as high as possible
#include <sys/time.h>

typedef std::map<std::string,int> integer_map;
typedef std::map<std::string,std::vector<std::string>> Graph;
typedef std::queue<std::string> string_queue;
typedef std::vector<std::vector<std::string>> vect_vect_str;
typedef std::vector<std::string> vect_str;

class WordLadder {
public:
	int min = large_num;
	vect_vect_str findLadders(std::string start, std::string end, Lexicon dict) {
		
		//src: http://www.cplusplus.com/reference/map/map/
		integer_map ladder;
		Graph graph; 
		string_queue q;
		ladder.insert(std::pair<std::string,int>(start,1));
		dict.add(end);
		q.push(start);

		//BFS to build the shortest paths graph
		while(!q.empty()){
			std::string word=q.front();
			q.pop();
			if (word==end){
				min=ladder[word];
				continue;
			}
			int dis=ladder[word]+1;
			// Invalid case. 
			if (dis>min) break;
			for (u_int i=0;i<word.size();i++){
				std::string temp=word;

				// start generating permutations and compare it against words from Lexicon DS. If words match, Keep them as a part of ladder, else discard.
				for (char c='a';c<='z';c++){
					temp[i]=c;

					// If permutation is not a word, Ignore!!!
					if (!dict.containsWord(temp)) continue;

					// Check to see if it is our target node. If so, insert it to ladder and insert map<string,vector<string>> to graph.
					if (ladder.find(temp)==ladder.end()){
						ladder.insert(std::pair<std::string,int>(temp,dis));
						q.push(temp);
						graph.insert(std::pair<std::string,vect_str>(temp,vect_str{word}));
						continue;
					}
					// If permutation is the target, skip the iteration.
					if (temp == end) break;
					if (ladder[temp]<dis) continue;
					else if (ladder[temp]==dis)
						graph[temp].push_back(word);
				}
			}
		}
		vect_vect_str result;
		vect_str block;
		if (graph.find(end)==graph.end()) return result;
		depthfirstsearch(end,min-1,result,block,graph);
		return result;
	}
	//DFS to follow shortest path graph generated by BFS and traverse through the graph. 
private:
	void depthfirstsearch(std::string end,int step,vect_vect_str &result, vect_str &block,Graph &map){
		if (step==0){
			block.push_back(end);
			result.push_back(std::vector<std::string>{block.rbegin(),block.rend()});
			block.pop_back();
			return;
		}
		block.push_back(end);
		for (std::string s:map[end])
			depthfirstsearch(s,step-1,result,block,map);
		block.pop_back();
	}
};
int main() {
	//Declaration for measuring time complexity
	struct timeval time;
	gettimeofday(&time, NULL);
	long totalTime = (time.tv_sec * 1000) + (time.tv_usec / 1000);

	//Initialisation
	WordLadder wl;
	int flag = 1;
	int start_flag = 1;
	Lexicon english("EnglishWords.dat");
	std::string start;
	std::string end;

	//Test cases. 
	//case 1:
	// std::string start = "gimlets";
	// std::string end = "treeing";

	//case 2:
	// std::string start = "skinked";
	// std::string end = "venters";

	//Input block
	while(1){
		std::cout<<"Enter start word (RETURN to quit): ";
		std::cin.getline(start);
		if(!start_flag){
			std::cin.ignore();
			std::cin.ignore();
			std::cin.ignore();
		}
		
		if (start == "") {
			std::cout<<"Exiting";
		    return 0;
		}
		start_flag = 0;
		std::cout<<"Enter destination word: ";
		std::cin>>end;
		if(start.length() != end.length()) return 0;
		vect_vect_str results = wl.findLadders(start,end,english);

		//Sorting results lexicographically
		// Borrowed from http://stackoverflow.com/questions/22155451/sorting-a-list-of-vectors-lexicographically-according-to-priorities
		std::sort(results.begin(),results.end()); 
		if(wl.min != 0) std::cout<<"Found ladder: ";
		else {
			std::cout<<"No ladder found.";
			gettimeofday(&time, NULL);
			totalTime = (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - totalTime);
			std::cout<<"Elasped time is "<<totalTime<<"ms"<<std::endl;
			return 0;
		}
		//printing results
		// Borrowed from http://stackoverflow.com/a/21715062/5536234
		for(auto const& string_vec : results){
			for( auto const& s : string_vec ){
				if(s==start && flag == 0){
					// Add new line char at the beginning of ladders except first ladder.
					std::cout<<std::endl;
				}
				flag = 0;
				std::cout << s;
				//To add space between words
				if(s!=end)std::cout<<" ";
			}
		}
		std::cout<<std::endl<<std::endl;
	}

	// Elapsed time measurement
	gettimeofday(&time, NULL);
	totalTime = (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - totalTime);
	std::cout<<"Elasped time is "<<totalTime<<"ms"<<std::endl;
	return 0;
}

