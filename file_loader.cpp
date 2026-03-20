#include "file_loader.h"
#include <fstream>

std::vector<std::string>& JotTextEditor::FileLoader::getLines() {
  return this->lines;
}

bool JotTextEditor::FileLoader::readFileIntoLines(const std::string &filename) {
  std::ifstream file(filename);
  if (!file) return false;

  this->lines.clear();
  std::string line;
  while (std::getline(file, line)) {
    this->lines.push_back(line);
  }
  return true;
}
