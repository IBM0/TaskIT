#include <iostream>
#include "FileOperations.h"
#include <fstream>
#include <vector>
#include <string>
#include "Operations.h"
using namespace std;
const std::string FileOperations::dataPath = "/home/mert/.taskbook/data.txt";

std::string ReturnStr(TaskStat_Enum stat)
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
    for (int i = 0; i < Operations::Tasks.size(); i++)
    {
        file << Operations::Tasks[i].number << endl;
        file << Operations::Tasks[i].name << endl;
        file << ReturnStr(Operations::Tasks[i].stat) << endl;
        file << endl;
    }

    file.close();
}

void FileOperations::ReadFromFile()
{
    string str;
    ifstream file;
    Task unit;
    file.open(dataPath, ios::in);
    int count = 0;
    while (getline(file, str))
    {
        if (str == "")
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
        count++;
        if (count == 3)
        {
            Operations::Tasks.push_back(unit);
            count = 0;
        }
        str = "";
    }
}