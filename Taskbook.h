#include <string>
#include "Op_Enum.h"
class Taskbook
{
private:
    static std::pair<Op_Enum, std::string> ParseInput(std::string);
    static void ManageCommand(const std::pair<Op_Enum, std::string> &);

public:
    static std::string Trim(std::string);
    static bool success;
    static bool fail;
    void ManageTaskbook();
    static std::string TakeInput();
};