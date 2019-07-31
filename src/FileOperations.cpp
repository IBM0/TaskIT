#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "FileOperations.h"
#include "Operations.h"
#include "pathInfo.h"

using namespace std;

std::string FileOperations::ReturnStr(TaskStat_Enum stat)
{
    if (stat == TaskStat_Enum::done)
    {
        return "done";
    }
    else if (stat == TaskStat_Enum::undone)
    {
        return "undone";
    }
    else if (stat == TaskStat_Enum::note)
    {
        return "note";
    }
    else if (stat == TaskStat_Enum::inprogress)
    {
        return "inprogress";
    }
    return "Unknown";
}

void FileOperations::WriteToFile()
{
    ofstream file;
    file.open(dataPath, ios::trunc | ios::out);
    for (auto &Task : Operations::Tasks)
    {
        file << Task.number << "\n";
        file << Task.name << "\n";
        file << ReturnStr(Task.stat) << "\n";
        if (Task.starred)
        {
            file << "yes"
                 << "\n";
        }
        else
        {
            file << "no"
                 << "\n";
        }
        file << Task.notebook << "\n";

        file << "\n";
    }

    file.close();
}

void FileOperations::ReadFromFile()
{
    string str;
    ifstream file;
    Task unit = Task();
    file.open(dataPath, ios::in);
    int count = 0;
    while (getline(file, str))
    {
        if (str.empty())
            continue;

        if (count == 0)
            unit.number = std::stoi(str);

        else if (count == 1)
            unit.name = str;

        else if (count == 2)
        {
            if (str == "done")
                unit.stat = TaskStat_Enum::done;

            else if (str == "undone")
                unit.stat = TaskStat_Enum::undone;

            else if (str == "note")
                unit.stat = TaskStat_Enum::note;

            else if (str == "inprogress")
                unit.stat = TaskStat_Enum::inprogress;
        }

        else if (count == 3)
        {
            unit.starred = str == "yes";
        }
        else if (count == 4)
        {
            unit.notebook = str;
        }

        count++;
        if (count == 5)
        {
            Operations::Tasks.push_back(unit);
            count = 0;
        }
        str = "";
    }
}