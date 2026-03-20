#include "file_loader.h"
#include <fstream>

std::vector<std::wstring>& JotTextEditor_UI::FileLoader::getLines() {
  return this->lines;
}

bool JotTextEditor_UI::FileLoader::readFileIntoLines(const std::wstring &filename) {
  std::wifstream file(filename.c_str());
  if (!file) return false;

  lines.clear();
  std::wstring line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  return true;
}
