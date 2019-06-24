#include <string>
#include <vector>
#include "Print.h"
class Operations
{
private:
    static int GetNewNum();
    static int GetNewNumArchive();

public:
    static std::vector<Task> Tasks;
    static std::vector<Task> ArchiveTasks;
    static std::vector<int> SplitDigits(std::string);
    void AddTask(const std::string&, TaskStat_Enum);
    void Check(std::string);
    void Begin(std::string);
    static void Find(const std::string&);
    static void Edit(std::string);
    void SendToArchive(Task);
    void Restore(std::string);
    static void Help();
    static void Clear();
    void RemoveTask(std::string);
};