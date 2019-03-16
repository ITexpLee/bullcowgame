/* This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

// Unreal Engine friendly stuff
// using FText = std::string
// using FString = std::string

#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "FBullCowGame.h"
#include "FFileManagment.h"

void PrintIntro();
void PlayGame();
void PrintGameSummery();
bool AskToPlayAgain();
std::string GetValidGuess();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays
FFileManagment BCFileManagment; // deals with reading words from file and creating base file

int main()
{

	bool bPlayAgain = false;

	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	system("pause");
}

void PrintIntro()
{	
	std::cout << "Welcome to Bull and Cows, a fun word game\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n\n";
	return;
}

// plays a single game to completion
void PlayGame()
{
	int MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){

		std::string Guess = GetValidGuess(); 
		// Submit valid guess to the game and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";

	}

	PrintGameSummery();
	return;
}

// loop continually until the user gives a valid guess
std::string GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	std::string Guess = "";
	do {
		int CurrentTry = BCGame.GetCurrentTry();
		// get a guess from the player
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". enter your guess : ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Legth:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram, an isogram is a word with no repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use only lowercase letters in your word.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}

	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n?) ";
	std::string Response = "";
	std::getline(std::cin, Response);

	if ((Response[0] == 'y') || (Response[0] == 'Y')) {
		BCGame.Reset();
		return true;
	}
	else {
		return false;
	}
}

void PrintGameSummery()
{
	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE! - YOU WIN!\n";
	}
	else {
		std::cout << "Better luck next time!\n";
	}
	return;
}
