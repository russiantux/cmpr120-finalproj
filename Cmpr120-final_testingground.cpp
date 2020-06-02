// Cmpr120-final_testingground.cpp : This file contains the 'main' function. (i would have never guessed Microsoft)
//

#include <iostream>
#include <io.h>
#include <windows.h>
#include <string>
#include <iomanip>
#include <fstream>

//i got tired of typing out 'std::' over and over again
using namespace std;

//prototypes

void Clear();
void Menu();

//defining most funcs as int's, as a form of data-oriented design & crude error handling.

int inputHandling(int input);
int loadSettings();
int writeSettings(int busNo, int sType);
int displaySettings(int busNo);
int createBus();
int reserveBus();

//const int for number of max bus seats & max buses
const int maxSeats = 32;
const int maxBuses = 10;

//main buffer arrays for bus/seat info
// found out about 2d arrays, pretty good bro

string busInfo[maxBuses][6];
string riderInfo[maxBuses][maxSeats];

//store the state of the menu, so see if needed to redraw after finishing a func
int menuState = 1;

int busAva = 0;

ifstream dataIn;
ofstream dataOut;

int main()
{
    //protype test bed, will clean it up
    Sleep(100);
    std::cout << std::setw(50) << "Bus Software\n";
    std::cout << std::setw(70) << "Bus Software\n";
    std::cout << std::setw(90) << "Bus Software\n";
    Sleep(2000);
    printf("test.");
    Clear();
    loadSettings();

    //actual init of menu/program
    Clear();
    Menu();

    //clean the console before exiting
    Clear();
    return 0;
}

//main menu func
void Menu() {
    int usrInput = 0;

    while (menuState == 1) {

        //i spent too much time making it look somewhat neat. windows api are a pain to deal with, so I stuck with setw() and ANSI color tables.
        Clear();
        //hey, it works.
        cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
        cout << setw(91) << "\033[1;36mAirport Transport Bus Reservation System\033[0m\n";
        cout << setw(73) << " Viktor Lazarev | CMPR-120\n" << endl;
        cout << setw(60) << "Main Menu: \n";
        cout << setw(65) << "1. Install a Bus \n";
        cout << setw(65) << "2. Reserve a spot \n";
        cout << setw(65) << "3. Show Bus Info \n";
        cout << setw(65) << "4. Bus Avalible \n";
        cout << setw(61) << "5. quit \n";

        //adjusting the last cout and not adding a new line to make the cursor somewhat centered
        cout << endl << setw(65) << "enter option: ";
        cin >> usrInput;

        //menu state handling
        if (inputHandling(usrInput) == 1) {
            menuState = 1;
            
            Sleep(1000);
        }
        else if (inputHandling(usrInput) == 0) {
            menuState = 1;
            cout<< endl << setw(87) << "\033[31merror\033[0m: invalid option, please try again.\n";
            Sleep(1000);
        }
        else if (inputHandling(usrInput) == -1) {
            menuState = 0;
        }
    }
}

//input validation, leading to other funcs
//returns a 1 if valid, -1 to exit, and 0 if input isnt vailid
int inputHandling(int input) {
    int i, j = -1;
    switch (input) {
    case 1:
        createBus();
        return 1;
        break;
    case 2:
        reserveBus();
        return 1;
        break;
    case 3:
        
        while (j == -1) {
            Clear();
            cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
            cout << setw(65) << "Enter a bus #: ";
            cin >> i;

            if (displaySettings(i) == 1) {
                j = 0;
                return 1;
                break;
            }
            else if (displaySettings(i) == -1) {
                j = -1;
            }
        }
       
    case 4:
        cout << endl << setw(65) << "There is " << busAva <<" busses avalible. \n";
        Sleep(2000);
        return 1;
        break;
    case 5:
        return -1;
        break;

    default:
        return 0;
        break;
    };
}

int loadSettings() {
    Clear();
    string fName = " ";
    //load all the busses into memory
    for (int i = 0; i < (maxBuses); i++) {
        fName = ("bus" + to_string(i) + ".txt");
        dataIn.open(fName);
        if (dataIn.is_open()) {
            while (dataIn.good()) {
                for (int j = 0; j < 7; j++) {
                    dataIn >> busInfo[i][j];
                    
                }
                busAva++;
            }
        }
        else {
            cout << endl << "\033[32mnotice\033[0m: file bus" << (i) << ".txt not found.\n";
            Sleep(100);
        }
        dataIn.close();
    }

    //load all the riders into memory
    for (int i = 0; i < (maxBuses); i++) {
        fName = ("busR" + to_string(i) + ".txt");
        dataIn.open(fName);
        if (dataIn.is_open()) {
            while (dataIn.good()) {
                for (int j = 0; j < maxSeats; j++) {
                    dataIn >> riderInfo[i][j];
                }
            }
        }
        else {
            cout << endl << "\033[32mnotice\033[0m: file busR" << (i) << ".txt not found.\n";
            Sleep(100);
        }
        dataIn.close();
    }
    Sleep(5000);
    return 1;
}

int createBus() {
    int i;
    Clear();
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << setw(65) << "Enter the bus #: ";
    cin >> i;
    if (i >= maxBuses) {
        i = maxBuses;
    }
    busInfo[(i -1)][0] = to_string(i);
    cout << setw(65) << endl << "Enter driver's name: ";
    cin >> busInfo[(i - 1)][1];
    cout << setw(65) << endl << "Arrival time: ";
    cin >> busInfo[(i - 1)][2];
    cout << setw(65) << endl << "Depart time: ";
    cin >> busInfo[(i - 1)][3];
    cout << setw(65) << endl << "From: ";
    cin >> busInfo[(i - 1)][4];
    cout << setw(65) << endl << "To: ";
    cin >> busInfo[(i - 1)][5];
    
    writeSettings(i, 1);

    return 1;
}

int reserveBus() {
    int i,j;
    Clear();
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << setw(65) << "Enter the bus #: ";
    cin >> i;
    if (i >= maxBuses) {
        i = maxBuses;
    }
    cout << endl << setw(65) << "Enter the seat # ( #1 - " << maxSeats << "): ";
    cin >>j;
    if (j >= maxSeats) {
        j = maxSeats;
    }
    
    cout << setw(65) << endl << "Enter rider's name: ";
    cin >> riderInfo[i - 1][j - 1];;
    
    writeSettings(i, 2);

    return 1;
}
//func to transfer data into 
int writeSettings(int busNo, int sType) {
    string fName = " ";
    if (sType == 1) {
        fName = "bus" + to_string(busNo) + ".txt";
        dataOut.open(fName);
        dataOut << busInfo[(busNo - 1)][0] << endl;
        dataOut << busInfo[(busNo - 1)][1] << endl;
        dataOut << busInfo[(busNo - 1)][2] << endl;
        dataOut << busInfo[(busNo - 1)][3] << endl;
        dataOut << busInfo[(busNo - 1)][4] << endl;
        dataOut << busInfo[(busNo - 1)][5] << endl;
    }
    else if (sType == 2) {
        fName = "busR" + to_string(busNo) + ".txt";
        dataOut.open(fName);
        for (int i = 0; i < (maxSeats); i++) {
            dataOut << riderInfo[busNo - 1][i] << endl;
        }
    }

    dataOut.close();
    return 1;
}

int displaySettings(int busNo) {
    int usrInput = -1;
    int j = 1;
    Clear();
 

    cout << setw(45) << endl << "Bus No.: " << busNo;
    cout << "  |  Driver's name: " << busInfo[busNo - 1][1];
    cout << setw(45) << endl << "Arrival time: " << busInfo[busNo - 1][2];
    cout << "  |  Depart time: " << busInfo[busNo - 1][3];
    cout << setw(45) << endl << "From: " << busInfo[busNo - 1][4];
    cout << "  |  To: " << busInfo[busNo - 1][5];
    cout << endl;

    for (int i = 0; i < maxSeats; i++) {
        cout << (i + 1) << ". " << riderInfo[busNo - 1][i] << setw(10);
        j++;
        if (j == 5) {
            cout << endl;
            j = 1;
        }
    }

    cout << endl << setw(45) << "Enter 0 to exit or 1 to look at a different bus : ";
    cin >> usrInput;

    if (usrInput == 1) {
        return -1;
    }
    else {
        return 1;
    }

}

//func to clear console, hopefully works with all OS's (why did I bother, i used windows.h already, good luck getting it on ubuntu or macos lul
void Clear() {
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined (__APPLE__)
    system("clear");
#endif
}

