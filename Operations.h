#include <string>
#include <vector>
#include "Task.h"
class Operations
{
private:
    int GetNewNum();

public:
    static std::vector<Task> Tasks;
    void AddTask(std::string, TaskStat_Enum);
    void Check(std::string);
    void Begin(std::string);
    void Edit(std::string);
    void Help();
    std::vector<int> SplitDigits(std::string);
    void RemoveTask(std::string);
};