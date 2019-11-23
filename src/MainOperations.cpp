#include <utility>
#include <string>
#include "Color.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <algorithm>
#include <iterator>
#include "MainOperations.h"
#include "FileOperations.h"
#include "pathInfo.h"
#include "Taskbook.h"
#include "Notebook.h"
using namespace std;

std::vector<Task> MainOperations::Tasks;
std::vector<Task> MainOperations::ArchiveTasks;

bool MainOperations::is_number(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

int MainOperations::GetNewNum()
{
    int size = Tasks.size();
    int num = 1;
    if (size >= 1)
    {
        num = Tasks[size - 1].number + 1;
    }
    return num;
}
int MainOperations::GetNewNumArchive()
{
    int size = ArchiveTasks.size();
    int num = 1;
    if (size >= 1)
    {
        num = ArchiveTasks[size - 1].number + 1;
    }
    return num;
}

void MainOperations::SendToArchive(Task deletedTask)
{
    deletedTask.number = GetNewNumArchive();
    ArchiveTasks.push_back(deletedTask);
    FileOperations::WriteToFile(ArchiveTasks, ArchivePath);
}

void MainOperations::Restore(std::string str)
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
    FileOperations::WriteToFile(Tasks, dataPath);
    FileOperations::WriteToFile(ArchiveTasks, ArchivePath);
}

void MainOperations::Begin(std::string str)
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
    FileOperations::WriteToFile(Tasks, dataPath);
}

void MainOperations::Check(std::string str)
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
    FileOperations::WriteToFile(Tasks, dataPath);
}

std::vector<int> MainOperations::SplitDigits(std::string str)
{
    std::istringstream iss(str);
    vector<string> tokens{istream_iterator<string>{iss},
                          istream_iterator<string>{}};
    std::vector<int> numbers;
    try
    {

        std::vector<std::__cxx11::string>::iterator it;
        while ((it = std::find_if(tokens.begin(), tokens.end(), [](std::string item) { return item.find('-') != std::string::npos; })) != tokens.end())
        {
            auto pos = (*it).find("-");
            int first = stoi(tokens[it - tokens.begin()].substr(0, pos));
            int second = stoi(tokens[it - tokens.begin()].substr(pos + 1));
            for (int i = first; i <= second; i++)
            {
                numbers.push_back(i);
            }

            tokens.erase(it);
        }
        for (int i = 0; i < tokens.size(); i++)
        {
            numbers.push_back(stoi(tokens[i]));
        }
    }
    catch (const std::exception &e)
    {
        Taskbook::fail = true;
        return {};
    }

    std::sort(numbers.begin(), numbers.end());
    numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());
    return numbers;
}

void MainOperations::Help()
{
    std::cout << " Usage" << endl;
    std::cout << "   Taskbook: [<options> ...]\n\n";
    std::cout << "   Options\n";
    std::cout << "       none            •      Display board view\n";
    std::cout << "       archive  -a     •      Display archived items\n";
    std::cout << "       begin  -b       •      Start/pause task\n";
    std::cout << "       check  -c       •      Check/uncheck task\n";
    std::cout << "       delete  -d      •      Delete item\n";
    std::cout << "       edit  -e        •      Edit item description\n";
    std::cout << "       find  -f        •      Search for items\n";
    std::cout << "       help  -h        •      Display help message\n";
    std::cout << "       list  -l        •      List items by attributes\n";
    std::cout << "       note  -n        •      Create note\n";
    std::cout << "       mv  -m          •      change name of notebooks\n";
    std::cout << "       restore  -r     •      Restore from archive\n";
    std::cout << "       star  -s        •      Star/unstar item\n";
    std::cout << "       task  -t        •      Create task\n";
    std::cout << "       copy  -x        •      Copy to clipboard\n";
    std::cout << "       sw (label)      •      Switch notebook\n";
    std::cout << "       clear           •      Clear archive\n"
              << endl;
}

void MainOperations::CopyToClipboard(const std::vector<Task> &vec, std::string str,const std::string & label)
{
    auto sp = SplitDigits(std::move(str));
    if (sp.size() != 1)
    {
        Taskbook::fail = true;
        return;
    }
    int num = sp[0];
    if (label != "My Board")
    {
        auto k = find_if(Notebook::notebookTasks.begin(),Notebook::notebookTasks.end(), [&](Task p) { return p.number == num; });
        if (k==Notebook::notebookTasks.end())
        {
            Taskbook::fail = true;
            return;
        }
    }
    auto f = find_if(vec.begin(), vec.end(), [&](Task p) { return p.number == num; });
    if (f == vec.end())
    {
        Taskbook::fail = true;
        return;
    }
    Taskbook::success = true;
    std::string p = "echo -n \"" + vec[f-vec.begin()].name + "\" | xclip -selection clipboard";
    const char *proc = p.c_str();
    system(proc);
}

void MainOperations::Edit(std::string str)
{
    auto it = find_if(str.begin(), str.end(), [](char p) { return p == ' '; });
    string temp = string(str.begin(), it);

    if (temp.empty() || !all_of(temp.begin(), temp.end(), [](char p) { return isdigit(p); }))
    {
        Taskbook::fail = true;
        return;
    }
    int num = stoi(temp);
    auto f = find_if(MainOperations::Tasks.begin(), MainOperations::Tasks.end(), [&](Task p) { return p.number == num; });
    if (f == MainOperations::Tasks.end())
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

    MainOperations::Tasks[f - MainOperations::Tasks.begin()].name = ss;
    FileOperations::WriteToFile(Tasks, dataPath);
}

void MainOperations::AddTask(const std::string &taskName, TaskStat_Enum stat, const std::string &label)
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
    FileOperations::WriteToFile(Tasks, dataPath);
}

void MainOperations::Clear()
{
    ofstream file(ArchivePath);
    ArchiveTasks.clear();
    for (int i = 0; i < Tasks.size(); i++)
    {
        Tasks[i].number = i + 1;
    }
    Taskbook::success = true;
    FileOperations::WriteToFile(Tasks, dataPath);
}

void MainOperations::Find(const vector<Task> &vec, const std::string &str)
{
    bool enter = true;
    if (str.empty())
    {
        enter = false;
    }
    vector<Task> items;
    if (enter)
    {
        for (auto &Task : vec)
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

    std::cout << boldred << " オ" << underLinemagenta << "Found Items" << reset << endl;
    Print::PrintBody(items, true);
    std::cout << endl;
}

set<string> MainOperations::NotebookSplit(string str)
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

void MainOperations::IterateNotebooks(const std::set<std::string> &myset)
{
    for (auto &&i : myset)
    {
        vector<Task> temp;
        copy_if(Tasks.begin(), Tasks.end(), back_inserter(temp), [&](Task p) { return p.notebook == i; });
        Print::CountVector(temp);
        Print::PrintTasks(temp, false, "@" + i);
        std::cout << endl;
    }
}

void MainOperations::AllNotebooks()
{
    std::set<std::string> myset;
    std::transform(Tasks.begin(), Tasks.end(), inserter(myset, myset.begin()), [](Task p) { return p.notebook; });
    Print::PrintNotebooks(myset);
}

void MainOperations::List(string str)
{
    if (str.empty())
    {
        set<string> myset;
        std::transform(Tasks.begin(), Tasks.end(), inserter(myset, myset.begin()), [](Task p) { return p.notebook; });
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

void MainOperations::Move(std::string str)
{
    str = str + " ";
    std::vector<std::string> tokens;
    std::vector<int> numbers;
    std::__cxx11::string::iterator it;
    while ((it = std::find(str.begin(), str.end(), ' ')) != str.end())
    {
        std::string temp = string(str.begin(), it);
        str.erase(str.begin(), it + 1);
        if (temp.empty() || std::all_of(temp.begin(), temp.end(), [](char p) { return p == ' '; }))
        {
            continue;
        }
        if (is_number(temp))
            numbers.push_back(stoi(temp));
        else
            tokens.push_back(temp);
    }

    std::string last;
    bool changed = false;
    if (tokens.size() < 1)
    {
        Taskbook::fail = true;
        return;
    }
    last = tokens[tokens.size() - 1];
    if (numbers.size() == 0 && tokens.size() == 2)
    {
        auto k = Tasks.begin();
        while ((k = std::find_if(Tasks.begin(), Tasks.end(), [&](Task p) { return p.notebook == tokens[0]; })) != Tasks.end())
        {
            Tasks[k - Tasks.begin()].notebook = last;
            changed = true;
        }
        if (changed)
        {
            Taskbook::success = true;
            FileOperations::WriteToFile(Tasks, dataPath);
            return;
        }
    }
    if (numbers.size() > 0 && tokens.size() == 1)
    {
        for (auto &&i : numbers)
        {
            auto k = std::find_if(Tasks.begin(), Tasks.end(), [&](Task p) { return p.number == i; });
            if (k != Tasks.end())
            {
                Tasks[k - Tasks.begin()].notebook = last;
                changed = true;
            }
        }

        if (changed)
        {
            Taskbook::success = true;
            FileOperations::WriteToFile(Tasks, dataPath);
            return;
        }
    }
    Taskbook::fail = true;
}

void MainOperations::Star(string str, vector<int> vec)
{
    if (vec.empty())
    {
        vec = SplitDigits(std::move(str));
        if (vec.empty())
        {
            Taskbook::fail = true;
            return;
        }
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
    FileOperations::WriteToFile(Tasks, dataPath);
}

void MainOperations::RemoveTask(string str,const std::string & label)
{
    auto vec = SplitDigits(std::move(str));
    if (vec.empty())
    {
        Taskbook::fail = true;
        return;
    }
    for (int i : vec)
    {
        if (label != "My Board")
        {
            auto k = find_if(Notebook::notebookTasks.begin(), Notebook::notebookTasks.end(), [&](Task p) { return p.number == i; });
            if (k != Notebook::notebookTasks.end())
            {
                Notebook::notebookTasks.erase(k, k + 1);
                Taskbook::success = true;
            }
            else
                continue;
        }
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
    FileOperations::WriteToFile(Tasks, dataPath);
}