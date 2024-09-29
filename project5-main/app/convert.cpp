#include "convert.hpp"
#include <string>
#include <sstream>
#include <unordered_set>
#include <string>
#include "MyPriorityQueue.hpp"
#include <map>
#include <iostream>

// You should not need to change this function.
void loadWordsIntoTable(std::unordered_set<std::string> & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}

}



// You probably want to change this function.
std::vector< std::string > convert(const std::string & s1, const std::string & s2, const std::unordered_set<std::string> & words)
{
	std::vector< std::string > ret;
	int s1Length = s1.length();
	int s2Length = s2.length();
	if(s1Length != s2Length){
		return ret;
	}
	if(s1 == s2){
		return ret;
	}
	std::map<std::string, int> visited;
	MyPriorityQueue<Node<std::string>> wordQueue;
	std::map<std::string , std::string> bFromA;
	
	Node<std::string> s1Node(0, s1, s1, s2);
	wordQueue.insert(s1Node);
	visited.insert({s1, s1Node.getFromS1() + s1Node.getToS2()});
	Node<std::string> currentNode;
	Node<std::string> nextNode;
	std::string nextWord;
	Node<std::string> toDelete;

	int fromS1Num = 0;

	while(wordQueue.size() > 0){
		currentNode = wordQueue.min();
		//std::cout << "check: " << currentNode.getWord() << " (" << currentNode.getFromS1() << ", " << currentNode.getToS2() << ")" << std::endl;
		fromS1Num = (currentNode.getFromS1() + 1);
		toDelete = wordQueue.min();
		wordQueue.extractMin();
		
		for(int i = 0; i < s1Length; i++){
			nextWord = currentNode.getWord();
			for(int j = 0; j < 26; j++){
				nextWord[i] = ('a' + j);
				//std::cout << "check if " << nextWord << " is in the dictionary" << std::endl;
				if(words.find(nextWord) != words.end()){
					Node<std::string> nextNode(fromS1Num, nextWord, s1, s2);
				    if((visited.find(nextWord) == visited.end())){
						visited.insert({nextWord, nextNode.getFromS1() + nextNode.getToS2()});
						wordQueue.insert(nextNode);
						//std::cout << "add to queue: " << nextNode.getWord() << " (" << nextNode.getFromS1() << ", " << nextNode.getToS2() << ")" << std::endl;
						bFromA.insert({nextWord, currentNode.getWord()});
					}else if(visited[nextWord] > nextNode.getFromS1() + nextNode.getToS2()){
						visited.insert({nextWord, nextNode.getFromS1() + nextNode.getToS2()});
						wordQueue.insert(nextNode);
						//std::cout << "add to queue: " << nextNode.getWord() << " (" << nextNode.getFromS1() << ", " << nextNode.getToS2() << ")" << std::endl;
						auto it = bFromA.find(nextWord);
						bFromA.erase(it);
						bFromA.insert({nextWord, currentNode.getWord()});
					}
				}
				if(nextWord == s2 && (words.find(nextWord) != words.end())){
					ret.insert(ret.begin(), nextWord);
					//std::cout << "path: " << nextWord << std::endl;
					while(nextWord != s1){
						nextWord = bFromA[nextWord];
					//	std::cout << "path: " << nextWord << std::endl;
						ret.insert(ret.begin(), nextWord);
					}
					int size = wordQueue.size();
					while(size > 0){
					wordQueue.extractMin();
						size -= 1;
					}
					return ret;
				}
			}
		}
	}
	int size = wordQueue.size();
	while(size > 0){
		wordQueue.extractMin();
		size -= 1;
	}
	return ret;
}

/*

// You probably want to change this function.
std::vector< std::string > convert(const std::string & s1, const std::string & s2, const std::unordered_set<std::string> & words)
{
	std::vector< std::string > ret;
	int s1Length = s1.length();
	int s2Length = s2.length();
	if(s1Length != s2Length){
		return ret;
	}
	if(s1 == s2){
		return ret;
	}
	std::unordered_set<std::string> visited;
	MyPriorityQueue<Node<std::string>*> wordQueue;
	std::map<std::string , std::string> bFromA;
	
	Node<std::string>* s1Node = new Node<std::string>(0, s1, s1, s2);
	wordQueue.insert(s1Node);
	visited.insert(s1);
	Node<std::string>* currentNode;
	Node<std::string>* nextNode;
	std::string nextWord;
	Node<std::string>* toDelete;

	int fromS1Num = 0;

	while(wordQueue.size() > 0){
		currentNode = wordQueue.min();
		std::cout << "check: " << currentNode->getWord() << " (" << currentNode->getFromS1() << ", " << currentNode->toS2 << ")" << std::endl;
		fromS1Num = (currentNode->getFromS1() + 1);
		toDelete = wordQueue.min();
		wordQueue.extractMin();
		
		for(int i = 0; i < s1Length; i++){
			nextWord = currentNode->getWord();
			for(int j = 0; j < 26; j++){
				nextWord[i] = ('a' + j);
				if((words.find(nextWord) != words.end()) && (visited.find(nextWord) == visited.end())){
					nextNode = new Node<std::string>(fromS1Num, nextWord, s1, s2);
					visited.insert(nextWord);
					wordQueue.insert(nextNode);
					std::cout << "add to queue: " << nextNode->getWord() << " (" << nextNode->getFromS1() << ", " << nextNode->toS2 << ")" << std::endl;
					bFromA.insert({nextWord, currentNode->getWord()});
				}
				if(nextWord == s2 && (words.find(nextWord) != words.end())){
					ret.insert(ret.begin(), nextWord);
					while(nextWord != s1){
						nextWord = bFromA[nextWord];
						//std::cout << "path: " << nextWord << std::endl;
						ret.insert(ret.begin(), nextWord);
					}
					//delete s1Node;
					delete toDelete;
					int size = wordQueue.size();
					Node<std::string>* toDelete2;
					while(size > 0){
						toDelete2 = wordQueue.min();
						wordQueue.extractMin();
						delete toDelete2;
						size -= 1;
					}
					return ret;
				}
			}
		}
		delete toDelete;
	}
	Node<std::string>* toDelete3;
	delete s1Node;
	int size = wordQueue.size();
	while(size > 0){
		toDelete3 = wordQueue.min();
		wordQueue.extractMin();
		delete toDelete3;
		size -= 1;
	}
	return ret;
}

*/