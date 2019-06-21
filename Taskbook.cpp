#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include "Color.h"
#include <locale>
// #include <algorithm>
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
bool Taskbook::success = false;
bool Taskbook::fail = false;

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
        input = TakeInput();
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

string Taskbook::TakeInput()
{
    string input;
    if (success)
    {
        cout << Color::boldbright_black << "Taskbook " << Color::blinkboldbright_yellow << "✔" << Color::reset << " ❖ ";
        success = false;
    }
    else if (fail)
    {
        cout << Color::boldbright_black << "Taskbook " << Color::blinkboldbright_red << "✘" << Color::reset << " ❖ ";
        fail = false;
    }
    else
    {
        cout << Color::boldbright_black << "Taskbook" << Color::reset << " ❖ ";
    }
    getline(cin, input);
    input = Trim(input);

    return input;
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
    str.erase(str.begin(), find_if(str.begin(), str.end(), [](char p) { return !isspace(p); }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](int p) { return !std::isspace(p); }).base(), str.end());
    return str;
}