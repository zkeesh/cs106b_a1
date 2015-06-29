/*
 * File: hello.cpp
 * --------------------------
 * Name: Zach Keeshin
 * This file has the four programs for Assignment 1
 * for the CS 106B class.
 */

#include <iostream>
#include <fstream>
#include "console.h"
#include "random.h"
#include "tokenscanner.h"
using namespace std;

/*
This function converts the given string
to an int
*/
int stringToInt(string str){

    if(str.length() == 1){
        return str[0] - '0';
    }

    if(str[0] == '-' && str.length() == 2){
        return -1 * (str[1] - '0');
    }

    string first_part = str.substr(0, str.length() - 1);
    char last = str[str.length() - 1];

    int ones_place = last - '0';

    int rest = stringToInt(first_part);

    if(rest < 0){
        return rest * 10 - ones_place;
    }else{
        return rest * 10 + ones_place;
    }
}
/*
This function converts the given int
to a string
*/
string intToString(int n){
    int ones = n % 10;
    char ones_char;

    if(ones < 0){
        ones_char = char(-1 * ones + '0');
    }else{
        ones_char = char(ones + '0');
    }

    if(n < 10 && n >= 0){
        return string() + ones_char;
    }
    if(n > -10 && n < 0){
        return string("-") + ones_char;
    }
    return intToString(n/10) + ones_char;
}

/*
This function calculates the combination
of two numbers based on Pascal's Triangle
*/
int c(int n, int k){
    if(n <= 1 || k == 0 || k == n){
       return 1;
    }
    return c(n-1, k-1) + c(n-1, k);
}

/*
This function simulates flipping a coin
until 3 consecutive heads are flipped
*/
void countHeads(){
    int flip;
    int counter = 0;
    int totalHeads = 0;
    int totalTails = 0;
    int streak = 0;
    while(true){
        flip = randomInteger(0,1);
          counter++;
        if(flip == 0){
            cout << "heads: " << endl;
            totalHeads++;
            streak++;
            if(streak == 3){
                break;
            }
        }else{
            cout << "tails: " << endl;
            totalTails++;
            streak = 0;
        }
    }
    cout << "Total Heads: " << totalHeads << endl;
    cout << "Total Tails: " << totalTails << endl;
    cout << "Total Flips: " << counter << endl;
}

/*
This returns whether or not the given character
is a vowel.
*/
bool isVowel(char ch){
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'y';
}

/*
This function counts how many syllables are in the given
word.
*/
int countSyllables(string str){
    int numVowels = 0;
    for(int i = 0; i < str.length(); i++){
        if(isVowel(str[i])){
            //if there's a vowel before it
            if(isVowel(str[i-1])){
               continue;
            }
            //if its an e at the end
            if(i == str.length() - 1 && str[i] == 'e'){
                continue;
            }
            numVowels++;
        }
    }
    if(numVowels == 0){
        numVowels = 1;
    }
    return numVowels;
}


int main() {
    double numWords = 0;
    double numSentences = 0;
    double numSyllables = 0;

    /* Open the file for reading.  Note the use of .c_str() here. */
    ifstream input("test.txt");

    TokenScanner scanner(input);
    scanner.ignoreWhitespace();
    while(scanner.hasMoreTokens()) {
        string token = scanner.nextToken();
        //if token starts with a letter counts as a word
        if(scanner.isWordCharacter(token[0])){
            numWords++;
        }
        if(token == "." || token == "!" || token == "?"){
            numSentences++;
        }
        numSyllables += countSyllables(token);
    }
    if(numWords == 0 && numSentences == 0){
        numWords = 1;
        numSentences = 1;
    }
    cout << "Number of words: " << numWords << endl;
    cout << "Number of sentences: " << numSentences << endl;
    cout << "Number of syllables: " << numSyllables << endl;

    //Calculate Flesch-Kincaid Grade Level score
    const double const_0 = -15.59;
    const double const_1 = 0.39;
    const double const_2 = 11.8;
    double grade = const_0 + const_1 * (numWords/numSentences) + const_2 * (numSyllables/numWords);

    cout << "Flesch-Kincaid Grade Level: " << grade << endl;

//    countHeads();
//    cout << c(10,3) << endl;
//    cout << c(2,2) << endl;
//    cout << c(5,1) << endl;
//    cout << intToString(10) << endl;
//    cout << intToString(25) << endl;
//    cout << stringToInt("125") << endl;
//    cout << stringToInt("55") << endl;

    return 0;
}
