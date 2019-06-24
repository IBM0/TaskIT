#include <string>

//1 bolds
//2 fade
//3 italic
//4 underline
//5 blinks
//7 background
//8 invisible

class Color
{
private:
public:
    //reset
    static const std::string reset;

    //bolds
    static const std::string boldred;
    static const std::string boldgreen;
    static const std::string boldyellow;
    static const std::string boldcyan;
    static const std::string boldmagenta;
    static const std::string boldblack;
    static const std::string boldblue;
    static const std::string boldbright_red;
    static const std::string boldbright_green;
    static const std::string boldbright_yellow;
    static const std::string boldbright_cyan;
    static const std::string boldbright_magenta;
    static const std::string boldbright_black;
    static const std::string boldbright_blue;

    //normals
    static const std::string red;
    static const std::string green;
    static const std::string yellow;
    static const std::string cyan;
    static const std::string magenta;
    static const std::string black;
    static const std::string blue;
    static const std::string bright_red;
    static const std::string bright_green;
    static const std::string bright_yellow;
    static const std::string bright_cyan;
    static const std::string bright_magenta;
    static const std::string bright_black;
    static const std::string bright_blue;

    //fades
    static const std::string fadered;
    static const std::string fadegreen;
    static const std::string fadeyellow;
    static const std::string fadecyan;
    static const std::string fademagenta;
    static const std::string fadeblack;
    static const std::string fadeblue;
    static const std::string fadebright_red;
    static const std::string fadebright_green;
    static const std::string fadebright_yellow;
    static const std::string fadebright_cyan;
    static const std::string fadebright_magenta;
    static const std::string fadebright_black;
    static const std::string fadebright_blue;

    //underline
    static const std::string underlinefadebright_blue;
    static const std::string underlineboldbright_black;

    //blinks
    static const std::string blinkboldbright_red;
    static const std::string blinkboldbright_yellow;
};
