#include <utility>
#include <string>
#include "Color.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <iterator>
#include "Operations.h"
#include "FileOperations.h"
#include "ArchiveFileOperations.h"
#include "pathInfo.h"
#include "Taskbook.h"
using namespace std;

std::vector<Task> Operations::Tasks;
std::vector<Task> Operations::notebookTasks;
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
    auto vec = SplitDigits(std::move(str));
    if (vec.empty())
    {
        Taskbook::fail = true;
        return;
    }
    for (int i : vec)
    {
        auto it = find_if(ArchiveTasks.begin(), ArchiveTasks.end(), [&](Task p) { return p.number == i; });
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

    Print::CountVector(Tasks);
    FileOperations::WriteToFile();
    ArchiveFileOperations::WriteArchive();
}

void Operations::Begin(std::string str)
{
    auto vec = SplitDigits(std::move(str));
    if (vec.empty())
    {
        Taskbook::fail = true;
        return;
    }
    for (int i : vec)
    {
        auto it = find_if(Tasks.begin(), Tasks.end(), [&](Task p) { return p.number == i; });
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

    Print::CountVector(Tasks);
    FileOperations::WriteToFile();
}
void Operations::Check(std::string str)
{
    auto vec = SplitDigits(std::move(str));
    if (vec.empty())
    {
        Taskbook::fail = true;
        return;
    }

    for (int i : vec)
    {
        auto it = find_if(Tasks.begin(), Tasks.end(), [&](Task p) { return p.number == i; });
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

    Print::CountVector(Tasks);
    FileOperations::WriteToFile();
}

std::vector<int> Operations::SplitDigits(std::string str)
{
    vector<string> numbers;
    auto it = str.begin();
    string temp;
    while (it != str.end())
    {
        if (isdigit(*it))
        {
            temp = temp + (*it);
        }
        else if (*it == ' ')
        {
            if (!temp.empty())
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
    if (!temp.empty())
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
    cout << "       none            •      Display board view\n";
    cout << "       archive  -a     •      Display archived items\n";
    cout << "       begin  -b       •      Start/pause task\n";
    cout << "       check  -c       •      Check/uncheck task\n";
    cout << "       delete  -d      •      Delete item\n";
    cout << "       edit  -e        •      Edit item description\n";
    cout << "       find  -f        •      Search for items\n";
    cout << "       help  -h        •      Display help message\n";
    cout << "       list  -l        •      List items by attributes\n";
    cout << "       note  -n        •      Create note\n";
    cout << "       restore  -r     •      Restore from archive\n";
    cout << "       star  -s        •      Star/unstar item\n";
    cout << "       task  -t        •      Create task\n";
    cout << "       copy  -x        •      Copy to clipboard\n";
    cout << "       clear           •      Clear archive\n"
         << endl;
}

void Operations::Help_Notebook()
{
    cout << " Usage" << endl;
    cout << "   Taskbook: [<options> ...]\n\n";
    cout << "   Options\n";
    cout << "       none            •      Display board view\n";
    cout << "       begin  -b       •      Start/pause task\n";
    cout << "       check  -c       •      Check/uncheck task\n";
    cout << "       delete  -d      •      Delete item\n";
    cout << "       edit  -e        •      Edit item description\n";
    cout << "       find  -f        •      Search for items\n";
    cout << "       help  -h        •      Display help message\n";
    cout << "       note  -n        •      Create note\n";
    cout << "       star  -s        •      Star/unstar item\n";
    cout << "       task  -t        •      Create task\n";
    cout << "       copy  -x        •      Copy to clipboard\n"
         << endl;
}

void Operations::CopyToClipboard(std::string str)
{
    auto vec = SplitDigits(std::move(str));
    if (vec.size() != 1)
    {
        Taskbook::fail = true;
        return;
    }
    auto f = find_if(Operations::Tasks.begin(), Operations::Tasks.end(), [&](Task p) { return p.number == vec[0]; });
    if (f == Operations::Tasks.end())
    {
        Taskbook::fail = true;
        return;
    }
    Taskbook::success = true;
    std::string p = "python3 /home/mert/Git/TaskIT/python/clipboard.py \"" + Operations::Tasks[vec[0] - 1].name + "\"";
    const char *proc = p.c_str();
    system(proc);
}

void Operations::Edit(std::string str)
{
    auto it = find_if(str.begin(), str.end(), [](char p) { return p == ' '; });
    string temp = string(str.begin(), it);

    if (temp.empty() || !all_of(temp.begin(), temp.end(), [](char p) { return isdigit(p); }))
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
    if (ss.empty())
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

void Operations::AddTask(const std::string &taskName, TaskStat_Enum stat, const std::string &label)
{
    if (taskName.empty())
    {
        Taskbook::fail = true;
        return;
    }

    int num = GetNewNum();
    Task newTask;
    newTask.number = num;
    newTask.stat = stat;
    newTask.starred = false;

    auto t = find_if(taskName.rbegin(), taskName.rend(), [](char p) { return p == '@'; });
    auto it = t.base();
    if (it != taskName.begin() && ((*(it - 2)) == ' '))
    {
        newTask.name = Taskbook::Trim(string(taskName.begin(), it - 2));
        if (newTask.name.empty())
        {
            Taskbook::fail = true;
            return;
        }
        newTask.notebook = Taskbook::Trim(string(it, taskName.end()));
        if (newTask.notebook == "")
        {
            Taskbook::fail = true;
            Taskbook::print = true;
            return;
        }
    }
    else
    {
        newTask.name = taskName;
        newTask.notebook = "My Board";
    }
    if (label != "")
    {
        newTask.notebook = label;
    }

    Tasks.push_back(newTask);
    Taskbook::success = true;
    Print::CountVector(Tasks);
    FileOperations::WriteToFile();
}

void Operations::Clear()
{
    ofstream file(ArchivePath);
    ArchiveTasks.clear();
    for (int i = 0; i < Tasks.size(); i++)
    {
        Tasks[i].number = i + 1;
    }
    Taskbook::success = true;
    FileOperations::WriteToFile();
}

void Operations::Find(const std::string &str)
{
    bool enter = true;
    if (str.empty())
    {
        enter = false;
    }
    vector<Task> items;
    if (enter)
    {
        for (auto &Task : Tasks)
        {
            if (Task.name.find(str) != string::npos)
            {
                items.push_back(Task);
                Taskbook::success = true;
            }
        }
    }

    if (!Taskbook::success)
    {
        Taskbook::fail = true;
        Taskbook::print = true;
        return;
    }

    cout << boldred << " オ" << underLinemagenta << "Found Items" << reset << endl;
    Print::PrintBody(items, true);
    cout << endl;
}

set<string> Operations::NotebookSplit(string str)
{
    vector<std::string> items;
    auto pos = str.begin();
    if (str != "")
    {
        std::string token;
        do
        {
            pos = find_if(str.begin(), str.end(), [](char p) { return p != ' '; });
            str.erase(str.begin(), pos);
            pos = find_if(str.begin(), str.end(), [](char p) { return p == ' '; });
            items.push_back(string(str.begin(), pos));
            str.erase(str.begin(), pos);

        } while (str != "");
    }

    set<string> myset;
    for (auto &item : items)
    {
        bool anyof = any_of(Tasks.begin(), Tasks.end(), [&](Task p) { return p.notebook == item; });
        if (anyof)
        {
            myset.insert(item);
        }
    }
    return myset;
}

void Operations::IterateNotebooks(const std::set<std::string> &myset)
{
    for (auto &&i : myset)
    {
        vector<Task> temp;
        copy_if(Tasks.begin(), Tasks.end(), back_inserter(temp), [&](Task p) { return p.notebook == i; });
        Print::CountVector(temp);
        Print::PrintTasks(temp, false, "@" + i);
        cout << endl;
    }
}

void Operations::List(string str)
{
    if (str.empty())
    {
        set<string> myset;
        transform(Tasks.begin(), Tasks.end(), inserter(myset, myset.begin()), [](Task p) { return p.notebook; });
        IterateNotebooks(myset);
        Print::CountVector(Tasks);
        return;
    }

    auto notebooks = NotebookSplit(str);
    if (notebooks.empty())
    {
        Taskbook::fail = true;
        Taskbook::print = true;
        return;
    }
    else
    {
        IterateNotebooks(notebooks);
    }
    Print::CountVector(Tasks);
}

void Operations::Star(string str)
{
    auto vec = SplitDigits(std::move(str));
    if (vec.empty())
    {
        Taskbook::fail = true;
        return;
    }
    for (auto &&i : vec)
    {
        auto it = find_if(Tasks.begin(), Tasks.end(), [&](Task p) { return p.number == i; });
        if (it != Tasks.end())
        {
            bool isstarred = Tasks[it - Tasks.begin()].starred;
            if (isstarred)
            {
                Tasks[it - Tasks.begin()].starred = false;
            }
            else
            {
                Tasks[it - Tasks.begin()].starred = true;
            }
            Taskbook::success = true;
        }
    }
    FileOperations::WriteToFile();
}

void Operations::RemoveTask(string str)
{
    auto vec = SplitDigits(std::move(str));
    if (vec.empty())
    {
        Taskbook::fail = true;
        return;
    }
    for (int i : vec)
    {
        auto it = find_if(Tasks.begin(), Tasks.end(), [&](Task p) { return p.number == i; });
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

    Print::CountVector(Tasks);
    FileOperations::WriteToFile();
}