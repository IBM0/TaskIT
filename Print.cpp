#include "Operations.h"
#include <vector>
#include <iostream>
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
    size = Operations::Tasks.size();
    for (int i = 0; i < size; i++)
    {
        if (Operations::Tasks[i].stat == TaskStat_Enum::done)
        {
            doneCount++;
        }
        else if (Operations::Tasks[i].stat == TaskStat_Enum::undone)
        {
            undoneCount++;
        }
        else if (Operations::Tasks[i].stat == TaskStat_Enum::note)
        {
            note++;
        }
        else if (Operations::Tasks[i].stat == TaskStat_Enum::inprogress)
        {
            inprogress++;
        }
    }
}

void Print::PrintBody(const std::vector<Task> &vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i].stat == TaskStat_Enum::done)
        {
            cout << "    " << vec[i].number << "."
                 << " ✔  " << vec[i].name << endl;
        }
        else if (vec[i].stat == TaskStat_Enum::undone)
        {
            cout << "    " << vec[i].number << "."
                 << " ☐  " << vec[i].name << endl;
        }
        else if (vec[i].stat == TaskStat_Enum::note)
        {
            cout << "    " << vec[i].number << "."
                 << " ★  " << vec[i].name << endl;
        }
        else if (vec[i].stat == TaskStat_Enum::inprogress)
        {
            cout << "    " << vec[i].number << "."
                 << " ⋯  " << vec[i].name << endl;
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
    cout << " ♥ My Board [" << doneCount << "/" << size << "]" << endl;
    PrintBody(Operations::Tasks);

    cout << "\n " << percent << "% of all tasks completed\n";
    cout << " " << doneCount << " done • " << inprogress << " in-progress • ";
    cout << undoneCount << " pending"
         << " • " << note << " notes\n"
         << endl;
}

void Print::PrintArchive()
{
    cout << " ♥ Archive" << endl;
    PrintBody(Operations::ArchiveTasks);
    cout << endl;
}
