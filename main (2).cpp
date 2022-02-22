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
// #include "driver.h"

using namespace std;

void printCharts(map<string, int> chart18, map<string, int> chart18J, string artist) {
    double avg = 0;
    double result = 0;
    double score = 0;
    for (auto e : chart18) {
        if (e.first == artist) {
        cout << e.first << " " << e.second << endl;
        score = score + (double)e.second;
        } else {
            result = result + (double)e.second;
        }
    }
    for (auto e : chart18J) {
        if (e.first == artist) {
        cout << e.first << " " << e.second << endl;
        score = score + (double)e.second;
        avg = result / chart18.size()+1;
        }
    }
    if (chart18J.count(artist) == 0) {
    avg = result/chart18.size();
    }
     if (score > avg) {
        cout << "This artist has ABOVE average streams." << endl;
     //  cout << avg << endl;
    } else {
        cout << "This artist has BELOW average streams." << endl;
       // cout << avg << endl;
    }
    
}

void printCharts2(map<string, int> chart19, map<string, int> chart19J, string artist) {
    double avg = 0;
    double result = 0;
    double score = 0;
    for (auto e : chart19) {
        if (e.first == artist) {
        cout << e.first << " " << e.second << endl;
        score = score + (double)e.second;
        } else {
            result = result + (double)e.second;
        }
    }
    for (auto e : chart19J) {
        if (e.first == artist) {
        cout << e.first << " " << e.second << endl;
        score = score + (double)e.second;
        avg = result / chart19.size()+1;
        }
    }
    if (chart19J.count(artist) == 0) {
    avg = result/chart19.size();
    }
     if (score > avg) {
        cout << "This artist has ABOVE average streams." << endl;
    //    cout << avg << endl;
    } else {
        cout << "This artist has BELOW average streams." << endl;
      //  cout << avg << endl;
    }
    
}

void printMap2(map<string, int> chart19, map<string, int> chartJ19) {
    cout << "\nTop 13 charts on day 19: \n";
    for (auto e : chart19) {
        cout << e.first << " " << e.second << endl;
    }
    for (auto e : chartJ19) {
        cout << e.first << " " << e.second << endl;
    }
}

void printMap1(map<string, int> chart18, map<string, int> chartJ18) {
    cout << "Top 13 charts on day 18: \n";
    for (auto e : chart18) {
        cout << e.first << " " << e.second << endl;
    }
    for (auto e : chartJ18) {
        cout << e.first << " " << e.second << endl;
    }
}

int main() {
    ifstream inFile;
    int num = 0, day = 0;
    string header, name, numStreams, artist;
    inFile.open("student7_DataFile.txt");
    map<string, int> chart18;
    map<string, int> chart19;
    map<string, int> chartJ18;
    map<string, int> chartJ19;
    getline(inFile, header, '\n');
    while (!inFile.eof()) {
        if (!inFile.fail()) {
            inFile >> name;
            inFile >> numStreams;
            num = stoi(numStreams);
            if (!chart18.count(name)) {
                chart18[name] = num;
            } else if (!chart19.count(name)) {
                chart19[name] = num;
            } else if (!chartJ18.count(name)) {
                chartJ18[name] = num;
            } else if (!chartJ19.count(name)) {
                chartJ19[name] = num;
            }
        }
    }
    inFile.close();
    printMap1(chart18, chartJ18);
    printMap2(chart19, chartJ19);
    cout << "Input Artist's name: ";
    cin >> artist;
    while (artist != "end") {
        if (chart18.count(artist)) { 
    cout << "Enter day to check Artist's streams: ";
    cin >> day;     
    cout << header << endl;
    if (day == 18) {
    printCharts(chart18, chartJ18, artist);
    } else if (day == 19) {
    printCharts2(chart19, chartJ19, artist);
        }
    }
    cout << "Input Artist's name: ";
    cin >> artist;
    }
    return 0;
}
  