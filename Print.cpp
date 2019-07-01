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

            cout << "    " << fadecyan << i.number << "." << reset
                 << boldbright_yellow << " ✔  " << reset << fadecyan << i.name << reset;
        }
        else if (i.stat == TaskStat_Enum::undone)
        {
            cout << "    " << fadecyan << i.number << "."
                 << magenta << " ☐  " << cyan << i.name << reset;
        }
        else if (i.stat == TaskStat_Enum::note)
        {
            cout << "    " << fadecyan << i.number << "."
                 << blue << " ●  " << cyan << i.name << reset;
        }
        else if (i.stat == TaskStat_Enum::inprogress)
        {
            cout << "    " << fadecyan << i.number << "."
                 << bright_blue << " ⋯  " << cyan << i.name << reset;
        }
        if (st)
        {
            cout << boldbright_green << " ★" << reset;
        }
        if (isprint&&i.notebook !="My Board")
        {
            cout << fadecyan << " @" + i.notebook << reset;
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

    if (isprint)
    {
        cout << boldbright_red << " ♥ ";
        cout << boldblack
             << name << reset << cyan << " [" << doneCount << "/" << size << "]" << reset << endl;
    }
    else
    {
        cout << "  " << boldblue
             << name << cyan << " [" << doneCount << "/" << size << "]" << reset << endl;
    }

    PrintBody(vec,isprint);

    if (isprint)
    {

        cout << "\n " << fadecyan << percent << "% of all tasks completed\n"
             << reset;
        cout << " " << boldyellow << doneCount << reset << fadecyan << " done · " << reset
             << boldcyan << inprogress << reset << fadecyan << " in-progress · " << reset
             << boldblack << undoneCount << reset << fadecyan << " pending" << reset
             << " · " << boldblue << note << reset << fadecyan << " notes\n"
             << reset
             << endl;
    }
}

void Print::PrintArchive()
{
    cout << boldbright_red << " ネ" << boldblack
         << "Archive" << reset << endl;

    PrintBody(Operations::ArchiveTasks,true);
    cout << endl;
}
