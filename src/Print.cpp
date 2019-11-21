#include "Operations.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include "Color.h"
using namespace std;

int Print::undoneCount;
int Print::inprogress;
int Print::note;
int Print::doneCount;
int Print::size;

void Print::CountVector(const vector<Task> &vec)
{
    undoneCount = 0;
    inprogress = 0;
    note = 0;
    doneCount = 0;
    for (auto &Task : vec)
    {
        if (Task.stat == TaskStat_Enum::done)
        {
            doneCount++;
        }
        else if (Task.stat == TaskStat_Enum::undone)
        {
            undoneCount++;
        }
        else if (Task.stat == TaskStat_Enum::note)
        {
            note++;
        }
        else if (Task.stat == TaskStat_Enum::inprogress)
        {
            inprogress++;
        }
    }
    size = doneCount + undoneCount + inprogress;
}

void Print::PrintBody(const std::vector<Task> &vec, bool isprint)
{
    for (const auto &i : vec)
    {
        bool st = false;
        if (i.starred)
        {
            st = true;
        }

        if (i.stat == TaskStat_Enum::done)
        {

            cout << "    " << gray << i.number << "." << reset
                 << boldyellow << " ✔  " << reset << gray << i.name << reset;
        }
        else if (i.stat == TaskStat_Enum::undone)
        {
            cout << "    " << gray << i.number << "."
                 << boldmagenta << " ☐  " << brightblue << i.name << reset;
        }
        else if (i.stat == TaskStat_Enum::note)
        {
            cout << "    " << gray << i.number << "."
                 << boldblue << " ●  " << brightblue << i.name << reset;
        }
        else if (i.stat == TaskStat_Enum::inprogress)
        {
            cout << "    " << gray << i.number << "."
                 << orange << " ⋯  " << brightblue << i.name << reset;
        }
        if (st)
        {
            cout << orange << " ★" << reset;
        }
        if (isprint && i.notebook != "My Board")
        {
            cout << gray << " @" + i.notebook << reset;
        }

        cout << endl;
    }
}

void Print::PrintTasks(const std::vector<Task> &vec, bool isprint = true, std::string name = "My Board")
{
    int percent = 0;
    if (size > 0)
    {
        percent = ((doneCount * 100) / size);
    }

    cout << boldred << " ♥ ";
    cout << underLinemagenta
         << name << reset << gray << " [" << doneCount << "/" << size << "]" << reset << endl;

    PrintBody(vec, isprint);


    cout << "\n " << gray << percent << "% of all tasks completed\n"
         << reset;
    cout << " " << boldyellow << doneCount << reset << gray << " done · " << reset
         << boldorange << inprogress << reset << gray << " in-progress · " << reset
         << boldmagenta << undoneCount << reset << gray << " pending" << reset
         << " · " << boldblue << note << reset << gray << " notes\n"
         << reset
         << endl;
}

void Print::PrintArchive()
{
    cout << boldred << " ネ" << underLinemagenta
         << "Archive" << reset << endl;

    PrintBody(Operations::ArchiveTasks, true);
    cout << endl;
}
