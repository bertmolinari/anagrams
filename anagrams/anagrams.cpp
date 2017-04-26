// anagrams.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
#include <string>
#include <fstream>
#include <iterator>
#include <map>
#include <vector>
#include <ctime>

// hash map { sorted-letters -> { word1, word2, etc } }

void Quicksort(std::string& stringToSort, int low, int high);
int PartitionString(std::string& stringToPartition, int low, int high);

int main()
{
	std::map< std::string, std::vector<std::string> > mymap;

	
	// read word from file
	std::ifstream file("h:\\wordlist.txt");

	std::string str;

	std::clock_t start = std::clock();
	
	while (std::getline(file, str))
	{

		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
		std::string originalWord = str;

//		::printf("input: %s ", str.c_str());

		// sort letters (alphabetical)
		Quicksort(str, 0, str.length() - 1);
		//std::sort(str.begin(), str.end());
		mymap[str].push_back(originalWord);

//		::printf("--> %s\n ", str.c_str());
	}

	double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	::printf("algo ran in: %4.3f", duration);
	
#ifdef NONE
	// print out the anagrams!
	for (std::map <std::string, std::vector<std::string>>::iterator start = mymap.begin(); start != mymap.end(); start++)
	{
		if (start->second.size() > 1)
		{
			::printf("Anagrams found! They are: ");
			for (int i = 0; i < start->second.size(); ++i)
			{
				::printf("%s ", start->second[i].c_str());
			}

			::printf("\n");
		}
	}
#endif

	// add element to hash map
	return 0;
}


void Quicksort(std::string& stringToSort, int low, int high)
{
	if (low < high)
	{

		// pick the pivot, we'll use the element at the midway point of the string
		int pivotIndex = ::PartitionString(stringToSort, low, high);

		// sort the "lower" piece of the string
		::Quicksort(stringToSort, low, pivotIndex - 1);
		
		// sort the "upper" piece of the string
		::Quicksort(stringToSort, pivotIndex, high);
	}
}

int PartitionString(std::string& stringToPartition, int low, int high)
{
	char pivotLetter = stringToPartition[high];

	int i = low - 1;
	for (int j = low; j <= high - 1; ++j)
	{
		if (stringToPartition[j] <= pivotLetter)
		{
			i++;
			std::swap(stringToPartition[i], stringToPartition[j]);
			//char temp = stringToPartition[i];
			//stringToPartition[i] = stringToPartition[j];
			//stringToPartition[j] = temp;
		}
	}

	std::swap(stringToPartition[i + 1], stringToPartition[high]);
	//char temp = stringToPartition[i + 1];
	//stringToPartition[i + 1] = stringToPartition[high];
	//stringToPartition[high] = temp;

	return i + 1;
}