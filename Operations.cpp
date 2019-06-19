#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include "Operations.h"
using namespace std;

std::vector<Task> Operations::Tasks;

void Operations::AddTask(std::string taskName)
{
    int size = Tasks.size();
    int num = 1;
    if (size>=1)
    {
        num = Tasks[size-1].number+1;
        /* code */
    }
    Task newTask;
    newTask.number = num;
    newTask.stat = TaskStat_Enum::undone;
    newTask.name = taskName;
    Tasks.push_back(newTask);
}

void Operations::RemoveTask(string taskNumberstr)
{
    int taskNumber = stoi(taskNumberstr);
    auto it = find_if(Tasks.begin(),Tasks.end(),[&](Task p ){return p.number == taskNumber;});
    if (it != Tasks.end())
    {
        Tasks.erase(it,it+1);
        cout << "\nremoved" << endl;
    }
}