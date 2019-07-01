#include "TaskStat_Enum.h"
class Task
{
private:
public:
    int number;
    TaskStat_Enum stat;
    std::string name;
    bool starred;
    std::string notebook;
};