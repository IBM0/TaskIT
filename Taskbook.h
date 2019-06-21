#include <string>
#include "Op_Enum.h"
class Taskbook
{
private:
    std::pair<Op_Enum, std::string> ParseInput(std::string);
    void ManageCommand(const std::pair<Op_Enum, std::string> &);

public:
    static std::string Trim(std::string);
    static bool success;
    static bool fail;
    void ManageTaskbook();
    static std::string TakeInput();
};