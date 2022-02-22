/*

File: main.cpp
Author: Danyal Warraich
Class: CS 251
Project 2 - Personality Tests
Description: Personality Test app using main.cpp file. The purpose
of this file is to have the user interface that takes in set of questions
and set of answers to compute score of user based on questions the user
answered. And takes in the set of names and their scores to search the
best match with the user for each people file that user uses. And it 
displays the interaction of choices user can select.
Date: 02/03/2022

Creative Component: mine.people -> List of Songs that you must listen to right
now. And it is based on several factors and that is (Harmony, Melody, Rythm, 
Quality, Emotion).

*/

#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "driver.h"

using namespace std;

// This function also follows the same pattern as processValue().
// This function takes in a string s2 which has factors. And takes in integer
// i, so the loop starts after the question and space. In the loop j equals
// i as initiation. if s2[j] eqauls ' ' then it parses and extracts
// characters after : which is (i+1) till space ' ' (j-2) and stores in s3. and
// therefore, stoi is used to convert string into integer and stored in num
// integer variable. and then i = j which basically means that the loop in
// the process factors should start from that index. Other case is if index j
// reaches s2.size()-1 then characters from i+1 until the end are extracted
// and converted into num integer and returned.
int processValue2(string s2, size_t& i) {
    int num = 0;
    for (size_t j = i; j < s2.size(); j++) {
        if (s2[j] == ' ') {
            string s3 = s2.substr(i+1, j-2);
            // cout << s3 << endl;
            num = stoi(s3);
            // cout << s3 << endl;
            // cout << s3.size() << endl;
            i = j;
            return num;
        } else if (j == s2.size()-1) {
            string s3 = s2.substr(i+1);
            // cout << s3 << endl;
            num = stoi(s3);
            i = j;
            return num;
        }
    }
    return {};
}

// This function also follows the same pattern as processFactors().
// This function takes in two strings, s1 has questions, and s2 has scores.
// For loop is used to identify if a character in s2 is an alphabet, so it
// assigns key to that character. Otherwise if s2[i] equals to : then a helper
// function is called processValue2. After an integer value is returned, object
// q accesses scores map to associate key with value. And names is
// assigned with s1, and finally it returns that element after complete parsing.
Person processScores(string& s2, string& s1) {
    char key;
    int value = 0;
    Person p;
    for (size_t i = 0; i < s2.size(); i++) {
        if (isalpha(s2[i])) {
            key = s2[i];
        //    cout << key << endl;
        } else if (s2[i] == ':') {
            value = processValue2(s2, i);
          //  cout << value << endl;
            p.scores[key] = value;
        }
    }
    p.name = s1;
    return p;
}

// This function takes in a string from s.name which will parse name from
// scores. This function follows the same pattern as processData function().
// It extracts the names and scores in seperate strings. After loop ends, It
// calls processScores() function to parse scores data into a map.
Person processData2(string& nam) {
    Person p;
    string s1, s2;
    set<Person> people;
    for (size_t i = 0; i < nam.size(); i++) {
        if (nam[i] == '.') {  // extract question
            s1 = nam.substr(0, i);
            s2 = nam.substr(i+2, nam.size()-1);
            break;
        }
    }
    p = processScores(s2, s1);
    return p;
}

// This function takes three parameters, set container which contains the
// all the lines of elements seperately. And it takes a map that will store
// the userScores. For loop loops through set of type Person. It calls the
// processData2 function to parse the data in s.name for each set element.
void processNames(set<Person>& names, map<char, int> &userScores) {
    Person P;
    set<Person> people;
    for (auto s : names) {
      P = processData2(s.name);
      people.insert(P);
    }
    // for (auto p : people) { cout << p.name << endl; }
    P = mostSimilarTo(userScores, people);
    cout << "You got " << P.name << "!" << endl << endl;
    P.scores.clear();
    P.name.clear();
    people.clear();
    names.clear();
}

// This function follows the same pattern as fileReading for Question
// but the difference is it takes in set of Person struct and name of
// the file. It reads the file line by line and Object p of type Person
// access the name from Person struct and lines is assigned to it. then
// this p.name which includes the name and scores of string is inserted
// in the set.
void fileReading2(set<Person>& names, string& filename) {
    ifstream inFile;
    string lines;
    inFile.open(filename);
    while (!inFile.eof()) {
        Person p;
        getline(inFile, lines);
        if (!inFile.fail()) {
            p.name = lines;
            names.insert(p);
        }
    }
    inFile.close();
}

// This function takes in a vector of string container. It prints The
// the files that the user can check its matches with other people.
// It basically returns the file name and concatenates .people To
// make it easier to open the file in the next function.
string display2(vector<string>& vec) {
    int i = 1;
    int userVal = 0;
    for (auto v : vec) {
        cout << i << ". " << v << endl;
        i++;
    }
    i = 0;
    cout << i << ". " << "To end program.\n\n";
    cout << "Choose test number (1-9, or 0 to end): ";
    cin >> userVal;
    if (userVal == 0) {
        string s = "To end program.";
        return s;
    }
    i = 1;
    for (auto v : vec) {
        if (userVal == i) {
            v = v + ".people";
            return v;
        }
        i++;
    }
    return {};
}

// This function has a parameter of vector conatiner of type string, and is
// passed by reference. The purpose is to store the names of the .people file
// so it can be used later to open these files and have users match with them.
void storeFileNames(vector<string>& vec) {
    vec.push_back("BabyAnimals");
    vec.push_back("Brooklyn99");
    vec.push_back("Disney");
    vec.push_back("Hogwarts");
    vec.push_back("MyersBriggs");
    vec.push_back("SesameStreet");
    vec.push_back("StarWars");
    vec.push_back("Vegetables");
    vec.push_back("mine");
}

// This function takes in object Q of type Question struct. The purpose of
// this function is to display the choices for users (1-5). It prints the
// questionText using Q to access it and asks user to pick an option. Hence,
// it returns an int type value entered by user.
int display(Question Q) {
    int userVal = 0;
    cout << "How much do you agree with this statement?\n";
    const string quote = "\"";
    cout << quote << Q.questionText << quote << endl << endl;
    cout << "1. Strongly disagree\n";
    cout << "2. Disagree\n";
    cout << "3. Neutral\n";
    cout << "4. Agree\n";
    cout << "5. Strongly agree\n\n";
    cout << "Enter your answer here (1-5): ";
    cin >> userVal;
    cout << endl;
    return userVal;
}

// This function takes in a string s2 which has factors. And takes in integer
// i, so the loop starts after the question and space. In the loop j equals
// i as initiation. If s2[j] eqauls space then it parses and extracts
// characters after : which is (i+1) till space ' ' (j-2) and stores in s3. and
// therefore, stoi is used to convert string into integer and stored in num
// integer variable. and then i = j which basically means that the loop in
// the process factors should start from that index. Other case is if index j
// reaches s2.size()-1 then characters from i+1 until the end are extracted
// and converted into num integer and returned.
int processValue(string s2, size_t& i) {
    int num = 0;
    for (size_t j = i; j < s2.size(); j++) {
        if (s2[j] == ' ') {
            string s3 = s2.substr(i+1, j-2);
            // cout << s3 << endl;
            num = stoi(s3);
            // cout << s3 << endl;
            // cout << s3.size() << endl;
            i = j;
            return num;
        } else if (j == s2.size()-1) {
            string s3 = s2.substr(i+1);
            // cout << s3 << endl;
            num = stoi(s3);
            i = j;
            return num;
        }
    }
    return {};
}

// This function takes in two strings, s1 has questions, and s2 has factors.
// For loop is used to identify if a character in s2 is an alphabet, so it
// assigns key to that character. Otherwise if s2[i] equals to : then a helper
// function is called processValue. After an integer value is returned, object
// q accesses factors map to associate key with value. And questionText is
// assigned with s1, and finally it returns that element after complete parsing.
Question processFactors(string& s2, string& s1) {
    char key;
    int value = 0;
    Question q;
    for (size_t i = 0; i < s2.size(); i++) {
        if (isalpha(s2[i])) {
            key = s2[i];
        //    cout << key << endl;
        } else if (s2[i] == ':') {
            value = processValue(s2, i);
          //  cout << value << endl;
            q.factors[key] = value;
        }
    }
    q.questionText = s1;
    return q;
}

// This function takes in a string called text which contains complete line
// from the set container, which has questions and factors in a string. This
// function returns Question element. For loop is used to extract question and
// factors seperately and then break the function. After that, processFactors()
// function is called which takes in string question and string factors.
Question processData(string& text) {
    Question q;
    string s1, s2;
    for (size_t i = 0; i < text.size(); i++) {
        if (text[i] == '.') {  // extract question
            s1 = text.substr(0, i+1);  // parses out question
            s2 = text.substr(i+2, text.size()-1);  // parses it out factors
            // cout << s2.size() << endl;
            // cout << s1 << endl;
            // cout << s2 << endl;
            break;
        }
    }
    q = processFactors(s2, s1);
    return q;
}

// This function takes parameters of set type Question struct and type int
// number which signifies the number of questions user is willing to answer.
// This function returns a map that assigns scores associated with char keys.
// While loop over here loops until i equals the number of questions user asked.
// Within this loop, randomQuestionFrom() function is called which takes in set
// of questions returns Question type object, which contains a random element of
// question. Now, processData() function is called which takes a string which
// needs to be parsed into seperate storage, one for question other for factors.
// And it returns that element of type question. display() function is called.
// Then scoresFrom() function is called to update the scores. And it returns
// map of those scores which can be accessed through factors map in Question.
map<char, int> processQuestions(set<Question> questions, int number) {
    map<Question, int> answers;
    map<char, int> expected;
    string text;
    int userVal = 0, i = 0;
    Question Q;
    while (i != number) {  // loop until user input number
    Q = randomQuestionFrom(questions);
    text = Q.questionText;
    // cout << Q.questionText << endl
    Q = processData(text);  // Parsing question and factors
    userVal = display(Q);  // returns user's choice (1-5)
    answers[Q] = userVal;  // assigns user's value to answers map
    expected = scoresFrom(answers);
    i++;
    }
    return expected;
}

// This function takes in a set container as parameter passed by reference, of
// Question type. This struct question has string which assigns question text
// and a map of factors of type char and int. This function reads the file, it
// opens the question.txt file and while loop is used to access the contents of
// the file. Within while loop an object q of Question type is created, so when
// the file is read, that line is assigned to question Text in the in struct.
// And that object is inserted in the set of questions.
void fileReading(set<Question>& questions) {
    ifstream inFile;
    string nums, temp, lines;
    inFile.open("questions.txt");
    while (!inFile.eof()) {
        Question q;  // created within while loop so new object is created
        getline(inFile, lines);
        if (!inFile.fail()) {
            q.questionText = lines;  // assigns whole line
            questions.insert(q);  // insert each object seperately in a set
        }
    }
    inFile.close();
}

// This main function includes all the essential variables and set and
// map containers that are used in almost all the functions. The main
// purpose is to call the functions in accordance to requirement of
// personality quiz and effectively open files, and primarily act
// as the user interface and user friendly.
int main() {
    int number = 0;
    set<Question> questions;
    set<Person> names;
    map<char, int> userScores;
    vector<string> vec;
    Person p;
    string filename;
    cout << "Welcome to the Personality Quiz!\n\n";
    cout << "Choose number of questions: ";
    cin >> number;
    cout << endl;
    fileReading(questions);  // updated scores returned in next func
    userScores = processQuestions(questions, number);
    storeFileNames(vec);
    filename = display2(vec);
    while (filename != "To end program.") {
    fileReading2(names, filename);
    processNames(names, userScores);
    filename = display2(vec);
    }
    cout << "Goodbye!" << endl;
    return 0;
}
