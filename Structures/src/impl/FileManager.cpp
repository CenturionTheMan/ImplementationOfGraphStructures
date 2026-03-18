#include "FileManager.h"


FileManager::~FileManager()
{
    Close();
}


bool FileManager::Open(const std::string& path)
{
    filePath = path;
    fileStream.open(filePath, std::ios::in | std::ios::out | std::ios::app);
    if (!fileStream.is_open())
    {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return false;
    }
    return true;
}

bool FileManager::IsOpen() const
{
    return fileStream.is_open();
}

void FileManager::Append(const std::string& text)
{
    if (!IsOpen()) return;
    fileStream << text;
    fileStream.flush();
}

void FileManager::AppendLineCSV(const std::vector<std::string>& line, char sep)
{
    if (!IsOpen()) return;

    std::ostringstream ss;

    for (size_t i = 0; i < line.size(); ++i) {
        ss << line[i];
        if (i != line.size() - 1)
            ss << sep;
    }

    ss << '\n';
    fileStream << ss.str();
    fileStream.flush();
}

void FileManager::Close()
{
    if (IsOpen())
    {
        fileStream.close();
    }
}

void FileManager::Clear()
{
    if (!IsOpen()) return;

    fileStream.close();

    fileStream.open(filePath, std::ios::out | std::ios::trunc);

    fileStream.close();
    fileStream.open(filePath, std::ios::in | std::ios::out | std::ios::app);
}
