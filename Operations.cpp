#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Operations.h"
#include "FileOperations.h"
#include "ArchiveFileOperations.h"
#include "Taskbook.h"
using namespace std;

std::vector<Task> Operations::Tasks;
std::vector<Task> Operations::ArchiveTasks;

int Operations::GetNewNum()
{
    int size = Tasks.size();
    int num = 1;
    if (size >= 1)
    {
        num = Tasks[size - 1].number + 1;
    }
    return num;
}
int Operations::GetNewNumArchive()
{
    int size = ArchiveTasks.size();
    int num = 1;
    if (size >= 1)
    {
        num = ArchiveTasks[size - 1].number + 1;
    }
    return num;
}

void Operations::SendToArchive(Task deletedTask)
{
    deletedTask.number = GetNewNumArchive();
    ArchiveTasks.push_back(deletedTask);
    ArchiveFileOperations::WriteArchive();
}

void Operations::Restore(std::string str)
{
    vector<int> couldntfind;
    auto vec = SplitDigits(str);
    if (vec.size() == 0)
        return;
    for (int i = 0; i < vec.size(); i++)
    {
        auto it = find_if(ArchiveTasks.begin(), ArchiveTasks.end(), [&](Task p) { return p.number == vec[i]; });
        if (it != Tasks.end())
        {
            it->number = GetNewNum();
            Tasks.push_back(*it);
            ArchiveTasks.erase(it, it + 1);
        }
        else
        {
            couldntfind.push_back(vec[i]);
        }
    }
    Print::CountVector();
    FileOperations::WriteToFile();
    ArchiveFileOperations::WriteArchive();
}

void Operations::Begin(std::string str)
{
    auto vec = SplitDigits(str);
    if (vec.size() == 0)
        return;

    vector<int> addedbegin;
    vector<int> couldntFind;
    for (int i = 0; i < vec.size(); i++)
    {
        auto it = find_if(Tasks.begin(), Tasks.end(), [&](Task p) { return p.number == vec[i]; });
        if (it != Tasks.end())
        {
            if (Tasks[it - Tasks.begin()].stat == TaskStat_Enum::undone)
            {
                Tasks[it - Tasks.begin()].stat = TaskStat_Enum::inprogress;
                addedbegin.push_back(vec[i]);
            }
            else if (Tasks[it - Tasks.begin()].stat == TaskStat_Enum::inprogress)
            {
                Tasks[it - Tasks.begin()].stat = TaskStat_Enum::undone;
                addedbegin.push_back(vec[i]);
            }
        }
        else
        {
            couldntFind.push_back(vec[i]);
        }
    }
    Print::CountVector();
    FileOperations::WriteToFile();
}
void Operations::Check(std::string str)
{
    auto vec = SplitDigits(str);
    if (vec.size() == 0)
        return;

    vector<int> checked;
    vector<int> couldntFind;
    for (int i = 0; i < vec.size(); i++)
    {
        auto it = find_if(Tasks.begin(), Tasks.end(), [&](Task p) { return p.number == vec[i]; });
        if (it != Tasks.end())
        {
            if (Tasks[it - Tasks.begin()].stat == TaskStat_Enum::done)
            {
                Tasks[it - Tasks.begin()].stat = TaskStat_Enum::undone;
            }
            else if (Tasks[it - Tasks.begin()].stat == TaskStat_Enum::undone)
            {
                Tasks[it - Tasks.begin()].stat = TaskStat_Enum::done;
            }
            else if (Tasks[it - Tasks.begin()].stat == TaskStat_Enum::inprogress)
            {
                Tasks[it - Tasks.begin()].stat = TaskStat_Enum::done;
            }
        }
        else
        {
            couldntFind.push_back(vec[i]);
        }
    }
    Print::CountVector();
    FileOperations::WriteToFile();
}

std::vector<int> Operations::SplitDigits(std::string str)
{
    vector<string> numbers;
    auto it = str.begin();
    string temp = "";
    while (it != str.end())
    {
        if (isdigit(*it))
        {
            temp = temp + (*it);
        }
        else if (*it == ' ')
        {
            if (temp.size() > 0)
            {
                numbers.push_back(temp);
            }
            temp = "";
        }
        else
        {
            cout << "\nfailll " << endl;
            return {};
        }
        it++;
    }
    if (temp.size() > 0)
        numbers.push_back(temp);

    vector<int> allnumbers;
    sort(numbers.begin(), numbers.end());
    numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());
    transform(numbers.begin(), numbers.end(), back_inserter(allnumbers), [](string p) { return stoi(p); });
    return allnumbers;
}

void Operations::Help()
{
    cout << " Usage" << endl;
    cout << "   Taskbook: [<options> ...]\n\n";
    cout << "   Options\n";
    cout << "       none                Display board view\n";
    cout << "       --archive -a        Display archived items\n";
    cout << "       --begin -b          Start/pause task\n";
    cout << "       --check -c          Check/uncheck task\n";
    cout << "       --delete -d         Delete item\n";
    cout << "       --edit -e           Edit item description\n";
    cout << "       --find -f           Search for items\n";
    cout << "       --help -h           Display help message\n";
    cout << "       --note -n           Create note\n";
    cout << "       --restore -r        Restore from archive\n";
    cout << "       --task -t           Create task\n";
    cout << "       clear               Clear archive\n"
         << endl;
}
void Operations::Edit(std::string str)
{
    auto it = find_if(str.begin(), str.end(), [](char p) { return p == ' '; });
    string temp = string(str.begin(), it);

    if (temp.size() == 0 || !all_of(temp.begin(), temp.end(), [](char p) { return isdigit(p); }))
    {
        cout << "faill" << endl;
        return;
    }
    int num = stoi(temp);
    auto f = find_if(Operations::Tasks.begin(), Operations::Tasks.end(), [&](Task p) { return p.number == num; });
    if (f == Operations::Tasks.end())
    {
        cout << "faill" << endl;
        return;
    }
    string ss = Taskbook::Trim(string(it, str.end()));
    if (ss == "")
    {
        cout << "fail" << endl;
        return;
    }
    Operations::Tasks[f - Operations::Tasks.begin()].name = ss;
    FileOperations::WriteToFile();
}

void Operations::AddTask(std::string taskName, TaskStat_Enum stat)
{
    int num = GetNewNum();
    Task newTask;
    newTask.number = num;
    newTask.stat = stat;
    newTask.name = taskName;
    Tasks.push_back(newTask);
    Print::CountVector();
    FileOperations::WriteToFile();
}

void Operations::Clear()
{
    ofstream file(ArchiveFileOperations::ArchivePath);
    ArchiveTasks.clear();
    for (int i = 0; i < Tasks.size(); i++)
    {
        Tasks[i].number = i + 1;
    }
    FileOperations::WriteToFile();
}

void Operations::Find(std::string str)
{
    vector<Task> items;
    for (int i = 0; i < Tasks.size(); i++)
    {
        if (Tasks[i].name.find(str) != string::npos)
        {
            items.push_back(Tasks[i]);
        }
    }
    cout << " ♥ Found Items" << endl;
    Print::PrintBody(items);
    cout << endl;
}

void Operations::RemoveTask(string str)
{
    auto vec = SplitDigits(str);
    if (vec.size() == 0)
        return;

    vector<int> couldntFind;
    vector<int> removed;
    for (int i = 0; i < vec.size(); i++)
    {
        auto it = find_if(Tasks.begin(), Tasks.end(), [&](Task p) { return p.number == vec[i]; });
        if (it != Tasks.end())
        {
            SendToArchive(*it);
            Tasks.erase(it, it + 1);
            removed.push_back(vec[i]);
        }
        else
        {
            couldntFind.push_back(vec[i]);
        }
    }
    Print::CountVector();
    FileOperations::WriteToFile();
}