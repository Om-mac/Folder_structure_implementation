#!/usr/bin/env python3
import sys, json
from PyQt5.QtWidgets import QApplication, QTreeView, QVBoxLayout, QWidget
from PyQt5.QtGui import QStandardItemModel, QStandardItem

def build_tree(parent, data):
    for key, value in data.items():
        item = QStandardItem(key)
        parent.appendRow(item)
        if isinstance(value, dict):
            build_tree(item, value)

def show(json_file):
    with open(json_file, 'r') as f:
        data = json.load(f)

    app = QApplication(sys.argv)
    window = QWidget()
    window.setWindowTitle("om's Project")
    window.resize(700, 500)

    layout = QVBoxLayout()
    model = QStandardItemModel()
    model.setHorizontalHeaderLabels(['Folder Tree'])
    build_tree(model.invisibleRootItem(), data)

    tree_view = QTreeView()
    tree_view.setModel(model)
    tree_view.expandAll()
    layout.addWidget(tree_view)

    window.setLayout(layout)
    window.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: show_gui.py <json_file>")
    else:
        show(sys.argv[1])