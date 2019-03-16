/* The only purpose to this class is to manage the file creation / connection 
to the words.txt file and to provide the word from the file to the game.
This file can then used be ammended by the player to add new
words to the list of randomly selected isograms */

// NOTE: the randomly selected word is passed to the games "HIDDEN_WORD" as "PlayWord"
// Inspect FBullCowGame.h constructor for clarity

#pragma once

#include <iostream>
#include <fstream>
#include <string>

class FFileManagment
{
public:
	FFileManagment();

	std::string GetPlayWord() const;
	int RandomNumber() const;

	void WordInnitialize();

private:
	// see constructor for innitilization
	int RandomInteger;
	std::string WordFile;
	std::string PlayWord;

	// helper function to check if this is the first time the game has been run, if so, creates words.txt file
	bool IsWordFileCreated(std::string WordFile) const;

	// starter words are hard coded in for the first time someone plays
	std::string DefaultWords[8] = { "friend", "god", "christ", "savior", "love", "joy", "word", "life" };
	const size_t DefaultWordCount = sizeof(DefaultWords) / sizeof(DefaultWords[0]);
};

