#include <string>
#include "Op_Enum.h"
#include <vector>
class Taskbook
{
private:
    static std::pair<Op_Enum, std::string> ParseInput(std::string);
    static void ManageCommand(const std::pair<Op_Enum, std::string> &);
    static bool ManageCommand_Notebook(const std::pair<Op_Enum, std::string> &, const std::string &label);
    static void SetPaths();
    static std::string label;

public:
    static std::string Trim(std::string);
    static bool success;
    static bool print;
    static bool fail;
    static std::string fall_back;
    void Startexe();
    Taskbook()
    {
        Startexe();
    };
    void ManageTaskbook();
    void ManageTaskbook(const std::string);
    static std::string TakeInput();
};
