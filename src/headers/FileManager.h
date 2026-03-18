#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <type_traits>

class FileManager
{
private:
    std::fstream fileStream;
    std::string filePath;

public:
    FileManager() = default;
    ~FileManager();

    bool Open(const std::string& path);
    bool IsOpen() const;
    void Append(const std::string& text);
    void AppendLineCSV(const std::vector<std::string>& line, char sep = ',');
    void Close();
    void Clear();

};