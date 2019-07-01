#include "Task.h"
#include <vector>
class Print
{
private:
public:
    static void PrintTasks(const std::vector<Task> &vec, bool, std::string);
    static void PrintBody(const std::vector<Task> &,bool);
    static void PrintArchive();
    static void CountVector(const std::vector<Task> &);
    static int doneCount;
    static int undoneCount;
    static int inprogress;
    static int note;
    static int size;
};