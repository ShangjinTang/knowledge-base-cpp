#pragma once

#include <memory>
#include <string>
#include <vector>
namespace Loadable {

class File {
private:
    std::string path;
    std::string name;

public:
    File(std::string path, std::string name) : path(path), name(name) {}
    std::string getFullName() {
        return path + "/" + name;
    }
};

class SearchPath {
public:
    static const constexpr char *SEPARATOR = ":";

private:
    std::string path;
    std::vector<std::string> parsedPath;

    void parsePath() {
        size_t start = 0;
        size_t end = 0;
        for (start = 0; start != std::string::npos; start = end) {
            end = path.find(SEPARATOR, start);
            std::string tmp(path, start, end - start);
            if (tmp.size() > 0) {
                parsedPath.push_back(tmp);
            }
        }
    }

public:
    // platform specific
    static bool fileAccessible(std::string path, std::string filename);
    SearchPath(std::string path) : path(path) {
        parsePath();
    }

    std::shared_ptr<File> findFile(std::string filename) {
        for (std::string currpath : parsedPath) {
            if (fileAccessible(currpath, filename)) {
                return std::make_shared<File>(currpath, filename);
            }
        }
        return nullptr;
    }
};

}  // namespace Loadable
