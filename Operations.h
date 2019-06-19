#include<string>
#include<vector>
#include "Task.h"
class Operations
{
    private:
    
    public:
    void AddTask(std::string);
    static std::vector<Task> Tasks;
    void RemoveTask(std::string);
    
};