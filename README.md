# 🗂️ Folder Structure Visualizer  
### ⚡ C++ × Python × PyQt5 × macOS Automator  

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B17-blue?style=for-the-badge&logo=c%2B%2B">
  <img src="https://img.shields.io/badge/GUI-PyQt5-brightgreen?style=for-the-badge&logo=python">
  <img src="https://img.shields.io/badge/OS-macOS-lightgrey?style=for-the-badge&logo=apple">
  <img src="https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge">
</p>

<p align="center">
  <b>Instantly visualize any folder’s structure in an interactive GUI — right from your Finder context menu.</b>
</p>

---

## ✨ Overview

The **Folder Structure Visualizer** is a hybrid tool that combines the **speed of C++** and the **power of Python (PyQt5)** to recursively map and display any folder hierarchy in an elegant, interactive GUI.

🖱️ Integrated with macOS **Automator**, you can simply **right-click any folder → Quick Actions → Show Folder Structure** and see your directory tree appear instantly!

---

## 🚀 Features

- ⚡ **Fast Recursive Scan** — Uses C++17 `<filesystem>` for efficient traversal  
- 🧠 **JSON Export** — Uses [`nlohmann/json`](https://github.com/nlohmann/json) for safe and structured data handling  
- 🪟 **Interactive GUI** — Built with PyQt5’s `QTreeView` for an expandable tree display  
- 🧩 **Finder Integration** — Launch from Finder context menu via Automator  
- 🔒 **Error Safe** — Handles unreadable files, permissions, and symbolic links gracefully  
- 🧰 **Cross-Language Power** — C++ backend + Python frontend = seamless experience  

---

## 🧱 Architecture Overview

```mermaid
graph TD;
    A[Finder Right Click: Quick Action] --> B[Automator Shell Script];
    B --> C[Terminal launches folder_viewer];
    C --> D[main.cpp - C++ Scanner];
    D --> E[folder_structure.json];
    E --> F[show_gui.py - Python GUI];
    F --> G[PyQt5 TreeView Window];

📂 Project Structure
📦 Folder Structure Visualizer  
├── main.cpp                 # C++17 core logic - folder scanning & JSON creation
├── show_gui.py              # Python GUI viewer (PyQt5)
├── json.hpp                 # nlohmann/json library (single header)
├── folder_structure.json    # Auto-generated output file
└── Automator.sh             # Automator workflow shell script


⚙️ Installation & Setup

1️⃣ Prerequisites
Requirement
Description
🧠 C++17+
For <filesystem> support
🐍 Python 3.9+
To run the PyQt5 GUI
💡 PyQt5
Install using pip3 install PyQt5
⚙️ nlohmann/json


2️⃣ Compile the C++ Executable
cd /Users/tapdiyaom/Desktop/DSA_Project
clang++ -std=c++17 main.cpp -o folder_viewer

3️⃣ macOS Automator Integration
	1.	Open Automator.app → Create Quick Action
	2.	Set:
	•	Workflow receives → files or folders in Finder
	•	Action → Run Shell Script
	3.	Paste this code:
    for f in "$@"; do
    osascript -e "tell application \"Terminal\" to do script \"/Users/tapdiyaom/Desktop/DSA_Project/folder_viewer '$f'\""
    done
    4.	Save as “Show Folder Structure”
    Now you can right-click any folder → Quick Actions → Show Folder Structure 🎨


🧩 Code Highlights

🔹 Recursive Folder Parser (C++)

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

🔹 GUI Builder (Python)

def build_tree(parent, data):
    for key, value in data.items():
        item = QStandardItem(key)
        parent.appendRow(item)
        if isinstance(value, dict):
            build_tree(item, value)


💻 Example Output

🧩 Terminal Command

./folder_viewer ~/Projects/MyApp

🎨 GUI Tree Output

📁 MyApp
 ┣ 📂 src
 ┃ ┣ 📜 main.cpp
 ┃ ┣ 📜 utils.cpp
 ┣ 📂 include
 ┃ ┗ 📜 utils.h
 ┗ 📜 README.md


🧠 Error Handling
Case
Handling
Invalid folder
Prints usage message
Permission denied
Marked as "unreadable"
Symbolic link
Marked as "special"
Non-directory input
Skipped safely


🧩 Optional: Build with CMake

cmake_minimum_required(VERSION 3.10)
project(FolderVisualizer)
set(CMAKE_CXX_STANDARD 17)
add_executable(folder_viewer main.cpp)

Then:

mkdir build && cd build
cmake ..
make


🌟 Future Improvements
	•	Add Dark/Light mode for GUI
	•	Add Search bar
	•	Show file sizes & types
	•	Package as .app with PyInstaller


📜 License

This project is licensed under the MIT License — see LICENSE￼ for details.

⸻
👨‍💻 Author

Om Tapdiya
💻 System Design & Automation Enthusiast
📫 omtapdiya75@gmail.com￼


<p align="center">
  ⭐ If you found this project useful, give it a star!  
  <br>Made with ❤️ by <b>Om Tapdiya</b>
</p>
```
