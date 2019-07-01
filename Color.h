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
static const std::string boldyellow = "\033[1;92m";
static const std::string boldblue = "\033[1;93m";
static const std::string boldmagenta = "\033[1;96m";
static const std::string boldbrightblue = "\033[1;95m";
static const std::string boldgray = "\033[1;90m";
static const std::string boldorange = "\033[1;94m";
static const std::string boldred = "\033[1;91m";

//normals
static const std::string orange = "\033[0;94m";
static const std::string yellow = "\033[0;92m";
static const std::string blue = "\033[0;93m";
static const std::string magenta = "\033[0;96m";
static const std::string brightblue = "\033[0;95m";
static const std::string gray = "\033[0;90m";
static const std::string underLinebrightblue = "\033[4;95m";
static const std::string underLinemagenta = "\033[4;96m";