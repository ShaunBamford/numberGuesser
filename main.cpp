#include <iostream>
#include <random>
using namespace std;

int main()
{
	// RNG
	const int MIN = 1;
	int MAX = 10;

	random_device seed;
	mt19937 gen{ seed() };

	int userGuess;
	int countGuesses = 0;
	int startLives = 5;
	int lives = 0;
	int level = 0;
	vector<int> prevGuesses;
	do
	{
		lives += startLives;
		uniform_int_distribution<> dist {MIN, MAX};
		int numToGuess = dist(gen);

		do
		{
			cout << "Please input a number between " << MIN << " and " << MAX << endl;
			cout << "You have " << lives << " lives left" << endl;
			cout << "Your previous guesses are: ";

			for (int guess : prevGuesses)
				cout << guess << ", ";
			cout << endl;

			cin >> userGuess;

			if (find(prevGuesses.begin(), prevGuesses.end(), userGuess) != prevGuesses.end())
			{
				cout << "You already guessed this number...\n" << endl;
			}
			else if (userGuess < MIN || userGuess > MAX)
			{
				cout << "Your guess is out of range, try again.\n" << endl;
			}
			else
			{
				if (userGuess < numToGuess)
					cout << "Your guess it too small, aim higher!\n";
				else if (userGuess > numToGuess)
					cout << "Your guess is too big, aim lower!\n";
				prevGuesses.push_back(userGuess);
				sort(prevGuesses.begin(), prevGuesses.end());
			}

			if (userGuess != numToGuess)
			{
				lives--;
			}

			countGuesses++;
		} while (userGuess != numToGuess && lives > 0);

		if (userGuess == numToGuess)
		{
			cout << "Congrats! You guessed it! It took you " << countGuesses << " guesses!" << endl;
			MAX += 5;
			level++;
			
			if (level % 3 == 0)
				lives++;

			prevGuesses.clear();
		}
	} while (lives > 0);
	if (lives == 0)
	{
		cout << "womp womp you died" << endl;
	}
}
