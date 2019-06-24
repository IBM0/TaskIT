#include "Operations.h"
#include <vector>
#include <iostream>
#include "Color.h"
using namespace std;

int Print::undoneCount;
int Print::inprogress;
int Print::note;
int Print::doneCount;
int Print::size;

void Print::CountVector()
{
    undoneCount = 0;
    inprogress = 0;
    note = 0;
    doneCount = 0;
    for (auto & Task : Operations::Tasks)
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

void Print::PrintBody(const std::vector<Task> &vec)
{
    for (const auto & i : vec)
    {
        if (i.stat == TaskStat_Enum::done)
        {
            cout << "    " << Color::fadecyan << i.number << "."
                 << Color::yellow << " ✔  " << Color::fadecyan << i.name << Color::reset << endl;
        }
        else if (i.stat == TaskStat_Enum::undone)
        {
            cout << "    " << Color::fadecyan << i.number << "."
                 << Color::magenta << " ☐  " << Color::cyan << i.name << Color::reset << endl;
        }
        else if (i.stat == TaskStat_Enum::note)
        {
            cout << "    " << Color::fadecyan << i.number << "."
                 << Color::blue << " ●  " << Color::cyan << i.name << Color::reset << endl;
        }
        else if (i.stat == TaskStat_Enum::inprogress)
        {
            cout << "    " << Color::fadecyan << i.number << "."
                 << Color::bright_blue << " ⋯  " << Color::cyan << i.name << Color::reset << endl;
        }
    }
}

void Print::PrintTasks()
{
    int percent = 0;
    if (size > 0)
    {
        percent = ((doneCount * 100) / size);
    }

    cout << Color::boldbright_red << " ♥ " << Color::underlineboldbright_black
         << "My Board" << Color::cyan << " [" << doneCount << "/" << size << "]" << Color::reset << endl;

    PrintBody(Operations::Tasks);

    cout << "\n " << Color::cyan << percent << "% of all tasks completed\n";
    cout << " " << Color::boldyellow << doneCount << Color::cyan << " done · "
         << Color::boldcyan << inprogress << Color::cyan << " in-progress · "
         << Color::boldblack << undoneCount << Color::cyan << " pending"
         << " · " << Color::boldblue << note << Color::cyan << " notes\n"
         << Color::reset
         << endl;
}

void Print::PrintArchive()
{
    cout << Color::boldbright_red << " ♥ " << Color::underlineboldbright_black
         << "Archive" << Color::reset << endl;

    PrintBody(Operations::ArchiveTasks);
    cout << endl;
}
