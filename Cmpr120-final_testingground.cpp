// Cmpr120-final_testingground.cpp : This file contains the 'main' function. (i would have never guessed Microsoft)
//

#include <iostream>
#include <io.h>
#include <windows.h>
#include <string>
#include <iomanip>

//i got tired of typing out 'std::' over and over again
using namespace std;

//prototypes

void Clear();
void Menu();

//defining most funcs as int's, as a form of data-oriented design & crude error handling.

int inputHandling(int input);
int loadSettings();
int writeSettings();
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
    printf("testing again");
    Sleep(1000);

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
        cout << setw(65) << "1. option 1 \n";
        cout << setw(65) << "2. option 2 \n";
        cout << setw(65) << "3. option 3 \n";
        cout << setw(65) << "4. option 4 \n";
        cout << setw(61) << "5. quit \n";

        //adjusting the last cout and not adding a new line to make the cursor somewhat centered
        cout << endl << setw(65) << "enter option: ";
        cin >> usrInput;

        //menu state handling
        if (inputHandling(usrInput) == 1) {
            menuState = 1;
            cout << "\033[32mdebug\033[0m: state active\n";
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
    switch (input) {
    case 1:

    case 2:

    case 3:

    case 4:
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

