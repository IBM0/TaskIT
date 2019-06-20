#include "Task.h"
#include <vector>
class Print
{
private:
public:
    static void PrintTasks();
    static void PrintBody(const std::vector<Task> &);
    static void PrintArchive();
    // static void PrintSearch();
    static void CountVector();
    static int doneCount;
    static int undoneCount;
    static int inprogress;
    static int note;
    static int size;
};