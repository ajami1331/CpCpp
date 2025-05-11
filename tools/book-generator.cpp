#define _CRT_SECURE_NO_WARNINGS

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
namespace fs = filesystem;

vector<string> getFiles(string path) {
  vector<string> files;
  for (const auto& entry : fs::recursive_directory_iterator(path)) {
    if (entry.is_regular_file() && entry.path().has_extension()) {
      files.emplace_back(entry.path().string());
    }
  }
  return files;
}

void encode(string& data) {
  string buffer;
  buffer.reserve(data.size());
  for (size_t pos = 0; pos != data.size(); ++pos) {
    switch (data[pos]) {
      case '&':
        buffer.append("&amp;");
        break;
      case '\"':
        buffer.append("&quot;");
        break;
      case '\'':
        buffer.append("&apos;");
        break;
      case '<':
        buffer.append("&lt;");
        break;
      case '>':
        buffer.append("&gt;");
        break;
      default:
        buffer.append(&data[pos], 1);
        break;
    }
  }
  data.swap(buffer);
}

int main(int argc, char* argv[]) {
  auto files = getFiles(CP_LIBRARY_PATH);
  string highlightjsVersion = "11.8.0";
  string header =
      string("") + "<!DOCTYPE html>\n" + "<html>\n" + "    <head>\n" +
      "    <meta charset=\"utf-8\">\n" +
      "    <meta name=\"viewport\" content=\"width=device-width\">\n" +
      "    <title>Algorithms</title>\n" +
      "    <link rel=\"stylesheet\" "
      "href=\"https://cdnjs.cloudflare.com/ajax/libs/highlight.js/" +
      highlightjsVersion + "/styles/default.min.css\">\n" +
      "    <script src=\"https://cdnjs.cloudflare.com/ajax/libs/highlight.js/" +
      highlightjsVersion + "/highlight.min.js\"></script>\n" +
      "    <script src=\"https://cdnjs.cloudflare.com/ajax/libs/highlight.js/" +
      highlightjsVersion + "/languages/go.min.js\"></script>\n" +
      "    <script>hljs.highlightAll();</script>\n" + "    </head>\n" +
      "<body>\n";
  string footer = "</body></html>";
  fs::remove_all(TOOLS_BOOK_GENERATOR_OUT_DIR);
  fs::create_directory(TOOLS_BOOK_GENERATOR_OUT_DIR);
  string output_file_name =
      string("") + TOOLS_BOOK_GENERATOR_OUT_DIR + "index.html";
  ofstream outFile;
  cout << "Writing to " << output_file_name << endl;
  outFile.open(output_file_name);
  outFile << header;
  outFile << "<h1>Algorithms</h1>\n";
  outFile << "<h2>Github: <a "
             "href=\"https://github.com/ajami1331/CpCpp/tree/main/"
             "library\">ajami1331/CpCpp</a></h2>\n";
  outFile << "<h2 id=\"table-of-content\">Table of Contents</h2>\n";
  outFile << "<ul>\n";
  for (auto file : files) {
    fs::path path(file);
    string filename = path.filename().string();
    outFile << "<li><a href=\"#" + filename + "\">" + filename + "</a></li>\n";
  }
  outFile << "</ul>\n";
  for (auto file : files) {
    fs::path path(file);
    string filename = path.filename().string();
    outFile << "<h2 id=\"" + filename + "\">" + filename + "</h2>\n";
    outFile << "<a href=\"#table-of-content\">^top</a>\n";
    outFile << "<pre><code>\n";
    ifstream t(file);
    string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
    encode(str);
    outFile << str;
    outFile << "</code></pre>\n";
  }
  outFile << footer;
  return 0;
}