/*

File: driver.h
Author: Danyal Warraich
Class: CS 251
Project 2 - Personality Tests
Description: Personality Test app using driver.h header file. The purpose
of this file is to have all the functions that takes in set of questions
and set of answers to compute score of user based on questions the user
answered. And takes in the set of names and their scores to search the
best match with the user for each people file that user uses.
Date: 02/03/2022

Creative Component: mine.people -> List of Songs that you must listen to right
now. And it based on several factors and that is (Harmony, Melody, Rythm, 
Quality, Emotion).

*/

#include <math.h>
#include <limits>
#include <string>
#include <map>
#include <set>
#include "myrandom.h"

using namespace std;

constexpr double lowest_double = std::numeric_limits<double>::lowest();

/* Type: Question
 *
 * Type representing a personality quiz question.
 */
struct Question {
    string questionText;  // Text of the question
    map<char, int> factors;   // Map from factors to +1 or -1
    friend bool operator< (const Question& lhs, const Question& rhs) {
        return lhs.questionText < rhs.questionText;
    }
    friend bool operator== (const Question& lhs, const Question& rhs) {
        return lhs.questionText == rhs.questionText;
    }
    friend bool operator!= (const Question& lhs, const Question& rhs) {
        return lhs.questionText != rhs.questionText;
    }
};

/* Type: Person
 *
 * Type representing a person, used to represent people when determining
 * who's the closest match to the user.
 */
struct Person {
    string name;      // Name of the person
    map<char, int> scores;  // Map from factors to +1 or -1
    friend bool operator< (const Person& lhs,   const Person& rhs) {
        return lhs.name < rhs.name;
    }
    friend bool operator== (const Person& lhs, const Person& rhs) {
        return lhs.name == rhs.name;
    }
    friend bool operator!= (const Person& lhs, const Person& rhs) {
        return lhs.name != rhs.name;
    }
};

/* randomElement
 *
 * This function selects, at random, a Question from the inputted questions set
 * and returns the question.  Note, this function does not remove the randomly
 * selected question from the set.
*/
Question randomElement(set<Question>& questions) {
    int ind = randomInteger(0, (int)questions.size()-1);
    int i = 0;
    for (auto e : questions) {
        if (i == ind) {
            return e;
        }
        i++;
    }
    return {};
}

// TODO(dwarr3): This function takes a set of type struct
// named question which has question text and the scores.
// This function calls randomElement function and gets a
// random element(question and scores). And it removes it
// from the set and returns that elemennt
Question randomQuestionFrom(set<Question>& questions) {
    if (questions.size() == 0) {
        throw runtime_error("set: empty");
    }
    Question Q;
    Q = randomElement(questions);
    for (auto &e : questions) {
        if (e.questionText == Q.questionText) {
            questions.erase(e);
            return Q;
        }
    }
    return {};
}

// TODO(dwarr): This function is more like a helper function
// which takes in the user's answer(integer value) and updates
// it between(-2 -> +2) based on what user chossed between
// strongly agree to strongly disagree and then returns that value
int scoresFrom2(int x) {
     int y = 0, i = 0;
     if (x == 0) { return -3; }
     if (x >= 6) {
      y = 3;
      i = 6;
     } else if (x >= 1 && x <= 5) {
         y = -2;
         i = 1;
     }
    while (x != i) {
        i++;
        y++;
    }
    return y;
}

// TODO(dwarr3): This function takes input a map of type
// struct Question as key and value as a number that user
// chose for answer the questions(1-5). This has a nested
// loop to first go through elements of answer map and Access
// value (a.second). It creates a an object q which Access
// the factors map in struct to compute scores of a specific key.
// Within second for loop scoresFrom2() function is called.
map<char, int> scoresFrom(map<Question, int>& answers) {
    Question q;
    int x = 0, y = 0;
    map<char, int> userInput;
    for (auto &a : answers) {
        q = a.first;
        x = a.second;  // cout << "a.second " << x << endl;
        for (auto &s : q.factors) {
            y = scoresFrom2(x);
            s.second = (y) * (s.second);
            userInput[s.first] = (userInput[s.first]) + s.second;
        }
    }
    return userInput;
}

// TODO(dwarr3): This function takes in a map called
// scores. this function first checks if all the keys are
// associated with zero then throw a runtime error. If the map
// has at least 1 non zero value then it loops through scores map
// and stores int value powered 2 associated with the same key
// in a temporary map. then loop through this temp map and add all
// the temp value into variable result and use the formula to store
// the nomralized values and return it
map<char, double> normalize(map<char, int>& scores) {
    unsigned int count = 0;
    for (auto e : scores) {
        if (e.second == 0) {
            count++;
        }
    }
    if (count == scores.size()) {
        throw runtime_error("map: empty");
    }
    map<char, double> norm;
    map<char, int> temp;
    double result = 0;
    for (auto e : scores) {
        temp[e.first] = pow(e.second, 2);
    }
    for (auto e : temp) {
        result = result + double(e.second);
    }
    result = sqrt(result);
    for (auto e : scores) {
        norm[e.first] = double(e.second) / double(result);
    }
    return norm;
}

// TODO(dwarr3): This function takes in two map containers
// this function's first two for loops check if a key in rhs map is not
// counted in lhs map and viceversa then that key is associated with 0 in
// a temp map. In nested for loop if the keys are same in both maps then
// cosine formula is applied and stored in temp map. Last for loop adds
// values from temp map and returns the similarity value which basically
// means how close the user is to the searched person.
double cosineSimilarityOf(const map<char, double>& lhs,
                          const map<char, double>& rhs) {
    map<char, double> temp;
    double similarity = 0;
    for (auto r : rhs) {
        if (lhs.count(r.first) == 0) {
            temp[r.first] = 0.0;
        }
    }
    for (auto l : lhs) {
        if (rhs.count(l.first) == 0) {
            temp[l.first] = 0.0;
        }
    }
    for (auto l : lhs) {
        for (auto r : rhs) {
            if (l.first == r.first) {
                 temp[r.first] = l.second * r.second;
            }
        }
    }
    for (auto s : temp) {
        similarity = similarity + s.second;
    }
    return similarity;
}

// TODO(dwarr3): this function takes in a map scores of user, and
// a set of type struct person named people. This function calls
// normalize() function to normalize user's scores once. A for loop
// is created to loop through the set in which at each instance the
// object p calls scores in person struct and normalizes and stores in
// peopleNorm map. userNorm and peopleNorm (the normalized scores) are
// assigned in consineSimilarity function and that function is called.
// Then if the similarity score is greater object person stores the name
// and score and after loop ends it returns the person object
Person mostSimilarTo(map<char, int>& scores, set<Person>& people) {
    if (people.empty()) {
        throw runtime_error("set: empty");
    }
    map<char, double> userNorm;
    map<char, double> peopleNorm;
    Person person;
    double similarity = 0, result = -1;
    userNorm = normalize(scores);
    for (auto p : people) {
        peopleNorm = normalize(p.scores);
        similarity = cosineSimilarityOf(peopleNorm, userNorm);
        if (similarity > result) {
            result = similarity;
            person.name = p.name;
            person.scores = p.scores;
        }
    }
    return person;
}
