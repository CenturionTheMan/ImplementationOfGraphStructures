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

    bool Open(const std::string& path)
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

    bool IsOpen() const
    {
        return fileStream.is_open();
    }

    void Append(const std::string& text)
    {
        if (!IsOpen()) return;
        fileStream << text;
        fileStream.flush();
    }

    template <typename T>
    void AppendLineCSV(const std::vector<T>& line, char sep = ',')
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

    void Close()
    {
        if (IsOpen())
        {
            fileStream.close();
        }
    }

    void Clear()
    {
        if (!IsOpen()) return;

        fileStream.close();

        fileStream.open(filePath, std::ios::out | std::ios::trunc);

        fileStream.close();
        fileStream.open(filePath, std::ios::in | std::ios::out | std::ios::app);
    }

    ~FileManager()
    {
        Close();
    }
};