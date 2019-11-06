#include <iostream>
#include "Taskbook.h"
#include "Color.h"
using namespace std;
int main(int argc, char *argv[])
{
    Taskbook tb;
    std::cout << std::endl;
    if (argc == 1)
        tb.ManageTaskbook();
    else
        tb.ManageTaskbook(argv[1]);
    while (true)
    {
        if (Taskbook::fall_back == "exit")
            return 0;

        else if (Taskbook::fall_back == "default")
            tb.ManageTaskbook();

        else
        {
            std::string new_notebook = Taskbook::fall_back;
            Taskbook::fall_back = "";
            tb.ManageTaskbook(std::move(new_notebook));
        }
    }

    return 0;
}