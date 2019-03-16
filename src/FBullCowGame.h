/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/
#pragma once

#include <string>
#include <fstream>
#include "FFileManagment.h"

// two integers, initialized to zero
struct FBullCowCount
{
	int Bulls = 0;
	int Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status = 0, OK, Not_Isogram, Wrong_Legth, Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int GetMaxTries() const;
	int GetCurrentTry() const;
	int GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(std::string) const;
	
	void Reset(); // TODO make a more rich return value.

	FBullCowCount SubmitValidGuess(std::string);

	
private:
	// see constructor for initialization
	int MyCurrentTry;
	std::string WordFile;
	std::string MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(std::string) const;
	bool IsLowercase(std::string) const;

};