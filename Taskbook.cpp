#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <math.h>
#include <numeric>
#include <fstream>
#include <experimental/filesystem>
#include "Taskbook.h"
#include "Operations.h"
#include "FileOperations.h"
#include "ArchiveFileOperations.h"
#include <experimental/filesystem>
using namespace std;

static bool print = true;

void Taskbook::ManageTaskbook()
{
    FileOperations::ReadFromFile();
    ArchiveFileOperations::ReadArchive();
    ifstream f(ArchiveFileOperations::ArchivePath.c_str());
    if (!f.good())
    {
        ofstream file(ArchiveFileOperations::ArchivePath);
    }
    Print::CountVector();

    while (true)
    {
        pair<Op_Enum, string> inputPair;
        string input;

        if (print)
        {
            Print::PrintTasks();
        }

        cout << "Taskbook: ";
        getline(cin, input);
        input = Trim(input);

        if (input == "exit")
            return;

        if (input == "clear")
            Operations::Clear();

        print = true;
        inputPair = ParseInput(input);
        if (inputPair.first != Op_Enum::Nil)
        {
            ManageCommand(inputPair);
        }
    }
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

    case Op_Enum::archive:
        Print::PrintArchive();
        print = false;
        break;

    case Op_Enum::find:
        makeOperation.Find(inputPair.second);
        print = false;
        break;

    case Op_Enum::restore:
        makeOperation.Restore(inputPair.second);
        print = false;
        break;

    default:
        return;
    }
}

std::pair<Op_Enum, std::string> Taskbook::ParseInput(string inputstr)
{
    inputstr = inputstr;
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

    else if (shortcut == "-f" || shortcut == "--find")
        operationName = Op_Enum::find;

    else if (shortcut == "-a" || shortcut == "--archive")
        operationName = Op_Enum::archive;

    else if (shortcut == "-r" || shortcut == "--restore")
        operationName = Op_Enum::restore;

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