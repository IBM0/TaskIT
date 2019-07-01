#include <string>

//1 bolds
//2 fade
//3 italic
//4 underline
//5 blinks
//7 background
//8 invisible
static const std::string reset = "\033[0m";

//bolds
static const std::string boldred = "\033[1;31m";
static const std::string boldgreen = "\033[1;32m";
static const std::string boldyellow = "\033[1;33m";
static const std::string boldcyan = "\033[1;36m";
static const std::string boldmagenta = "\033[1;35m";
static const std::string boldblack = "\033[1;30m";
static const std::string boldblue = "\033[1;34m";
static const std::string boldbright_red = "\033[1;91m";
static const std::string boldbright_green = "\033[1;92m";
static const std::string boldbright_yellow = "\033[1;93m";
static const std::string boldbright_cyan = "\033[1;96m";
static const std::string boldbright_magenta = "\033[1;95m";
static const std::string boldbright_black = "\033[1;90m";
static const std::string boldbright_blue = "\033[1;94m";

//normals
static const std::string red = "\033[0;31m";
static const std::string green = "\033[0;32m";
static const std::string yellow = "\033[0;33m";
static const std::string cyan = "\033[0;36m";
static const std::string magenta = "\033[0;35m";
static const std::string black = "\033[0;30m";
static const std::string blue = "\033[0;34m";
static const std::string bright_red = "\033[0;91m";
static const std::string bright_green = "\033[0;92m";
static const std::string bright_yellow = "\033[0;93m";
static const std::string bright_cyan = "\033[0;96m";
static const std::string bright_magenta = "\033[0;95m";
static const std::string bright_black = "\033[0;90m";
static const std::string bright_blue = "\033[0;94m";

//fades
static const std::string fadered = "\033[2;31m";
static const std::string fadegreen = "\033[2;32m";
static const std::string fadeyellow = "\033[2;33m";
static const std::string fadecyan = "\033[2;36m";
static const std::string fademagenta = "\033[2;35m";
static const std::string fadeblack = "\033[2;30m";
static const std::string fadeblue = "\033[2;34m";
static const std::string fadebright_red = "\033[2;91m";
static const std::string fadebright_green = "\033[2;92m";
static const std::string fadebright_yellow = "\033[2;93m";
static const std::string fadebright_cyan = "\033[2;96m";
static const std::string fadebright_magenta = "\033[2;95m";
static const std::string fadebright_black = "\033[2;90m";
static const std::string fadebright_blue = "\033[2;94m";

//underline
static const std::string underlinefadebright_blue = "\033[4;94m";
static const std::string underlineboldbright_black = "\033[4;90m";
