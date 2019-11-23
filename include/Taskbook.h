#include <string>
#include "Op_Enum.h"
#include <vector>
class Taskbook
{
private:
    static std::pair<Op_Enum, std::string> ParseInput(const std::string &);
    static void ManageCommand(const std::pair<Op_Enum, std::string> &);
    static bool ManageCommand_Notebook(const std::pair<Op_Enum, std::string> &, const std::string &label);
    static void SetPaths();

public:
    static std::string label;
    static std::string Trim(std::string);
    static bool success;
    static std::string aa;
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
