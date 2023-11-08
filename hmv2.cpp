#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <graphics.h>

#define MAX_WORD_LENGTH 100
#define MAX_GUESSES 6

using namespace std;

string capitalized(string lower)
{
    for (int i = 0; i < lower.length(); i++)
    {
        lower[i] = toupper(lower[i]);
    }
    return lower;
}

void convertToUnderscore(string &word, string &guessed)
{
    guessed = word;
    for (size_t i = 0; i < word.length(); i++)
    {
        if (word[i] != ' ')
            guessed[i] = '_';
    }
}

bool updateEnteredCharacter(char enteredCharacter[50], char ec, int &len)
{
    for (int i = 0; i < len; i++)
    {
        if (ec == enteredCharacter[i])
            return true;
    }
    enteredCharacter[len++] = ec;
    return false;
}

int displayEnteredCharacter(char enteredCharacter[50], int &lengthOfArray)
{
    char temp;
    cout << "Entered character: ";
    for (int i = 0; i < lengthOfArray; i++)
    {
        temp = toupper(enteredCharacter[i]);
        cout << temp << " ";
    }
    cout << endl;
}

void displayGuessedWord(const string &guessed, int hasWon = 0)
{
    string temp = capitalized(guessed);
    if (!hasWon)
        cout << "Guessed word: " << temp << endl;
    else
        cout << "Correct word: " << temp << endl;
}

void replace(const string &word, string &guessed, char ch, int &num_guesses, int &er, bool isMatched)
{
    bool found = false;
    for (size_t i = 0; i < word.length(); i++)
    {
        if (tolower(word[i]) == tolower(ch))
        { // Convert both characters to lowercase for case-insensitive comparison
            guessed[i] = ch;
            found = true;
        }
    }
    if (!found && !isMatched) // word ma check garya
        num_guesses++;

    er = num_guesses;
}

void draw(int er)
{
    switch (er)
    {
    case 1:
        // Draw head
        for (int i = -2; i < 3; i++)
            circle(400, 200, 50 + i);
        break;
    case 2:
        // Draw body
        for (int i = -2; i < 2; i++)
            line(400 + i, 250, 400 + i, 400);
        break;
    case 3:
        // Draw left arm
        for (int i = -2; i < 3; i++)
            line(400 + i, 275 + i, 350 + i, 325 + i);
        break;
    case 4:
        // Draw right arm
        for (int i = -2; i < 3; i++)
            line(400 - i, 275 + i, 450 - i, 325 + i);
        break;
    case 5:
        // Draw left leg
        for (int i = -2; i < 3; i++)
            line(400 + i, 400 + i, 350 + i, 500 + i);
        break;
    case 6:
        // Draw right leg
        for (int i = -2; i < 3; i++)
            line(400 - i, 400 + i, 450 - i, 500 + i);
        outtextxy(365, 80, "Game Over");
        break;
    }
}

void getWord(ifstream &file, string &word)
{
    srand(static_cast<unsigned>(time(NULL)));
    int number_of_countries = 194;
    int random_number = rand() % number_of_countries;
    for (int i = 0; i < random_number; i++)
    {
        getline(file, word);
    }
    transform(word.begin(), word.end(), word.begin(), ::tolower);
}

void displayStats(int gPlayed, int CDs)
{
    cout << "Total number of games played: " << gPlayed << endl;
    cout << "Total number of Chicken Dinner: " << CDs << endl
         << endl;
}

void displayHomeScreen()
{

    cout << "Press any key to continue.......";
    getchar();
}

bool mainGame(int &score)
{
    string word;
    string guessed;
    int num_guesses = 0, er = 0, lengthOfArray = 0;
    char enteredCharacter[50], ch;
    bool isMatched;

    ifstream countryListFile("countryList.txt");
    if (!countryListFile.is_open())
    {
        cout << "Error opening the file." << endl;
        return 1;
    }

    //	numberOfGamesPlayed++;
    getWord(countryListFile, word);
    convertToUnderscore(word, guessed);

    cout << "The country to guess has " << guessed.length() << " letters." << endl;

    initwindow(800, 600); // Initialize graphics window with width 800 and height 600

    while (true)
    {
        displayGuessedWord(guessed);
        if(strlen(enteredCharacter)!=0)
        	displayEnteredCharacter(enteredCharacter, lengthOfArray);
        cout << "Enter a character to guess: ";
        cin >> ch;        // Read character from console
        ch = tolower(ch); // Convert character to lowercase
        isMatched = updateEnteredCharacter(enteredCharacter, ch, lengthOfArray);
        replace(word, guessed, ch, num_guesses, er, isMatched);
        system("cls");
        draw(er);

        if (word == guessed)
        {
            cout << "Winner Winner Chicken Dinner!!!" << endl;
            displayEnteredCharacter(enteredCharacter, lengthOfArray);
            displayGuessedWord(guessed, 1);
            //	numberOfCDs++;
            score++;
            cout << "Win Streaks: " << score << endl;
            getch();
            system("cls");
            closegraph();
            return true;
        }

        if (er >= MAX_GUESSES)
        {
            displayGuessedWord(word); // Display the correct word
            cout << "Wrong!! You lost." << endl;
            displayEnteredCharacter(enteredCharacter, lengthOfArray);
            cout << "The correct word is: " << capitalized(word) << endl;
            cout << "Win Streaks: " << score << endl;
            getch();
            closegraph();
            return false;
        }
    }
    
}
int main()
{
	int score=0;
    while (true)
    {
        if (!mainGame(score)){
        
            break;
        }
    }

    return 0;
}
