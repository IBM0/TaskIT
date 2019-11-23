#include <vector>
#include <string>
#include <set>
#include "Print.h"
class Task;
class MainOperations
{
private:
    static int GetNewNum();
    static int GetNewNumArchive();
    static std::set<std::string> NotebookSplit(std::string);

public:
    static std::vector<Task> Tasks;
    static std::vector<Task> ArchiveTasks;
    /*mutual*/static std::vector<int> SplitDigits(std::string);
    /*mutual*/static bool is_number(const std::string& s);
    /*mutual*/static void Find(const std::vector<Task> & vec,const std::string &);
    /*mutual*/static void CopyToClipboard(const std::vector<Task> & vec,std::string,const std::string & label);
    /*mutual*/static void List(std::string);
    /*mutual*/static void IterateNotebooks(const std::set<std::string> &);
    /*mutual*/static void AddTask(const std::string &taskName, TaskStat_Enum stat, const std::string &label);
    /*mutual*/static void RemoveTask(std::string str,const std::string & label);
    static void AllNotebooks();
    /*no need mutual*/static void SendToArchive(Task);
    /*no need mutual*/static void Restore(std::string);
    /*no need mutual*/static void Clear();
    /*no need mutual*/static void Help();
    static void Edit(std::string);
    /*send clear add*/static void Check(std::string);
    /*send clear add*/static void Begin(std::string);
    /*send clear add*/static void Star(std::string,std::vector<int>);
    static void Move(std::string);
};