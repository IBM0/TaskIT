#include <string>
class FileOperations
{
private:
    static const std::string dataPath;

public:
    static void WriteToFile();
    static void ReadFromFile();
};