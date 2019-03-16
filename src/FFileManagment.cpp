#include "FFileManagment.h"
#include <time.h>

std::string FFileManagment::GetPlayWord() const { return PlayWord; }

FFileManagment::FFileManagment()
{
	RandomInteger = 0;
	const std::string WORD_FILE = "words.txt";
	WordFile = WORD_FILE;
	PlayWord = "";
}

// Checks if words.txt exists, if not, creates it, if so selects a word from it.
void FFileManagment::WordInnitialize()
{
	if (!IsWordFileCreated(WordFile)) {

		std::ofstream WriteWordFile(WordFile);
		for (unsigned int i = 0; i < DefaultWordCount; i++) {
			WriteWordFile << DefaultWords[i] << std::endl;
		}

		PlayWord = DefaultWords[1]; // will only be used as the word the first time game is played
		WriteWordFile.close();

	}
	else {

		int count = 1;
		int rand_number = RandomNumber();
		std::string word = "";

		std::ifstream ReadWordFile(WordFile);

		do {

			if (count == rand_number) {
				ReadWordFile >> PlayWord;
				break;
			}
			count++;

		} while (ReadWordFile >> word);

		ReadWordFile.close();

		// Uncomment to see the word and location of the word in the Words.txt file
		// std::cout << "the word number is " << count << std::endl;
		// std::cout << "the playword is " << PlayWord << std::endl;
	}

	return;
}

int FFileManagment::RandomNumber() const
{
	int count = 0;
	std::string word = "";

	std::ifstream ReadWordFile(WordFile);
	while (ReadWordFile >> word) {
		count++;
	}

	srand((unsigned)time(0));
	int random_integer;
	int lowest = 0, highest = count - 1;
	int range = (highest - lowest) + 1;

	for (int index = 0; index < count; index++) {
	random_integer = lowest + int(range*rand() / (RAND_MAX + 1.0));
	}

	ReadWordFile.close();
	return random_integer;
}

bool FFileManagment::IsWordFileCreated(std::string WordFile) const
{
	struct stat buf;
	return (stat(WordFile.c_str(), &buf) == 0); // will return true if file exists
}
