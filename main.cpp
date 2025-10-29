#include <iostream>
#include <filesystem>
#include <fstream>
#include "json.hpp" // use quotes if json.hpp is in project folder
#include <cstdlib>

namespace fs = std::filesystem;
using json = nlohmann::json;

// Recursively walk the folder and save structure safely
json folder_to_json(const fs::path& path) {
    json j;
    try {
        for (auto& entry : fs::directory_iterator(path)) {
            try {
                if (fs::is_directory(entry.path())) {
                    j[entry.path().filename().string()] = folder_to_json(entry.path());
                } else if (fs::is_regular_file(entry.path())) {
                    j[entry.path().filename().string()] = "file";
                } else {
                    // For symlinks or special files
                    j[entry.path().filename().string()] = "special";
                }
            } catch (const fs::filesystem_error& e) {
                // Skip entries that cannot be read
                j[entry.path().filename().string()] = "unreadable";
            }
        }
    } catch (const fs::filesystem_error& e) {
        // If the top-level folder itself cannot be accessed
        j[path.filename().string()] = "unreadable";
    }
    return j;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./folder_viewer <folder_path>\n";
        return 1;
    }

    fs::path folder = argv[1];

    if (!fs::exists(folder) || !fs::is_directory(folder)) {
        std::cerr << "Invalid folder: " << folder << "\n";
        return 1;
    }

    json structure = folder_to_json(folder);

    // Save to temp JSON file
    fs::path json_path = "/Users/tapdiyaom/Desktop/DSA_Project/folder_structure.json";
    std::ofstream file(json_path);
    file << structure.dump(4);
    file.close();

    // Call Python GUI script safely with quotes to handle spaces
    fs::path py_path = "/Users/tapdiyaom/Desktop/DSA_Project/show_gui.py";
    std::string cmd = "/opt/homebrew/opt/python@3.9/libexec/bin/python3 \"" 
                      + py_path.string() + "\" \"" + json_path.string() + "\"";
    std::system(cmd.c_str());

    return 0;
}