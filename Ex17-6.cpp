#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include "LinkedList.h"
#include "Pair.h"
#include "SparseArray.h"


std::vector<std::string> wordExtractor(const std::string& text)
{
	const std::string separators{ " ,;:.\"!?'\n" };       // Word delimiters
	std::vector<std::string> words;                       // Words found
	size_t start{ text.find_first_not_of(separators) };  // First word start index

	while (start != std::string::npos)                    // Find the words
	{
		size_t end{ text.find_first_of(separators, start + 1) }; // Find end of word
		if (end == std::string::npos)                        // Found a separator?
			end = text.length();                               // No, so set to end of text
		words.push_back(text.substr(start, end - start));    // Store the word
		start = text.find_first_not_of(separators, end + 1); // Find first character of next word
	}

	return words;
}

void storePoetry(SparseArray<List<std::string>>&array)
{
	std::string text = "O Attic shape! Fair attitude! with brede "
		"Of marble men and maidens overwrought, "
		"With forest branchesand the trodden weed; "
		"Thou, silent form, dost tease us out of thought "
		"As doth eternity : Cold Pastoral! "
		"When old age shall this generation waste, "
		"Thou shalt remain, in midst of other woe "
		"Than ours, a friend to man, to whom thou say'st, "
		"Beauty is truth, truth beauty,-that is all "
		"Ye know on earth, and all ye need to know. ";

	std::vector<std::string>storage = wordExtractor(text);
	std::vector<std::string>temp;// dummy vector for storing words with the same initial letter

	for (char alphabet = 'A'; alphabet <= 'z'; ++alphabet)
	{
			for (size_t i{}; i < storage.size();++i)
			{
				if (alphabet == storage[i][0])
				{
					temp.push_back(storage[i]);
				}
			}

			if (temp.size())
			{
				array[static_cast<size_t>(alphabet) - 65] = temp;//alphabet-65 is a an index counter
				temp.clear();// empty vector
			}
	}


	for (size_t i{}; i < 100; ++i)
	{
		if (!array[i].empty())
		{
			array[i].printList();
			std::cout << "\n";
		}
	}


}


int main()
{
	SparseArray<List<std::string>>array;
	storePoetry(array);

}

