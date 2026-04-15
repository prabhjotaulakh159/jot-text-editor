#include <vector>
#include <string>

class FileLoader {
  private:
    std::vector<std::wstring> lines;
  
  public:
    std::vector<std::wstring>& getLines();
    bool readFileIntoLines(const std::wstring& filename);
    bool dumpContentIntoFile(const std::wstring& content, const std::wstring& filename);
};
