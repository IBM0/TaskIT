#include <fstream>
#include <iostream>
#include <string>
#include "ArchiveFileOperations.h"
#include "Operations.h"
#include "FileOperations.h"
#include "pathInfo.h"
#include <unistd.h>

using namespace std;

void ArchiveFileOperations::WriteArchive()
{
    ofstream file;
    file.open(ArchivePath, ios::trunc | ios::out);
    for (auto &ArchiveTask : Operations::ArchiveTasks)
    {
        bool st = ArchiveTask.starred;
        file << ArchiveTask.number << "\n";
        file << ArchiveTask.name << "\n";
        file << FileOperations::ReturnStr(ArchiveTask.stat) << "\n";
        if (st)
        {
            file << "yes"
                 << "\n";
        }
        else
        {
            file << "no"
                 << "\n";
        }
        file << ArchiveTask.notebook << "\n";

        file << endl;
    }

    file.close();
}
void ArchiveFileOperations::ReadArchive()
{
    string str;
    ifstream file;
    Task unit;
    file.open(ArchivePath, ios::in);
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
            Operations::ArchiveTasks.push_back(unit);
            count = 0;
        }
        str = "";
    }
    file.close();
}