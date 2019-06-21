#include <vector>
#include <string>
#include "Color.h"
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
    auto vec = SplitDigits(str);
    if (vec.size() == 0)
    {
        Taskbook::fail = true;
        return;
    }
    for (int i = 0; i < vec.size(); i++)
    {
        auto it = find_if(ArchiveTasks.begin(), ArchiveTasks.end(), [&](Task p) { return p.number == vec[i]; });
        if (it != ArchiveTasks.end())
        {
            it->number = GetNewNum();
            Tasks.push_back(*it);
            ArchiveTasks.erase(it, it + 1);
            Taskbook::success = true;
        }
    }
    if (!Taskbook::success)
        Taskbook::fail = true;

    Print::CountVector();
    FileOperations::WriteToFile();
    ArchiveFileOperations::WriteArchive();
}

void Operations::Begin(std::string str)
{
    auto vec = SplitDigits(str);
    if (vec.size() == 0)
    {
        Taskbook::fail = true;
        return;
    }
    for (int i = 0; i < vec.size(); i++)
    {
        auto it = find_if(Tasks.begin(), Tasks.end(), [&](Task p) { return p.number == vec[i]; });
        if (it != Tasks.end())
        {
            if (Tasks[it - Tasks.begin()].stat == TaskStat_Enum::undone)
            {
                Tasks[it - Tasks.begin()].stat = TaskStat_Enum::inprogress;
                Taskbook::success = true;
            }
            else if (Tasks[it - Tasks.begin()].stat == TaskStat_Enum::inprogress)
            {
                Tasks[it - Tasks.begin()].stat = TaskStat_Enum::undone;
                Taskbook::success = true;
            }
        }
    }
    if (!Taskbook::success)
        Taskbook::fail = true;

    Print::CountVector();
    FileOperations::WriteToFile();
}
void Operations::Check(std::string str)
{
    auto vec = SplitDigits(str);
    if (vec.size() == 0)
    {
        Taskbook::fail = true;
        return;
    }

    for (int i = 0; i < vec.size(); i++)
    {
        auto it = find_if(Tasks.begin(), Tasks.end(), [&](Task p) { return p.number == vec[i]; });
        if (it != Tasks.end())
        {
            if (Tasks[it - Tasks.begin()].stat == TaskStat_Enum::done)
            {
                Tasks[it - Tasks.begin()].stat = TaskStat_Enum::undone;
                Taskbook::success = true;
            }
            else if (Tasks[it - Tasks.begin()].stat == TaskStat_Enum::undone)
            {
                Tasks[it - Tasks.begin()].stat = TaskStat_Enum::done;
                Taskbook::success = true;
            }
            else if (Tasks[it - Tasks.begin()].stat == TaskStat_Enum::inprogress)
            {
                Tasks[it - Tasks.begin()].stat = TaskStat_Enum::done;
                Taskbook::success = true;
            }
        }
    }
    if (!Taskbook::success)
        Taskbook::fail = true;

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
            Taskbook::fail = true;
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
        Taskbook::fail = true;
        return;
    }
    int num = stoi(temp);
    auto f = find_if(Operations::Tasks.begin(), Operations::Tasks.end(), [&](Task p) { return p.number == num; });
    if (f == Operations::Tasks.end())
    {
        Taskbook::fail = true;
        return;
    }
    string ss = Taskbook::Trim(string(it, str.end()));
    if (ss == "")
    {
        Taskbook::fail = true;
        return;
    }
    if (!Taskbook::fail)
    {
        Taskbook::success = true;
    }

    Operations::Tasks[f - Operations::Tasks.begin()].name = ss;
    FileOperations::WriteToFile();
}

void Operations::AddTask(std::string taskName, TaskStat_Enum stat)
{
    if (taskName == "")
    {
        Taskbook::fail = true;
        return;
    }

    int num = GetNewNum();
    Task newTask;
    newTask.number = num;
    newTask.stat = stat;
    newTask.name = taskName;
    Tasks.push_back(newTask);
    Taskbook::success = true;
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
    Taskbook::success = true;
    FileOperations::WriteToFile();
}

void Operations::Find(std::string str)
{
    if (str == "")
    {
        Taskbook::fail = true;
        cout << Color::boldbright_red << " ♥ " << Color::underlineboldbright_black
             << "Found Items" << Color::reset << "\n"
             << endl;
        return;
    }

    vector<Task> items;
    for (int i = 0; i < Tasks.size(); i++)
    {
        if (Tasks[i].name.find(str) != string::npos)
        {
            items.push_back(Tasks[i]);
            Taskbook::success = true;
        }
    }
    if (!Taskbook::success)
    {
        Taskbook::fail = true;
    }

    cout << Color::boldbright_red << " ♥ " << Color::underlineboldbright_black
         << "Found Items" << Color::reset << endl;
    Print::PrintBody(items);
    cout << endl;
}

void Operations::RemoveTask(string str)
{
    auto vec = SplitDigits(str);
    if (vec.size() == 0)
    {
        Taskbook::fail = true;
        return;
    }
    for (int i = 0; i < vec.size(); i++)
    {
        auto it = find_if(Tasks.begin(), Tasks.end(), [&](Task p) { return p.number == vec[i]; });
        if (it != Tasks.end())
        {
            SendToArchive(*it);
            Tasks.erase(it, it + 1);
            Taskbook::success = true;
        }
    }
    if (!Taskbook::success)
    {
        Taskbook::fail = true;
    }

    Print::CountVector();
    FileOperations::WriteToFile();
}