#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <math.h>
#include <numeric>
#include "Taskbook.h"
// #include "Task.h"
#include "Operations.h"
using namespace std;

void Taskbook::ManageTaskbook()
{
    while (true)
    {
        pair<Op_Enum, string> inputPair;
        string input;

        PrintTasks();
        cout << "Taskbook:";
        getline(cin,input);

        if (input == "exit")
        {
            cout << "exiting" << endl;
            return;
        }
        inputPair = ParseInput(input);
        if (inputPair.first != Op_Enum::Nil)
        {
            ManageCommand(inputPair);
        }
    }
}

void Taskbook::PrintTasks()
{
    int doneCount = count_if(Operations::Tasks.begin(),Operations::Tasks.end(),[](Task p){return p.stat == TaskStat_Enum::done;});
    int size = Operations::Tasks.size();
    cout << "My Board[" << doneCount << "/" << size << "]"<< endl;
    for (int i = 0; i < size; i++)
    {
        cout << "  " << Operations::Tasks[i].number<< "." << " S " << Operations::Tasks[i].name << endl;
    }
    cout << endl;
}

void Taskbook::ManageCommand(const std::pair<Op_Enum, std::string> &inputPair)
{
    Operations makeOperation;
    switch (inputPair.first)
    {
    case Op_Enum::add:
        makeOperation.AddTask(inputPair.second);
        break;

    case Op_Enum::remove:
        makeOperation.RemoveTask(inputPair.second);
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
    // cout << "inputstr : " + inputstr<< endl;

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
    // cout << "shortcut :" + shortcut<< endl;

    parsed = string(it, inputstr.end());
    parsed = Trim(parsed);
    // cout << "parsed :" + parsed<< endl;

    cout << endl;
    if (shortcut == "-t")
        operationName = Op_Enum::add;
    else if (shortcut == "-d")
        operationName = Op_Enum::remove;
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