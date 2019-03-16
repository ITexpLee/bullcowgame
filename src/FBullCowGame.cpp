#pragma once
#include <iostream>
#include <map>
#include "FBullCowGame.h"

// Unreal Engine fiendly stuff
// #define TMAP std::map

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }
int FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

int FBullCowGame::GetMaxTries() const 
{
	std::map<int, int> WordLenthToMaxTries{ { 3,5 },{ 4,7 },{ 5,10 },{ 6,15 },{ 7,20 } };
	return WordLenthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	FFileManagment FFilemanagment;
	FFilemanagment.WordInnitialize();
	const std::string HIDDEN_WORD = FFilemanagment.GetPlayWord();
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(std::string Guess) const
{

	if (!IsIsogram(Guess)) { // if the guess isnt an isogram
		return EGuessStatus::Not_Isogram; 
	}
	else if (Guess.length() != GetHiddenWordLength()) {// if the guess length is wrong
		return EGuessStatus::Wrong_Legth;
	}
	else if (!IsLowercase(Guess)) { // if the guess isnt all lowercase
		return EGuessStatus::Not_Lowercase;
	}
	else {
		return EGuessStatus::OK;
	}

}



// recieves a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(std::string Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int MHWchar = 0; MHWchar < WordLength; MHWchar++) {
		// compare letters against the guess
		for (int GChar = 0; GChar < WordLength; GChar++) {
			// if they match
			if (Guess[GChar] == MyHiddenWord[MHWchar]) {
				// if they are in the same place
				if (MHWchar == GChar) {
					BullCowCount.Bulls++; // increment bulls 
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(std::string Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	std::map<char, bool> LetterSeen; // setup our map

	for (char Letter : Word)	// for all letters of the word 
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) { // if the letter is in the map
			return false; // we do NOT have an Isogram
		}
		else {
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}
	return true; // for example in cases where \0 is entered
}

bool FBullCowGame::IsLowercase(std::string Word) const
{
	for (char Letter : Word)
	{
		if (!islower(Letter)) { // if uppercase is found
			return false;
		}
	}
	return true;
}


