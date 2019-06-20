#include <string>
#include "TaskStat_Enum.h"
class FileOperations
{
private:
    static const std::string dataPath;

public:
    static std::string ReturnStr(TaskStat_Enum);
    static void WriteToFile();
    static void ReadFromFile();
};