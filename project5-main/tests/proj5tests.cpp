#include <vector>
#include "catch_amalgamated.hpp"
#include <fstream>
#include <unordered_set>
#include "MyPriorityQueue.hpp"
#include "convert.hpp"


namespace{

// The test cases are below these two functions.

bool isValidChange(const std::string &s1, const std::string &s2)
{
	if( s1.length() != s2.length() )
	{
		return false;
	}
	int count = 0;
	for (size_t i{0}; i < s1.length(); i++)
	{
		if( s1[i] != s2[i])
		{
			count++;
		}
	}
	return count == 1;
}

bool validConversion(const std::vector< std::string > &r, std::string s1, std::string s2,  std::istream & in)
{
	
	// read word list into std::set<std::string>

	std::set<std::string> words;
	std::string line, word;
	std::stringstream ss;

	if( r.size() == 0 )
	{
		return false; 
	}
	if( s1 == s2 and r.size() == 1 and r[0] == s1 )
	{
		return true;
	}
	if( r[0] != s1 or r[ r.size() - 1] != s2)
	{
		return false;
	}

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			//std::cout << "This is where you should add " << word << " into your WordSet." << std::endl;
			words.insert( word );
		}
	}


	for(size_t i{0}; i < r.size() - 1; i++)
	{
		if( words.count(r[i]) == 0 or  (! isValidChange(r[i], r[i+1]) ) )
		{
			return false;
		}
	}
	if( words.count(r[ r.size() -1 ] ) == 0 )
		return false;
	return true;
}


/*
TEST_CASE("SimpleTestBigHeap", "[NONRequiredHeap]")
{
	MyPriorityQueue<int> mpq;
	for(int i = 10000000; i > 1; i-=2){
		mpq.insert(i);
	}
	for(int i = 9999999; i >2; i-=2){
		mpq.insert(i);
	}
	REQUIRE(mpq.min() == 2);
	REQUIRE(mpq.size() == 9999999);
}*/


// As always, this is a STARTING POINT of TEST_CASE( cases
	// and is not an exhaustive set of TEST_CASE( cases.
	// You should be sure to TEST_CASE( EVERY function of 
	// your priority queue as well as the Lewis Carroll puzzle.

TEST_CASE("BigTestOfMin", "[NONRequiredHeap]")
{
	MyPriorityQueue<int> mpq;
	mpq.insert(5);
	mpq.insert(5);
	mpq.insert(5);
	mpq.insert(5);
	mpq.insert(4);
	mpq.insert(5);
	mpq.insert(5);
	mpq.insert(6);
	mpq.insert(3);
	REQUIRE(mpq.min() == 3);
	mpq.extractMin();
	REQUIRE(mpq.min() == 4);
	mpq.extractMin();
	REQUIRE(mpq.min() == 5);
	//REQUIRE(mpq.extractMin() == PriorityQueueEmptyException);
}

TEST_CASE("TryNodeQueue", "[NONRequiredHeap]"){
	MyPriorityQueue<Node<std::string>*> mpq;
	Node<std::string>* node = new Node<std::string>(1, "test", "test", "test");
	mpq.insert(node);
	mpq.extractMin();
	delete node;
	REQUIRE(mpq.size() == 0);
}



TEST_CASE("SimplePQCreation", "[RequiredHeap]")
{
	MyPriorityQueue<int> mpq;
	mpq.insert(3);
	REQUIRE(mpq.min() == 3);
}


TEST_CASE("SimpleTestOfMin", "[RequiredHeap]")
{
	MyPriorityQueue<int> mpq;
	mpq.insert(3);
	mpq.insert(5);
	REQUIRE(mpq.min() == 3);
}


TEST_CASE("SimpleTestOfMinUpdating", "[RequiredHeap]")
{
	MyPriorityQueue<int> mpq;
	mpq.insert(3);
	mpq.insert(2);
	REQUIRE(mpq.min() == 2);
}


TEST_CASE("AntToEat", "[RequiredConversion]")
{
	std::string WORD_ONE = "ant";
	std::string WORD_TWO = "eat";
	size_t CORRECT_LENGTH = 5;


	std::unordered_set<std::string> words;
	std::ifstream in("words.txt");
	loadWordsIntoTable(words, in);


 	std::vector< std::string > r = convert(WORD_ONE, WORD_TWO, words);

	std::ifstream in2("words.txt");

 	REQUIRE(r.size() == CORRECT_LENGTH);
 	REQUIRE(  validConversion(r, WORD_ONE, WORD_TWO, in2) );
}


// Additional sample tests for conversion
// these ARE NOT required in the sense 
// 	  that your project will be graded even
//    if one or more of these do not pass.
// However, failing to pass these might indicate 
//		you might not be happy with your grade, 
//		so I encourage you to pass them anyway :) 


TEST_CASE("HeadToTail", "[SampleConversionTests]")
{
	std::string WORD_ONE = "head";
	std::string WORD_TWO = "tail";
	size_t CORRECT_LENGTH = 6;


	std::unordered_set<std::string> words;
	std::ifstream in("words.txt");
	loadWordsIntoTable(words, in);


 	std::vector< std::string > r = convert(WORD_ONE, WORD_TWO, words);

	std::ifstream in2("words.txt");

 	REQUIRE(r.size() == CORRECT_LENGTH);
 	REQUIRE(  validConversion(r, WORD_ONE, WORD_TWO, in2) );
}


TEST_CASE("PuttersToHampers", "[SampleConversionTests]")
{
	std::string WORD_ONE = "putters";
	std::string WORD_TWO = "hampers";
	size_t CORRECT_LENGTH = 14;


	std::unordered_set<std::string> words;
	std::ifstream in("words.txt");
	loadWordsIntoTable(words, in);


 	std::vector< std::string > r = convert(WORD_ONE, WORD_TWO, words);

	std::ifstream in2("words.txt");

 	REQUIRE(r.size() == CORRECT_LENGTH);
 	REQUIRE(  validConversion(r, WORD_ONE, WORD_TWO, in2) );
}



TEST_CASE("BankingToBrewing", "[SampleConversionTests]")
{
	std::string WORD_ONE = "banking";
	std::string WORD_TWO = "brewing";
	size_t CORRECT_LENGTH = 15;


	std::unordered_set<std::string> words;
	std::ifstream in("words.txt");
	loadWordsIntoTable(words, in);


 	std::vector< std::string > r = convert(WORD_ONE, WORD_TWO, words);

	std::ifstream in2("words.txt");

 	REQUIRE(r.size() == CORRECT_LENGTH);
 	REQUIRE(  validConversion(r, WORD_ONE, WORD_TWO, in2) );
}






TEST_CASE("ChangesToGlasses", "[SampleConversionTests]")
{
	std::string WORD_ONE = "changes";
	std::string WORD_TWO = "glasses";
	size_t CORRECT_LENGTH = 48;


	std::unordered_set<std::string> words;
	std::ifstream in("words.txt");
	loadWordsIntoTable(words, in);


 	std::vector< std::string > r = convert(WORD_ONE, WORD_TWO, words);

	std::ifstream in2("words.txt");

 	REQUIRE(r.size() == CORRECT_LENGTH);
 	REQUIRE(  validConversion(r, WORD_ONE, WORD_TWO, in2) );
}


TEST_CASE("ChangesToSmashed", "[SampleConversionTests]")
{
	std::string WORD_ONE = "changes";
	std::string WORD_TWO = "smashed";
	size_t CORRECT_LENGTH = 48;


	std::unordered_set<std::string> words;
	std::ifstream in("words.txt");
	loadWordsIntoTable(words, in);


 	std::vector< std::string > r = convert(WORD_ONE, WORD_TWO, words);

	std::ifstream in2("words.txt");

 	REQUIRE(r.size() == CORRECT_LENGTH);
 	REQUIRE(  validConversion(r, WORD_ONE, WORD_TWO, in2) );
}



TEST_CASE("BoostedToClasses", "[SampleConversionTests]")
{
	std::string WORD_ONE = "boosted";
	std::string WORD_TWO = "classes";
	size_t CORRECT_LENGTH = 44;


	std::unordered_set<std::string> words;
	std::ifstream in("words.txt");
	loadWordsIntoTable(words, in);


 	std::vector< std::string > r = convert(WORD_ONE, WORD_TWO, words);

	std::ifstream in2("words.txt");

 	REQUIRE(r.size() == CORRECT_LENGTH);
 	REQUIRE(  validConversion(r, WORD_ONE, WORD_TWO, in2) );
}


}