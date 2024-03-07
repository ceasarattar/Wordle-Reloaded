#include <iostream>         // For the input and output.
#include <fstream>          // For file input and output.
#include <vector>           // Input file is stored in a vector.
#include <cassert>          // For the assert statement used to validate file open.
#include <cctype>           // Allows using the tolower() function.
#include <ctime>            // Timer functions.
using namespace std;        // Provides a scope for the identifiers.

void startScreen()         // Displays the starting diplay screen and instructions.
  {
    cout << "Program 3: Wordle Reload" << endl << "CS 141, Spring 2022, UIC" << endl << endl 
         << "The objective of this game is to guess the randomly selected" << endl
         << "word within a given number of attempts. You can select either" << endl
         << "a three or five word board." << endl
         << "At the conlusion of the game, stats will be displayed." << endl
         << "Indicators will be given if characters of the user entered" << endl
         << "word are reflected in the guessed word." << endl
         << "  - If the character is in the correct position, the character" << endl
         << "    will display as an uppercase value." << endl
         << "  - If the character is within the random word, the character" << endl
         << "    will display as a lowercase value." << endl
         << "  - If you enter a character that is not in the word, an asterisk '*'" << endl
         << "    will display." << endl << endl << endl;
  }

void menuOptions(int &menuOption)                                 // Displays the menu options and asks 
  {                                                                 // for user input.
    cout << "Select a menu option:" << endl                         // cout statements that display the
         << "   1. To play Wordle Reload 3 letter play" << endl     // menu options.
         << "   2. To play Wordle Reload 5 letter play" << endl     // ................................
         << "   3. Exit the program" << endl                        // ................................
         << "Your choice --> ";                                     // ................................
    cin >> menuOption;                                              // asks for user input for the menu
    cout << endl;                                                   // options.
  }

void readWordsIntoDictionary(vector <string>& words3L, vector <string>&words5L)        // Read in dictionary into dictionary vector
  {
    ifstream inStream;                       // Declare an input stream for reading
    inStream.open("wordlewords.txt");        // Open dictionary file
    assert(inStream.fail() == false);        // Ensure file open worked
  
    words3L.clear();        // Clearing out the vector that holds all of the 3 letter words.
    words5L.clear();        // Clearing out the vector that holds all of the 3 letter words.

    string newWord;                         // Store a single input word
    while(inStream >> newWord)              // While there is another word to be read
      {
        if (newWord.length() == 3)          // Keep repeating while input from 
          {                                 // the file yields a word for the 
            words3L.push_back(newWord);     // 3 letter word vector
          }

        if (newWord.length() == 5)          // Keep repeating while input from
          {                                 // the file yields a word for the
            words5L.push_back(newWord);     // 5 letter word vector
          }
      }
    inStream.close();                       // Close the dictionary file
  }

int binarySearchString(string searchWord, vector< string> dictionary) // binary search, checks for word in dictionary
  {
    for (int i = 0; i < searchWord.length(); i++)       // loops from 0 to the length of the searchWord
      {
        searchWord.at(i) = tolower(searchWord.at(i));   // loops from 0 to the length of the searchWord
      }
    int mid;        // initializes the variable mid for binary search as an integer
    int low;        // initializes the variable low for binary search as an integer
    int high;       // initializes the variable high for binary search as an integer
    low = 0;
    high = dictionary.size() - 1;        // gets the size of dictionary - 1 (so the index numbers of dictionary)
    while (high >= low)                  // loops while the variable high is bigger than or equal to low
      {
        mid = (high + low) / 2;          // gets the middle value 
        int searchResult = searchWord.compare(dictionary[mid]);
        if (searchResult == 0) 
        {
          return mid;                  // returns the middle value using binary search
        }
        else if (searchResult < 0) 
        {
          high = mid - 1;              // returns the high value using binary search
        }
        else 
        {
          low = mid + 1;               // returns the low value using binary search
        }
      }
    return -1; // not found
}

void checkExist(string word, vector<string> dictionary)        // checks if the word is in the vector dictionary
  {
    int result = binarySearchString(word, dictionary);         // binary search that returns -1 if the word is not in the vector
    if (result == -1)
      {
        cout << "Not a playable word, please select another word." << endl;      // prints not a playable word
      }
  }

void displayBoard5L(string &currentAttempt, char char1, char char2, char char3, char char4, char char5)        // prints the display board
  {                                                                                                            // prints the display word 
    currentAttempt += "[";                                                     // this function uses a reference pass-by parameter and
    currentAttempt += char1;                                                   // multiple different parameters to avoid using 
    currentAttempt += "] ";                                                    // global variables
    currentAttempt += " [";                                                    // sets currentAttempts to different output for the board
    currentAttempt += char2;                                                   // sets currentAttempts to different output for the board
    currentAttempt += "] ";                                                    // sets currentAttempts to different output for the board
    currentAttempt += " [";                                                    // sets currentAttempts to different output for the board
    currentAttempt += char3;                                                   // sets currentAttempts to different output for the board
    currentAttempt += "] ";                                                    // sets currentAttempts to different output for the board
    currentAttempt += "[";                                                     // sets currentAttempts to different output for the board
    currentAttempt += char4;                                                   // sets currentAttempts to different output for the board
    currentAttempt += "] ";                                                    // sets currentAttempts to different output for the board
    currentAttempt += " [";                                                    // sets currentAttempts to different output for the board
    currentAttempt += char5;                                                   // sets currentAttempts to different output for the board
    currentAttempt += "] \n";                                                  // sets currentAttempts to different output for the board
    cout << currentAttempt;                                                    // sets currentAttempts to different output for the board
  }

void threeLetterGame(string randomWord1, int &tempStreak, int &userAttempts, int &winStreak, int &userWins, vector <string> words3L)
  {                                                             // function for the three letter game 
    string userInput;                                           // initializes the variable that stores the user input word
    string currentAttempt = "";                                 // used for re-printing each row after each consecutive try
    int turns = 0;
    cout << "To get started, enter your first 3 letter word." << endl
         << "You have 4 attempts to guess the random word." << endl
         << "The timer will start after your first word entry." << endl
         << "Try to guess the word within 20 seconds." << endl << endl;
    while (turns < 4)                                           // sets the turns to less than 4 for the three letter word (4 attempts)
      {
        char char1 = '*';                                       // initializes char1 as an astrisk
        char char2 = '*';                                       // initializes char2 as an astrisk
        char char3 = '*';                                       // initializes char3 as an astrisk
        cout << "Please enter word --> ";
        cin >> userInput;                                       // asks for the user's word as an input 
        cout<<endl;
        userAttempts++;                                         // increments userAttempts with each attempt

        if (userInput.size() != 3)                              // prints out an error message if the word is not 3 letters long for the 3 letter game
          {
            cout << "Invalid word entry - please enter a word that is 3 characters long." << endl << endl;
            continue;
          }
        else if (binarySearchString(userInput , words3L) == -1)              // prints out an error message if the word is not found in the vector 
          {                                                                  // using binary search
            cout << "\nNot a playable word, please select another word.\n";
          }
        else
          {         
            turns++;                            // increments for each attempt
            if (tolower(userInput[0]) == randomWord1[0]){          // the rest of this portion compares every element in the randomly generated
                char1 = toupper(userInput[0]);}                    // word to every element in the user entered word, and then either sets the
            else if (tolower(userInput[0]) == randomWord1[1]){     // indexed character to an astrisk if no match is found, lowercase if a match is
                char1 = tolower(userInput[0]);}                    // found in a different index, or upper case is a match is found in the same index
            else if (tolower(userInput[0]) == randomWord1[2]){
                char1 = tolower(userInput[0]);}

            if (tolower(userInput[1]) == randomWord1[1]){
                char2 = toupper(userInput[1]);}
            else if (tolower(userInput[1]) == randomWord1[0]){
                char2 = tolower(userInput[1]);}
            else if (tolower(userInput[1]) == randomWord1[2]){
                char2 = tolower(userInput[1]);}

            if (tolower(userInput[2]) == randomWord1[2]){
                char3 = toupper(userInput[2]);}
            else if (tolower(userInput[2]) == randomWord1[1]){
                char3 = tolower(userInput[2]);}
            else if (tolower(userInput[2]) == randomWord1[0]){
                char3 = tolower(userInput[2]);}
            
            currentAttempt += "[";                                // prints out the display board after running the if and else if statements 
            currentAttempt += char1;                              // sets currentAttempts to different output for the board
            currentAttempt += "]  [";                             // sets currentAttempts to different output for the board
            currentAttempt += char2;                              // sets currentAttempts to different output for the board
            currentAttempt += "]  [";                             // sets currentAttempts to different output for the board
            currentAttempt += char3;                              // sets currentAttempts to different output for the board
            currentAttempt += "] \n";                             // sets currentAttempts to different output for the board
            cout<<currentAttempt;
            
            if (toupper(userInput.at(0)) == toupper(randomWord1.at(0))       // checks if a complete match is found and increments a win!
                && toupper(userInput.at(1)) == toupper(randomWord1.at(1)) && toupper(userInput.at(2)) == toupper(randomWord1.at(2)))
              {
                userWins++;
                cout << "Nice Work!  You guessed the correct word" << endl;
                cout << "  - You completed the board in: " << 0 << " seconds." << endl;
                cout << "  - It took you " << turns << "/4 attempts." << endl;
                tempStreak++;                   // temp variable to hold the sreak
              
                if(tempStreak > winStreak)
                  {
                    winStreak++;
                  }
                break;
              }
            if (turns == 4)         // max attempts hits 4
              { 
                cout << "\nMaximum amount of attempts have been reached. Try again.\n";
                tempStreak = 0;
              }
          }  
      }
  }


void fiveLetterGame(string randomWord2, int &tempStreak, int &userAttempts, int &winStreak, int &userWins, vector <string> words5L)
  {                                                               // function to play the five letter game using a vector as a parameter 
    string userInput;                                           // and pass by references to avoid using global variables
    string currentAttempt = "";
    int turns = 0;
    cout << "To get started, enter your first 5 letter word." << endl
         << "You have 6 attempts to guess the random word." << endl
         << "The timer will start after your first word entry." << endl
         << "Try to guess the word within 40 seconds." << endl << endl;
    while (turns < 6)                              // checks if the tries are still valid for the five letter word
      {
        char char1 = '*';
        char char2 = '*';
        char char3 = '*';
        char char4 = '*';
        char char5 = '*';
        cout << "Please enter word --> ";
        cin >> userInput;
        cout<<endl;
        userAttempts++;               // increments userAttempts after the user inputs a word  
        
        if (userInput.size() != 5)          // prints an error message if the word size is not 5 for a five letter game 
          {
            cout << "Invalid word entry - please enter a word that is 5 characters long." << endl << endl;
            continue;
          }
        else if (binarySearchString(userInput , words5L) == -1)                  // checks if word is in 5-letter dictionary and prints an error
          {                                                                      // message if not
            cout << "\nNot a playable word, please select another word.\n";
          }
        else
        {

            turns++;

            if (tolower(userInput[0]) == tolower(randomWord2[0])){         // the rest of this portion compares every element in the randomly generated
                char1 = toupper(userInput[0]);}                           // word to every element in the user entered word, and then either sets the
            else if (tolower(userInput[0]) == tolower(randomWord2[1])){  // indexed character to an astrisk if no match is found, lowercase if a match is
                char1 = tolower(userInput[0]);}                         // found in a different index, or upper case is a match is found in the same index
            else if (tolower(userInput[0]) == tolower(randomWord2[2])){
                char1 = tolower(userInput[0]);}
            else if (tolower(userInput[0]) == tolower(randomWord2[3])){
                char1 = tolower(userInput[0]);}
            else if (tolower(userInput[0]) == tolower(randomWord2[4])){
                char1 = tolower(userInput[0]);}

            if (tolower(userInput[1]) == tolower(randomWord2[1])){
                char2 = toupper(userInput[1]);}
            else if (tolower(userInput[1]) == tolower(randomWord2[0])){
                char2 = tolower(userInput[1]);}
            else if (tolower(userInput[1]) == tolower(randomWord2[2])){
                char2 = tolower(userInput[1]);}
            else if (tolower(userInput[1]) == tolower(randomWord2[3])){
                char2 = tolower(userInput[1]);}
            else if (tolower(userInput[1]) == tolower(randomWord2[4])){
                char2 = tolower(userInput[1]);}

            if (tolower(userInput[2]) == tolower(randomWord2[2])){
                char3 = toupper(userInput[2]);}
            else if (tolower(userInput[2]) == tolower(randomWord2[1])){
                char3 = tolower(userInput[2]);}
            else if (tolower(userInput[2]) == tolower(randomWord2[0])){
                char3 = tolower(userInput[2]);}
            else if (tolower(userInput[2]) == tolower(randomWord2[3])){
                char3 = tolower(userInput[2]);}
            else if (tolower(userInput[2]) == tolower(randomWord2[4])){
                char3 = tolower(userInput[2]);}

            if (tolower(userInput[3]) == tolower(randomWord2[3])){
                char4 = toupper(userInput[3]);}
            else if (tolower(userInput[3]) == tolower(randomWord2[2])){
                char4 = tolower(userInput[3]);}
            else if (tolower(userInput[3]) == tolower(randomWord2[1])){
                char4 = tolower(userInput[3]);}
            else if (tolower(userInput[3]) == tolower(randomWord2[0])){
                char4 = tolower(userInput[3]);}
            else if (tolower(userInput[3]) == tolower(randomWord2[4])){
                char4 = tolower(userInput[3]);}

            if (tolower(userInput[4]) == tolower(randomWord2[4])){
                char5 = toupper(userInput[4]);}
            else if (tolower(userInput[4]) == tolower(randomWord2[3])){
                char5 = tolower(userInput[4]);}
            else if (tolower(userInput[4]) == tolower(randomWord2[2])){
                char5 = tolower(userInput[4]);}
            else if (tolower(userInput[4]) == tolower(randomWord2[1])){
                char5 = tolower(userInput[4]);}
            else if (tolower(userInput[4]) == tolower(randomWord2[0])){
                char5 = tolower(userInput[4]);}

            currentAttempt += "[";                                    // prints out the display board after running the if and else if statements 
            currentAttempt += char1;                                  // sets currentAttempts to different output for the board
            currentAttempt += "]  [";
            currentAttempt += char2;
            currentAttempt += "]  [";
            currentAttempt += char3;
            currentAttempt += "]  [";
            currentAttempt += char4;
            currentAttempt += "]  [";
            currentAttempt += char5;
            currentAttempt += "] \n";
            cout<<currentAttempt;
            if (toupper(userInput.at(0)) == toupper(randomWord2.at(0)) && toupper(userInput.at(1)) == toupper(randomWord2.at(1)) && toupper(userInput.at(2))== toupper(randomWord2.at(2))&& toupper(userInput.at(3))== toupper(randomWord2.at(3))&& toupper(userInput.at(4))== toupper(randomWord2.at(4)))
              {                                                            // checks if a complete match is found
                userWins++;
                cout << "Nice Work!  You guessed the correct word" << endl;
                cout << "  - You completed the board in: " << 0 << " seconds." << endl;
                cout << "  - It took you " << turns << "/6 attempts." << endl;
                tempStreak++;                   // increments the streak variable after a win
                if (tempStreak > winStreak)
                  {
                    winStreak++;
                  }
                break;
              }
            if(turns == 6)             // checks if max attempts hits 6
              {
                cout<<"\nMaximum amount of attempts have been reached. Try again.\n";
                tempStreak = 0;
              }
          }
      }
  }





int main()
  {
    srand(1);
    int userAttempts = 0;                                              // initializes userAttempts and sets it to 0 
    int userTime = 0;                                                 // initializes userTime and sets it to 0 
    int winStreak = 0;                                               // initializes winStreak and sets it to 0 
    int userWins = 0;                                               // initializes userWins and sets it to 0 
    startScreen();
    int counter = 0;                                              // initializes counter and sets it to 0 
    int tempStreak = 0;                                          // initializes tempStreak and sets it to 0 
    int menuOption;                                             // initializes menuOption 
    vector <string> words3L;
    vector <string> words5L;
    readWordsIntoDictionary(words3L, words5L);                     // calls the function that reads the words from the file to the vector
    while (true)
      {
        menuOptions(menuOption);               // displays the menu options
        if (menuOption == 1)                   // condition if the user wants to play a 3 letter game 
          {
            string randomWord1 = words3L.at((rand() % words3L.size()));                    // gets a random word using rand()
            threeLetterGame(randomWord1, tempStreak, userAttempts, winStreak, userWins, words3L);  // calls the three letter game 
            counter++;                                      
          }
        if (menuOption == 2)                   // condition if the user wants to play a 5 letter game 
          {
            string randomWord2 = words5L.at(rand() % words5L.size());                               // gets a random word using rand()
            fiveLetterGame(randomWord2, tempStreak, userAttempts, winStreak, userWins, words5L);    // calls the five letter game 
          }

        if (menuOption == 3)                  // condition if the user wants to exit the game
          {
            cout << "Overall Stats:" << endl
                 << "  - You guessed: " << userWins << endl
                 << "  - Your longest streak is: " << winStreak << endl;
            if (winStreak>0)
              {
                cout << "  - Average word completion time: " << userTime << endl;
              }
            else
              {
                cout << "  - Average word completion time: N/A " << endl;
              }

            cout<< "Exiting program" << endl;
            exit(0);
          }
      }
  }