// Christopher Dickerson
// 6-15-2020
// CIS1111
// This program is meant for use by Cross Country coaches to enter in their team's times. It will generate a leaderboard based on each athlete's seeded time 
// It then puts the entered data in a .txt file, and reads that data from that text file into multiple different vectors where times are then sorted by a 
// selection sort. It then outputs the rankings with a random bib number. (This Program could also be used by athletes)

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// Outputs menu
void menu() {
    cout << "1 to continue entering times / 2 to see the data: ";
}

// Generates random bib number between 1 and 100
int bibNum() {
    return abs(rand() % 100 + 1);
}

// This makes sure I don't forget to put count as a parameter
void txtToArr() {
    cout << "Code Error: Forgot to add count.";
}

// Overloaded version of the function above.
// Puts the .txt into a vector and sorts it
vector<string> txtToArr(int c) {
    ifstream unList;
    unList.open("unorderedList.txt");
    vector<string> names;
    vector<double> times;
    vector<int> bNum;
    int tempIn;
    string tempS;
    double tempD;
    int tempI;

    // Adds data to their respective vectors 
    // Was having trouble sorting 2d arrays/vectors because I was only wanting to sort one column so I used multiple vectors 
    string str;
    while (unList.good()) {
        unList >> tempIn;

        unList >> tempS;
        names.push_back(tempS);
        
        unList >> tempD;
        times.push_back(tempD);

        unList >> tempI;
        bNum.push_back(tempI);
    }

    int small;
    string temp;
    double temp2;
    int temp3;

    //Sorts the times vector and moves the corresponding values with it
    for (int i = 0; i < c - 1; i++) {
        small = i;
        for (int j = i + 1; j < c; j++) {
            if (times[j] < times[small]) {
               small = j;
            }
        }
        temp = names[i];
        temp2 = times[i];
        temp3 = bNum[i];
        times[i] = times[small];
        names[i] = names[small];
        bNum[i] = bNum[small];
        names[small] = temp;
        times[small] = temp2;
        bNum[small] = temp3;
    }

    // Compiles all of the vectors together
    vector<string> all;
    for (unsigned int i = 0; i < names.size(); i++) {
        all.push_back(to_string(i+1));
        all.push_back(names[i]);
        all.push_back(to_string(times[i]));
        all.push_back(to_string(bNum[i]));
    }

    unList.close();
    return all;
}

int main()
{


    // Variables
    string name;
    double PR;
    int input;
    int count = 0;
    ofstream unorderedList;
    unorderedList.open("unorderedList.txt");

    cout << "Enter in information to get a leaderboard based on PR times.\n\n";
    do {
        count++;
        unorderedList << count << " ";
        cout << "Enter athlete name: ";
        cin >> name;
        unorderedList << name << " ";

        cout << "\n\nEnter in athlete PR (Personal Record). For example 17:41 = 17.41: ";
        cin >> PR;
        unorderedList << PR << " " << bibNum() << "\n";
        menu();
        cin >> input;
        cout << "\n\n";
    } while (input == 1);

    unorderedList.close();

    if (input == 2) {

        cout << "Seed\tName\tPR\t\tBib Number\n";

        // Outputs vectors
        int count2 = 0;
        vector<string> data = txtToArr(count);
        for (unsigned int i = 0; i < data.size()-4; i++) {
            if (count2 == 4) {
                cout << endl;
                count2 = 0;
            }
            cout << txtToArr(count)[i] << "\t";
            count2++;
        }
        txtToArr(count);
    }
    else if (input != 1 && input != 2) {
        cout << "\n\n";
        exit(0);
    }
    cout << "\n\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu