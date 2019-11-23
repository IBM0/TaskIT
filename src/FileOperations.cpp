#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "FileOperations.h"
#include "MainOperations.h"
#include "pathInfo.h"

using namespace std;

std::string FileOperations::ReturnStr(TaskStat_Enum stat)
{
    if (stat == TaskStat_Enum::done)
        return "done";

    else if (stat == TaskStat_Enum::undone)
        return "undone";

    else if (stat == TaskStat_Enum::note)
        return "note";

    else if (stat == TaskStat_Enum::inprogress)
        return "inprogress";

    return "Unknown";
}

void FileOperations::WriteToFile(const std::vector<Task> &vec, const std::string &path)
{
    ofstream file;
    file.open(path, ios::trunc | ios::out);
    for (auto &Task : vec)
    {
        file << Task.number << "\n";
        file << Task.name << "\n";
        file << ReturnStr(Task.stat) << "\n";

        if (Task.starred)
            file << "yes"
                 << "\n";

        else
            file << "no"
                 << "\n";

        file << Task.notebook << "\n";
        file << endl;
    }
    file.close();
}

void FileOperations::ReadFromFile(std::vector<Task> &vec, const std::string &path)
{
    string str;
    ifstream file;
    Task unit = Task();
    file.open(path, ios::in);
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
            unit.starred = str == "yes";

        else if (count == 4)
            unit.notebook = str;

        count++;
        if (count == 5)
        {
            vec.push_back(unit);
            count = 0;
        }
        str = "";
    }
    file.close();
}