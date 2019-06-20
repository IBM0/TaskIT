#include <fstream>
#include <iostream>
#include <string>
#include "ArchiveFileOperations.h"
#include "Operations.h"
#include "FileOperations.h"
using namespace std;

const string ArchiveFileOperations::ArchivePath = "/home/mert/.taskbook/archive.txt";

void ArchiveFileOperations::WriteArchive()
{
    ofstream file;
    file.open(ArchivePath, ios::trunc | ios::out);
    for (int i = 0; i < Operations::ArchiveTasks.size(); i++)
    {
        file << Operations::ArchiveTasks[i].number << endl;
        file << Operations::ArchiveTasks[i].name << endl;
        file << FileOperations::ReturnStr(Operations::ArchiveTasks[i].stat) << endl;
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
            Operations::ArchiveTasks.push_back(unit);
            count = 0;
        }
        str = "";
    }
    file.close();
}