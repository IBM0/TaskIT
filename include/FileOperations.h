#include <string>
#include "TaskStat_Enum.h"
class Task;
class FileOperations
{
private:
public:
    static std::string ReturnStr(TaskStat_Enum stat);
    static void WriteToFile(const std::vector<Task> & , const std::string &);
    static void ReadFromFile(std::vector<Task> & , const std::string &);
};