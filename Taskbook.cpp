#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <math.h>
#include <numeric>
#include "Taskbook.h"
#include "Operations.h"
#include "FileOperations.h"
using namespace std;

int Taskbook::undoneCount;
int Taskbook::inprogress;
int Taskbook::note;
int Taskbook::doneCount;
int Taskbook::size;
static bool print = true;

void Taskbook::CountVector()
{
    undoneCount = 0;
    inprogress = 0;
    note = 0;
    doneCount = 0;
    size = Operations::Tasks.size();
    for (int i = 0; i < size; i++)
    {
        if (Operations::Tasks[i].stat == TaskStat_Enum::done)
        {
            doneCount++;
        }
        else if (Operations::Tasks[i].stat == TaskStat_Enum::undone)
        {
            undoneCount++;
        }
        else if (Operations::Tasks[i].stat == TaskStat_Enum::note)
        {
            note++;
        }
        else if (Operations::Tasks[i].stat == TaskStat_Enum::inprogress)
        {
            inprogress++;
        }
    }
}

void Taskbook::ManageTaskbook()
{
    FileOperations::ReadFromFile();
    CountVector();

    while (true)
    {
        pair<Op_Enum, string> inputPair;
        string input;

        if (print)
        {
            PrintTasks();
        }

        cout << "Taskbook: ";
        getline(cin, input);

        if (input == "exit")
            return;

        print = true;
        inputPair = ParseInput(input);
        if (inputPair.first != Op_Enum::Nil)
        {
            ManageCommand(inputPair);
        }
    }
}

void Taskbook::PrintTasks()
{
    int percent = 0;
    if (size > 0)
    {
        percent = ((doneCount * 100) / size);
    }
    cout << " ♥ My Board [" << doneCount << "/" << size << "]" << endl;
    for (int i = 0; i < size; i++)
    {
        if (Operations::Tasks[i].stat == TaskStat_Enum::done)
        {
            cout << "    " << Operations::Tasks[i].number << "."
                 << " ✔  " << Operations::Tasks[i].name << endl;
        }
        else if (Operations::Tasks[i].stat == TaskStat_Enum::undone)
        {
            cout << "    " << Operations::Tasks[i].number << "."
                 << " ☐  " << Operations::Tasks[i].name << endl;
        }
        else if (Operations::Tasks[i].stat == TaskStat_Enum::note)
        {
            cout << "    " << Operations::Tasks[i].number << "."
                 << " ★  " << Operations::Tasks[i].name << endl;
        }
        else if (Operations::Tasks[i].stat == TaskStat_Enum::inprogress)
        {
            cout << "    " << Operations::Tasks[i].number << "."
                 << " ⋯  " << Operations::Tasks[i].name << endl;
        }
    }
    cout << "\n " << percent << "% of all tasks completed\n";
    cout << " " << doneCount << " done • " << inprogress << " in-progress • ";
    cout << undoneCount << " pending"
         << " • " << note << " notes\n"
         << endl;
}

void Taskbook::ManageCommand(const std::pair<Op_Enum, std::string> &inputPair)
{
    Operations makeOperation;
    switch (inputPair.first)
    {
    case Op_Enum::add:
        makeOperation.AddTask(inputPair.second, TaskStat_Enum::undone);
        break;

    case Op_Enum::add_note:
        makeOperation.AddTask(inputPair.second, TaskStat_Enum::note);
        break;

    case Op_Enum::check:
        makeOperation.Check(inputPair.second);
        break;

    case Op_Enum::begin:
        makeOperation.Begin(inputPair.second);
        break;

    case Op_Enum::remove:
        makeOperation.RemoveTask(inputPair.second);
        break;

    case Op_Enum::edit:
        makeOperation.Edit(inputPair.second);
        break;

    case Op_Enum::help:
        makeOperation.Help();
        print = false;
        break;

    default:
        return;
    }
}

std::pair<Op_Enum, std::string> Taskbook::ParseInput(string inputstr)
{
    inputstr = Trim(inputstr);
    Op_Enum operationName;
    string parsed;
    string shortcut;

    vector<char> untilSpace;
    auto it = inputstr.begin();
    for (; it != inputstr.end(); it++)
    {
        if (*it != ' ')
        {
            untilSpace.push_back(*it);
        }
        else
            break;
    }
    shortcut = string(untilSpace.begin(), untilSpace.end());
    parsed = string(it, inputstr.end());
    parsed = Trim(parsed);

    cout << endl;
    if (shortcut == "-t" || shortcut == "--task")
        operationName = Op_Enum::add;

    else if (shortcut == "-d" || shortcut == "--delete")
        operationName = Op_Enum::remove;

    else if (shortcut == "-n" || shortcut == "--note")
        operationName = Op_Enum::add_note;

    else if (shortcut == "-c" || shortcut == "--check")
        operationName = Op_Enum::check;

    else if (shortcut == "-b" || shortcut == "--begin")
        operationName = Op_Enum::begin;

    else if (shortcut == "-e" || shortcut == "--edit")
        operationName = Op_Enum::edit;

    else if (shortcut == "-h" || shortcut == "--help")
        operationName = Op_Enum::help;

    else
        operationName = Op_Enum::Nil;

    return {operationName, parsed};
}

std::string Taskbook::Trim(std::string str)
{
    int start = 0;
    int end = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == ' ')
            start++;
        else
            break;
    }
    for (int i = str.size() - 1; i >= 0; i--)
    {
        if (str[i] == ' ')
            end++;
        else
            break;
    }
    return string(str.begin() + start, str.end() - end);
}