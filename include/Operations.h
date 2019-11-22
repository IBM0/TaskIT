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
    static std::vector<Task> notebookTasks;
    static std::vector<Task> ArchiveTasks;
    static std::vector<int> SplitDigits(std::string);
    void AddTask(const std::string &, TaskStat_Enum, const std::string &label = "");
    void Check(std::string);
    void Begin(std::string);
    static void Find(const std::string &);
    static void Edit(std::string);
    static void Move(std::string);
    void Edit_inNotebook(std::string);
    static bool is_number(const std::string& s);
    static void Swit(const std::string &);
    void SendToArchive(Task);
    void Restore(std::string);
    static void Help();
    static void Help_Notebook();
    static void CopyToClipboard(std::string);
    static void Clear();
    void RemoveTask(std::string);
    void Star(std::string);
    void List(std::string);
    void IterateNotebooks(const std::set<std::string> &);
};