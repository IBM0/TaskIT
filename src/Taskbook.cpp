#include <iostream>
#include <string>
#include <algorithm>
#include "Color.h"
#include <fstream>
#include "Taskbook.h"
#include "Operations.h"
#include "FileOperations.h"
#include "pathInfo.h"
#include "ArchiveFileOperations.h"
#include <unistd.h>
#include "Notebook.h"
using namespace std;

bool Taskbook::print = true;
bool Taskbook::success = false;
bool Taskbook::fail = false;
std::string Taskbook::fall_back = "";
std::string Taskbook::label;
std::string UserName;
std::string dataPath;
std::string ArchivePath;

void Taskbook::SetPaths()
{
    char *p = getlogin();
    UserName = string(p);
    dataPath = "/home/" + UserName + "/.taskbook/data.txt";
    ArchivePath = "/home/" + UserName + "/.taskbook/archive.txt";
}

void Taskbook::ManageTaskbook(const std::string argv) // notebook version
{
    label = argv;
    Notebook::ReadLabel(label);
    Print::CountVector(Operations::notebookTasks);

    while (true)
    {
        pair<Op_Enum, string> inputPair;
        string input;

        if (print)
        {
            Print::PrintTasks(Operations::notebookTasks, false, label);
        }
        input = TakeInput();
        if (input == "")
        {
            cout << "\n";
            print = true;
            continue;
        }

        if (input == "exit")
        {
            fall_back = "exit";
            return;
        }

        print = true;
        inputPair = ParseInput(input);
        if (inputPair.first != Op_Enum::Nil)
        {
            if (ManageCommand_Notebook(inputPair, label))
            {
                Notebook::ReadLabel(label);
                Print::CountVector(Operations::notebookTasks);
            }
            if (!fall_back.empty())
            {
                return;
            }
        }
    }
}

void Taskbook::Startexe()
{
    SetPaths();
    FileOperations::ReadFromFile();
    ArchiveFileOperations::ReadArchive();
}

void Taskbook::ManageTaskbook()
{
    Print::CountVector(Operations::Tasks);
    while (true)
    {
        pair<Op_Enum, string> inputPair;
        string input;

        if (print)
        {
            Print::PrintTasks(Operations::Tasks, true, "My Board");
        }
        input = TakeInput();
        if (input == "")
        {
            cout << "\n";
            print = true;
            continue;
        }

        if (input == "exit")
        {
            fall_back = "exit";
            return;
        }

        if (input == "clear")
            Operations::Clear();

        print = true;
        inputPair = ParseInput(input);
        if (inputPair.first != Op_Enum::Nil)
        {
            ManageCommand(inputPair);
            if (!fall_back.empty())
            {
                return;
            }
        }
    }
}

std::string Taskbook::TakeInput()
{
    string input;
    if (success)
    {
        cout << boldblue << "Taskbook " << boldyellow << "✔" << reset << " ❖ ";
        success = false;
    }
    else if (fail)
    {
        cout << boldblue << "Taskbook " << boldred << "✘" << reset << " ❖ ";
        fail = false;
    }
    else
    {
        cout << boldblue << "Taskbook" << reset << " ❖ ";
    }
    getline(cin, input);
    input = Trim(input);

    return input;
}

bool Taskbook::ManageCommand_Notebook(const std::pair<Op_Enum, std::string> &inputPair, const std::string &label)
{
    Operations makeOperation;
    switch (inputPair.first)
    {
    case Op_Enum::add:
        makeOperation.AddTask(inputPair.second, TaskStat_Enum::undone, label);
        break;

    case Op_Enum::add_note:
        makeOperation.AddTask(inputPair.second, TaskStat_Enum::note, label);
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
        makeOperation.Edit_inNotebook(inputPair.second);
        break;

    case Op_Enum::star:
        makeOperation.Star(inputPair.second);
        break;

    case Op_Enum::help:
        makeOperation.Help_Notebook();
        print = false;
        return false;

    case Op_Enum::copy:
        makeOperation.CopyToClipboard(inputPair.second);
        return false;

    case Op_Enum::find:
        makeOperation.Find(inputPair.second);
        print = false;
        return false;

    case Op_Enum::sw:
        if (!inputPair.second.empty())
        {
            fall_back = inputPair.second;
            return false;
        }
        fall_back = "default";
        return false;

    case Op_Enum::clear:
    case Op_Enum::list:
    case Op_Enum::archive:
    case Op_Enum::restore:
    case Op_Enum::move:
        fail = true;
        break;

    case Op_Enum::Nil:
        return false;
    }
    return true;
}

void Taskbook::ManageCommand(const std::pair<Op_Enum, std::string> &inputPair)
{
    Operations makeOperation;
    switch (inputPair.first)
    {
    case Op_Enum::add:
        makeOperation.AddTask(inputPair.second, TaskStat_Enum::undone);
        break;

    case Op_Enum::sw:
        fall_back = inputPair.second;
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

    case Op_Enum::clear:
        makeOperation.Clear();
        break;

    case Op_Enum::list:
        print = false;
        makeOperation.List(inputPair.second);
        break;

    case Op_Enum::star:
        makeOperation.Star(inputPair.second);
        break;

    case Op_Enum::move:
        makeOperation.Move(inputPair.second);
        break;

    case Op_Enum::help:
        makeOperation.Help();
        print = false;
        break;

    case Op_Enum::copy:
        makeOperation.CopyToClipboard(inputPair.second);
        break;

    case Op_Enum::archive:
        Print::PrintArchive();
        print = false;
        break;

    case Op_Enum::restore:
        makeOperation.Restore(inputPair.second);
        break;

    case Op_Enum::find:
        print = false;
        makeOperation.Find(inputPair.second);
        break;

    case Op_Enum::Nil:
        return;
    }
}

std::pair<Op_Enum, std::string> Taskbook::ParseInput(const std::string & inputstr)
{
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
    parsed = string(it,inputstr.end());
    parsed = Trim(parsed);

    cout << endl;
    if (shortcut == "t" ||shortcut == "-t" || shortcut == "task")
        operationName = Op_Enum::add;

    else if (shortcut == "d" ||shortcut == "-d" || shortcut == "delete")
        operationName = Op_Enum::remove;

    else if (shortcut == "n" ||shortcut == "-n" || shortcut == "note")
        operationName = Op_Enum::add_note;

    else if (shortcut == "c" ||shortcut == "-c" || shortcut == "check")
        operationName = Op_Enum::check;

    else if (shortcut == "b" ||shortcut == "-b" || shortcut == "begin")
        operationName = Op_Enum::begin;

    else if (shortcut == "e" ||shortcut == "-e" || shortcut == "edit")
        operationName = Op_Enum::edit;

    else if (shortcut == "h" ||shortcut == "-h" || shortcut == "help")
        operationName = Op_Enum::help;

    else if (shortcut == "f" ||shortcut == "-f" || shortcut == "find")
        operationName = Op_Enum::find;

    else if (shortcut == "a" ||shortcut == "-a" || shortcut == "archive")
        operationName = Op_Enum::archive;

    else if (shortcut == "sw")
        operationName = Op_Enum::sw;

    else if (shortcut == "l" ||shortcut == "-l" || shortcut == "list")
        operationName = Op_Enum::list;

    else if (shortcut == "s" ||shortcut == "-s" || shortcut == "star")
        operationName = Op_Enum::star;

    else if (shortcut == "r" ||shortcut == "-r" || shortcut == "restore")
        operationName = Op_Enum::restore;

    else if (shortcut == "x" ||shortcut == "-x" || shortcut == "copy")
        operationName = Op_Enum::copy;

    else if (shortcut == "m" ||shortcut == "-m" || shortcut == "move")
        operationName = Op_Enum::move;

    else
    {
        operationName = Op_Enum::Nil;
        Taskbook::fail = true;
    }

    return {operationName, parsed};
}

std::string Taskbook::Trim(std::string str)
{
    str.erase(str.begin(), find_if(str.begin(), str.end(), [](char p) { return !isspace(p); }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](int p) { return !std::isspace(p); }).base(), str.end());
    return str;
}