#include <vector>
#include <string>

namespace JotTextEditor_IO {
  class FileLoader {
    private:
      std::vector<std::wstring> lines;
    
    public:
      std::vector<std::wstring>& getLines();
      bool readFileIntoLines(const std::wstring& filename);
  };
};