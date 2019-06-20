#include <string>
class ArchiveFileOperations
{
private:
public:
    static const std::string ArchivePath;
    static void WriteArchive();
    static void ReadArchive();
};