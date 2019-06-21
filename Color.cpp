#include <string>
#include "Color.h"

const std::string Color::reset = "\033[0m";

//bolds
const std::string Color::boldred = "\033[1;31m";
const std::string Color::boldgreen = "\033[1;32m";
const std::string Color::boldyellow = "\033[1;33m";
const std::string Color::boldcyan = "\033[1;36m";
const std::string Color::boldmagenta = "\033[1;35m";
const std::string Color::boldblack = "\033[1;30m";
const std::string Color::boldblue = "\033[1;34m";
const std::string Color::boldbright_red = "\033[1;91m";
const std::string Color::boldbright_green = "\033[1;92m";
const std::string Color::boldbright_yellow = "\033[1;93m";
const std::string Color::boldbright_cyan = "\033[1;96m";
const std::string Color::boldbright_magenta = "\033[1;95m";
const std::string Color::boldbright_black = "\033[1;90m";
const std::string Color::boldbright_blue = "\033[1;94m";

//normals
const std::string Color::red = "\033[0;31m";
const std::string Color::green = "\033[0;32m";
const std::string Color::yellow = "\033[0;33m";
const std::string Color::cyan = "\033[0;36m";
const std::string Color::magenta = "\033[0;35m";
const std::string Color::black = "\033[0;30m";
const std::string Color::blue = "\033[0;34m";
const std::string Color::bright_red = "\033[0;91m";
const std::string Color::bright_green = "\033[0;92m";
const std::string Color::bright_yellow = "\033[0;93m";
const std::string Color::bright_cyan = "\033[0;96m";
const std::string Color::bright_magenta = "\033[0;95m";
const std::string Color::bright_black = "\033[0;90m";
const std::string Color::bright_blue = "\033[0;94m";

//fades
const std::string Color::fadered = "\033[2;31m";
const std::string Color::fadegreen = "\033[2;32m";
const std::string Color::fadeyellow = "\033[2;33m";
const std::string Color::fadecyan = "\033[2;36m";
const std::string Color::fademagenta = "\033[2;35m";
const std::string Color::fadeblack = "\033[2;30m";
const std::string Color::fadeblue = "\033[2;34m";
const std::string Color::fadebright_red = "\033[2;91m";
const std::string Color::fadebright_green = "\033[2;92m";
const std::string Color::fadebright_yellow = "\033[2;93m";
const std::string Color::fadebright_cyan = "\033[2;96m";
const std::string Color::fadebright_magenta = "\033[2;95m";
const std::string Color::fadebright_black = "\033[2;90m";
const std::string Color::fadebright_blue = "\033[2;94m";

//underline
const std::string Color::underlinefadebright_blue = "\033[4;94m";
const std::string Color::underlineboldbright_black = "\033[4;90m";

//blinks
const std::string Color::blinkboldbright_red = "\033[5;91m";
const std::string Color::blinkboldbright_yellow = "\033[5;93m";