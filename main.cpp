#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>

CONSOLE_SCREEN_BUFFER_INFO csbi;
HANDLE hStdOutput;
BOOL bUsePause;

using namespace std;

//ofstream questLog("log.txt");
void readFromQuestFile()
{
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
    cout << "\t \t \t \t \t \t \t" << "<Current log>\n\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    ifstream questLog("log.txt");
    string line;
    if (questLog.is_open())
    {
        int logEntry = 0;
        while(getline(questLog, line))
        {
            logEntry++;
            cout << logEntry << "\t" << line << "\n\n";
        }

        questLog.close();
    }
    return;
}

//Lmao gejat van internet ik had er geen zin meer in
void eraseFileLine() {
    std::string line;
    std::ifstream fin;
    std::string path = "log.txt";
    std::string eraseLine;
    int delNumber = 0;
    int currLogNumber = 0;
    cout << "del number:";
    cin >> delNumber;

    fin.open("log.txt");
    // contents of path must be copied to a temp file then
    // renamed back to the path file
    std::ofstream temp;
    temp.open("temp.txt");
    

    while (getline(fin, line)) {
        // write all lines to temp other than the line marked for erasing
        currLogNumber++;

        if (currLogNumber != delNumber)
        {
            temp << line << "\n";
        }
    }

    temp.close();
    fin.close();

    // required conversion for remove and rename functions
    const char * p = path.c_str();
    remove(p);
    rename("temp.txt", p);
    system("cls");
    readFromQuestFile();
}

void writeToQuestFile()
{
    system("cls");
    string a;
    cout << "Give the new task a name\n";
    cout << "Just keep it simple and all\n";
    cout << "Name of new task: ";
    getline(std::cin >> std::ws, a);
    ofstream questLog("log.txt", std::ios_base::app);
    questLog.write(a.data(), a.size());
    questLog << "\n";
    questLog.close();
    system("cls");
    readFromQuestFile();
    return;
}

void clearLog()
{
    ofstream questLog("log.txt");
    questLog.close();   
}

int main(void)
{
    int inputCommand;

    hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!GetConsoleScreenBufferInfo(hStdOutput, &csbi))
    {
        printf("GetConsoleScreenBufferInfo failed: %d\n", GetLastError());
        return 0;
    }

    readFromQuestFile();
        
    while(true)
    {
        cin >> inputCommand;
            
        switch (inputCommand)
        {
            case 1:
               readFromQuestFile();
               break;
            case 2:
                writeToQuestFile();
                break;
            case 3:
                eraseFileLine();
                break;
            default:
                break;
            }
        }
        
    return 0;
}