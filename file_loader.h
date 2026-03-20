#include <vector>
#include <string>

namespace JotTextEditor {
  class FileLoader {
    private:
      std::vector<std::string> lines;
    
    public:
      std::vector<std::string>& getLines();
      bool readFileIntoLines(const std::string& filename);
  };
};