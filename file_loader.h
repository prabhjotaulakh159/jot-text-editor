#include <vector>
#include <string>

namespace JotTextEditor_UI {
  class FileLoader {
    private:
      std::vector<std::wstring> lines;
    
    public:
      std::vector<std::wstring>& getLines();
      bool readFileIntoLines(const std::wstring& filename);
  };
};