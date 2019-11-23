#include <string>
class Task;
class Notebook
{
public:
    static void ReadLabel(const std::string &);
    static std::vector<Task> notebookTasks;
    static void Edit(std::string);
    static void Star(std::string);
    static void Help_Notebook();

};