#include <string>
#include <vector>
#include "Print.h"
class Operations
{
private:
    int GetNewNum();
    int GetNewNumArchive();

public:
    static std::vector<Task> Tasks;
    static std::vector<Task> ArchiveTasks;
    std::vector<int> SplitDigits(std::string);
    void AddTask(std::string, TaskStat_Enum);
    void Check(std::string);
    void Begin(std::string);
    void Find(std::string);
    void Edit(std::string);
    void SendToArchive(Task);
    void Restore(std::string);
    void Help();
    static void Clear();
    void RemoveTask(std::string);
};