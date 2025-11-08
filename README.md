# 🗂️ Folder Structure Visualizer  

### ⚡ C++ × Python × PyQt5 × macOS Automator  

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=for-the-badge&logo=c%2B%2B">
  <img src="https://img.shields.io/badge/GUI-PyQt5-3776AB?style=for-the-badge&logo=python">
  <img src="https://img.shields.io/badge/OS-macOS-333333?style=for-the-badge&logo=apple">
  <img src="https://img.shields.io/badge/License-MIT-FDEA02?style=for-the-badge">
</p>

<p align="center">
  Instantly visualize any folder’s structure in an interactive GUI — right from your Finder context menu.
</p>

---

## ✨ Overview

The Folder Structure Visualizer is a hybrid utility combining the speed of C++ with the power of Python’s PyQt5 framework. It recursively scans any folder and displays its complete hierarchy in a clean, interactive tree-view interface.

🖱️ With macOS Automator integration, you can right-click any folder → Quick Actions → Show Folder Structure to instantly open its visual map.

---

## 🚀 Features

- ⚡ Fast recursive traversal using C++17 `<filesystem>`
- 🧠 Structured JSON output with `nlohmann/json`
- 🪟 Expandable GUI built on PyQt5 `QTreeView`
- 🧩 Finder Quick Action support through Automator
- 🔒 Handles unreadable files and special symbolic links safely
- 🧰 Seamless bridge between C++ backend and Python frontend

---

## 🧱 Architecture Overview

graph TD;
A[Finder Right Click: Quick Action] --> B[Automator Shell Script];
B --> C[Terminal launches folder_viewer];
C --> D[main.cpp - C++ Scanner];
D --> E[folder_structure.json];
E --> F[show_gui.py - Python GUI];
F --> G[PyQt5 TreeView Window];



---

## 📂 Project Structure

📦 Folder Structure Visualizer
├── main.cpp # Core folder scanning and JSON export logic
├── show_gui.py # Python GUI built with PyQt5
├── json.hpp # nlohmann/json header library
├── folder_structure.json # Auto-generated output file
└── Automator.sh # Automator workflow shell script


---

## ⚙️ Installation & Setup

### 1️⃣ Prerequisites

| Requirement | Description |
|--------------|-------------|
| C++17+ | Required for `<filesystem>` support |
| Python 3.9+ | For running the PyQt5 interface |
| PyQt5 | Install via `pip3 install PyQt5` |
| nlohmann/json | Included as `json.hpp` |

---

### 2️⃣ Compile the C++ Executable

cd /Users/tapdiyaom/Desktop/DSA_Project
clang++ -std=c++17 main.cpp -o folder_viewer



---

### 3️⃣ macOS Automator Integration

1. Open **Automator.app → New → Quick Action**  
2. Configure:
   - Workflow receives: files or folders in Finder  
   - Action: Run Shell Script
3. Paste this snippet:
for f in "$@"; do
osascript -e "tell application "Terminal" to do script "/Users/tapdiyaom/Desktop/DSA_Project/folder_viewer '$f'""
done


4. Save as **Show Folder Structure**

Now right-click any folder → Quick Actions → Show Folder Structure 🎨

---

## 🧩 Core Code Highlights

### 🔹 Recursive Folder Parser (C++)

json folder_to_json(const fs::path& path) {
json j;
for (auto& entry : fs::directory_iterator(path)) {
if (fs::is_directory(entry.path()))
j[entry.path().filename().string()] = folder_to_json(entry.path());
else if (fs::is_regular_file(entry.path()))
j[entry.path().filename().string()] = "file";
else
j[entry.path().filename().string()] = "special";
}
return j;
}



### 🔹 GUI Builder (Python)

def build_tree(parent, data):
for key, value in data.items():
item = QStandardItem(key)
parent.appendRow(item)
if isinstance(value, dict):
build_tree(item, value)



---

## 💻 Example Output

### 🧩 Terminal Execution

./folder_viewer ~/Projects/MyApp


### 🎨 GUI Display

📁 MyApp
┣ 📂 src
┃ ┣ 📜 main.cpp
┃ ┣ 📜 utils.cpp
┣ 📂 include
┃ ┗ 📜 utils.h
┗ 📜 README.md



---

## 🧠 Error Handling

| Case | Handling |
|-------|-----------|
| Invalid folder | Prints usage information |
| Permission denied | Marked as unreadable |
| Symbolic link | Marked as special |
| Non-directory input | Skipped gracefully |

---

## 🛠️ Optional Build Using CMake

cmake_minimum_required(VERSION 3.10)
project(FolderVisualizer)
set(CMAKE_CXX_STANDARD 17)
add_executable(folder_viewer main.cpp)



Then:

mkdir build && cd build
cmake ..
make



---

## 🌟 Future Improvements

- Add dark and light theme modes  
- Add search functionality  
- Display file sizes and types  
- Package as standalone `.app` using PyInstaller  

---

## 📜 License

Licensed under the MIT License. Refer to the LICENSE file for more details.

---

## 👨‍💻 Author

Om Tapdiya  
System Design & Automation Enthusiast  
📫 omtapdiya75@gmail.com  

<p align="center">
  ⭐ If you find this project helpful, give it a star!  
  <br>Crafted with ❤️ by Om Tapdiya
</p>