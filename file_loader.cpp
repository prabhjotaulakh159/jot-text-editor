#include "file_loader.h"
#include <fstream>

std::vector<std::wstring>& JotTextEditor::FileLoader::getLines() {
  return this->lines;
}

bool JotTextEditor::FileLoader::readFileIntoLines(const std::wstring &filename) {
  std::wifstream file(filename.c_str());
  if (!file) return false;

  this->lines.clear();
  std::wstring line;
  while (std::getline(file, line)) {
    this->lines.push_back(line);
  }
  return true;
}
