#ifndef __PROJ5_PRIORITY_QUEUE_HPP
#define __PROJ5_PRIORITY_QUEUE_HPP

#include "runtimeexcept.hpp"
#include <vector>
#include <iostream>
#include <cmath>

class PriorityQueueEmptyException : public RuntimeException 
{
public:
	PriorityQueueEmptyException(const std::string & err) : RuntimeException(err) {}
};


template<typename Object> class Node{
	public:
	int fromS1;
	int toS2;
	std::string word;
	
	Node(){
		fromS1 = 0;
		toS2 = 0;
	}

	Node(int fromS1Num, std::string string, std::string s1, std::string s2){
		fromS1 = fromS1Num;
		toS2 = 0;
		int length = string.length();
		for(int i = 0; i < length; i++){
			if(s2[i] != string[i]){
				toS2 += 1;
			}
		}
		word = string;
	}
	
	bool operator<(const Node& node2);
	bool operator>(const Node& node2);
	bool operator==(const Node& node2);
	bool operator!=(const Node& node2);

	int getFromS1(){
		return fromS1;
	}

	int getToS2(){
		return toS2;
	}

	std::string getWord(){
		return word;
	}
};


template<typename Object>
bool Node<Object>::operator < (const Node& node2){
	//int sum1 = (this->fromS1)+(this->toS2);
	//int sum2 = (node2->fromS1)+(node2->toS2);
	//return sum1<sum2;
	//if(((this->fromS1)+(this->toS2)) < ((node2->fromS1)+(node2->toS2))){
	//	return true;
	//}else{
	//	return false;
	//}

	if((fromS1 + toS2) < (node2.fromS1 + node2.toS2)){
		return true;
	}else{
		return false;
	}
}

template<typename Object>
bool Node<Object>::operator > (const Node& node2){
	
	if((fromS1 + toS2) > (node2.fromS1 + node2.toS2)){
		return true;
	}else{
		return false;
	}
}

template<typename Object>
bool Node<Object>::operator == (const Node& node2){
	if((fromS1 + toS2) == (node2.fromS1 + node2.toS2)){
		return true;
	}else{
		return false;
	}

}

template<typename Object>
bool Node<Object>::operator != (const Node& node2){
	if((fromS1 + toS2) != (node2.fromS1 + node2.toS2)){
		return true;
	}else{
		return false;
	}
}

template<typename Object>
class MyPriorityQueue
{
private:
	// fill in private member data here
	std::vector<Object> heapArray;

public:

	// You also need a constructor and a destructor.

	MyPriorityQueue();
	~MyPriorityQueue();

 	size_t size() const noexcept;
	bool isEmpty() const noexcept;

	void insert(const Object & elem);


	// Note:  no non-const version of this one.  This is on purpose because
	// the interior contents should not be able to be modified due to the
	// heap property.  This isn't true of all priority queues but 
	// for this project, we will do this.
	// min and extractMin should throw PriorityQueueEmptyException if the queue is empty.
	const Object & min() const; 

	void extractMin(); 

};

template<typename Object>
MyPriorityQueue<Object>::MyPriorityQueue()
{
	
}


template<typename Object>
MyPriorityQueue<Object>::~MyPriorityQueue()
{
	int size = heapArray.size();
	while(size > 0){
		heapArray.pop_back();
		size -= 1;
	}
}


template<typename Object>
size_t MyPriorityQueue<Object>::size() const noexcept
{
	return heapArray.size();
}



template<typename Object>
bool MyPriorityQueue<Object>::isEmpty() const noexcept
{
	if(heapArray.size() == 0){
		return true;
	}else{
		return false;
	}
}

template<typename Object>
void MyPriorityQueue<Object>::insert(const Object & elem) 
{
	int index = heapArray.size();
	//std::cout << "insert \"" << elem.getWord() << "\", (" << elem.getFromS1() << " + " << elem.getToS2() << ") to index " << index << std::endl;
	heapArray.push_back(elem);
	Object temp;
	while(index > 0){
		//std::cout << "compare " << heapArray[index].getWord()  << " " << index << ": ("<< heapArray[index].getFromS1() << " + " << heapArray[index].getToS2() << ") and parent " << heapArray[floor((index-1)/2)].getWord() << " "<< floor((index-1)/2) << ": ("<< heapArray[floor((index-1)/2)].getFromS1() << " + " << heapArray[floor((index-1)/2)].getToS2()  << ")" <<std::endl;
		//std::cout << "compare " << heapArray[index] << " and " << heapArray[floor((index-1)/2)] << std::endl;
		if(heapArray[index] < heapArray[floor((index-1)/2)]){
			//std::cout << "swap \"" << heapArray[index].getWord() << "\" and \"" << heapArray[floor((index-1)/2)].getWord() << "\"" <<  std::endl;
			temp = heapArray[index];
			heapArray[index] = heapArray[floor((index-1)/2)];
			heapArray[floor((index-1)/2)] = temp;
			index = floor((index-1)/2);
		}else{
			return;
		}
	}
}




template<typename Object>
const Object & MyPriorityQueue<Object>::min() const
{
	int size = heapArray.size();
	if(size == 0){
		throw PriorityQueueEmptyException("Could not find min. Queue was empty.");
	}else{
		const Object & returnObject = heapArray[0];
		return returnObject;
	}
}   



template<typename Object>
void MyPriorityQueue<Object>::extractMin() 
{
	int index = heapArray.size();
	if(index == 0){
		throw PriorityQueueEmptyException("Could not extract min. Queue was empty.");
	}
	Object temp;
	temp = heapArray[0];
	heapArray[0] = heapArray[index-1];
	heapArray[index-1] = temp;
	heapArray.pop_back();
	index = 0;
	int childIndex = 1;
	int arraySize = heapArray.size();
	while(childIndex < arraySize){
		Object min = heapArray[index];
		int minIndex = index;
		if(heapArray[childIndex] < min){
			min = heapArray[childIndex];
			minIndex = childIndex;
		}
		if(childIndex+1 < arraySize){
			if(heapArray[childIndex+1] < min){
				min = heapArray[childIndex+1];
				minIndex = childIndex+1;
			}
		}

		if(minIndex == index){
			return;
		}else{
			//std::cout << "swap \"" << heapArray[index].getWord() << "\" and \"" << heapArray[minIndex].getWord() << "\"" <<  std::endl;

			temp = heapArray[index];
			heapArray[index] = heapArray[minIndex];
			heapArray[minIndex] = temp;
			index = minIndex;
			childIndex = 2*index + 1;
		}

	}
}


#endif 
