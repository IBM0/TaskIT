#include <string>
#include "Op_Enum.h"
class Taskbook
{
private:
    static std::pair<Op_Enum, std::string> ParseInput(std::string);
    static void ManageCommand(const std::pair<Op_Enum, std::string> &);
    static void SetPaths();

public:
    static std::string Trim(std::string);
    static bool success;
    static bool print;
    static bool fail;
    void ManageTaskbook();
    static std::string TakeInput();
};
