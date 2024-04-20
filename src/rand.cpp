#include <cstdlib>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "rand.h"
#include "randutils.hpp"

//----------------------------------------------------------------------------
// Output constants to color values:
#define C_CLEAR  "\033[2J\033[1;1H"
#define C_RESET  "\e[m"
#define C_GREEN  "\e[32m"
#define C_YELLOW "\e[33m"
#define C_CYAN   "\e[36m"
#define C_BLUE   "\e[34m"
#define C_RED    "\e[31m"
#define C_WHITE  "\e[37m"
#define C_BOLD   "\e[1m"
#define C_BWHITE "\e[47m"

extern "C" 
{
	#include "clipboard.h"
	//----------------------------------------------------------------------------
	// Random number generator that implements the randutils auto_seed_256 seed engine.
	// More information on the seed engine in https://www.pcg-random.org/posts/simple-portable-cpp-seed-entropy.html
	int random_nr(int min, int max) 
	{
		std::uniform_int_distribution dist{min, max};
		static std::mt19937           engine{randutils::auto_seed_256{}.base()};
		return dist(engine);
	}

	//----------------------------------------------------------------------------
	// Picks random words from the ud2 dictionary to output it into a string.
	// ud2.txt is a uniquely decodable list, based on Google Ngram data and Niceware v. 4.0 list made by sts10.
	int random_wordpicker(uint wordcount, char *separator)
	{
		std::vector<std::string> word;
		std::string password;
		std::string sep{*separator};
		std::string number = std::to_string(random_nr(0, 0xABC));
		std::ifstream file("dictionaries/ud2.txt");

		if (!file)
		{
			std::cerr << "Hipass couldn't open the file. Please try again or refer to the manpage.\n";
			return 1;
		}
		for (std::string s; file >> s; ) word.push_back(s);
		if (word.empty())
		{
			std::cerr << "Hipass could not read the word. Please try again or refer to the manpage.\n";
			return 1;
		}

		// Select words from the dictionary using the random_nr(min, max) function and append to string.
		for (uint i = 0; i < wordcount; i++)
		{
			password.append(word[random_nr(0, 0xABCDEF) % word.size()]);
			password.append(sep);
		}
		password.append(number);

		// This will output different colors for separators and words for better user visibility.
		for (long unsigned int i = 0; i < password.length(); i++)
		{
			if (password[i] == *separator)
				std::cout << C_RED << password[i] << C_RESET;
			else if (isdigit(password.at(i)))
				std::cout << C_CYAN << password[i] << C_RESET;
			else
				std::cout << C_WHITE << password[i];
		}

		std::cout << std::endl;
		copy_to_clipboard_prompt(password.c_str());
		std::cout << std::endl;
		return 0;
	}
}
