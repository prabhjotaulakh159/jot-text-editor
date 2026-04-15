# Jot Text Editor

A small toy text editor built on the windows api (windows.h). 

## Features: 
- Open a file and output it's content on the editor
- Save a file and choose where to do so
- Validate before exiting

## How to compile

Using the MinGW Compiler: 
```code
g++ main.cpp file_loader.cpp app_state.cpp -o editor.exe -lComdlg32
```