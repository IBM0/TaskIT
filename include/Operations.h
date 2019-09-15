#include <string>
#include <vector>
#include <set>
#include "Print.h"
class Operations
{
private:
    static int GetNewNum();
    static int GetNewNumArchive();
    static std::set<std::string> NotebookSplit(std::string);

public:
    static std::vector<Task> Tasks;
    static std::vector<Task> ArchiveTasks;
    static std::vector<int> SplitDigits(std::string);
    void AddTask(const std::string &, TaskStat_Enum);
    void Check(std::string);
    void Begin(std::string);
    static void Find(const std::string &);
    static void Edit(std::string);
    void SendToArchive(Task);
    void Restore(std::string);
    static void Help();
    static void CopyToClipboard(std::string);
    static void Clear();
    void RemoveTask(std::string);
    void Star(std::string);
    void List(std::string);
    void IterateNotebooks(const std::set<std::string> &);
};