#include "MainOperations.h"
#include <iostream>
#include <algorithm>
#include "Taskbook.h"
#include "FileOperations.h"
#include "pathInfo.h"
#include "Notebook.h"
using namespace std;

std::vector<Task> Notebook::notebookTasks;

void Notebook::ReadLabel(const std::string &label)
{
    if (!notebookTasks.empty())
        notebookTasks.clear();
        
    std::copy_if(MainOperations::Tasks.begin(), MainOperations::Tasks.end(),
                 std::back_inserter(notebookTasks), [&](Task p) { return p.notebook == label; });
}

void Notebook::Help_Notebook()
{
    std::cout << " Usage" << std::endl;
    std::cout << "   Taskbook: [<options> ...]\n\n";
    std::cout << "   Options\n";
    std::cout << "       none            •      Display board view\n";
    std::cout << "       begin  -b       •      Start/pause task\n";
    std::cout << "       check  -c       •      Check/uncheck task\n";
    std::cout << "       delete  -d      •      Delete item\n";
    std::cout << "       edit  -e        •      Edit item description\n";
    std::cout << "       find  -f        •      Search for items\n";
    std::cout << "       help  -h        •      Display help message\n";
    std::cout << "       note  -n        •      Create note\n";
    std::cout << "       star  -s        •      Star/unstar item\n";
    std::cout << "       task  -t        •      Create task\n";
    std::cout << "       copy  -x        •      Copy to clipboard\n";
    std::cout << "       sw (label)      •      Switch notebook\n"
              << std::endl;
}

void Notebook::Star(string str)
{
    auto vec = MainOperations::SplitDigits(std::move(str));
    if (vec.empty())
    {
        Taskbook::fail = true;
        return;
    }
    std::vector<int> send;
    for (auto &&i : vec)
    {
        auto it = find_if(notebookTasks.begin(), notebookTasks.end(), [&](Task p) { return p.number == i; });
        if (it != notebookTasks.end())
        {
            bool isstarred = notebookTasks[it - notebookTasks.begin()].starred;
            if (isstarred)
            {
                notebookTasks[it - notebookTasks.begin()].starred = false;
                send.push_back(it->number);
            }
            else
            {
                notebookTasks[it - notebookTasks.begin()].starred = true;
                send.push_back(it->number);
            }
            Taskbook::success = true;
        }
    }
    if (send.empty())
        Taskbook::fail = true;
    else
        MainOperations::Star("",send);
}

void Notebook::Edit(std::string str)
{
    auto it = find_if(str.begin(), str.end(), [](char p) { return p == ' '; });
    string temp = string(str.begin(), it);

    if (temp.empty() || !all_of(temp.begin(), temp.end(), [](char p) { return isdigit(p); }))
    {
        Taskbook::fail = true;
        return;
    }
    int num = stoi(temp);
    auto f = find_if(notebookTasks.begin(), notebookTasks.end(), [&](Task p) { return p.number == num; });
    if (f == notebookTasks.end())
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

    f = find_if(MainOperations::Tasks.begin(), MainOperations::Tasks.end(),
                [&](Task p) { return p.number == num; });
    notebookTasks[f - notebookTasks.begin()].name = ss;
    FileOperations::WriteToFile(MainOperations::Tasks, dataPath);
}

