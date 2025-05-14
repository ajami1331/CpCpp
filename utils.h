#ifndef util_h
#define util_h 1

#include <filesystem>

#include "library/Common.h"
#include "library/StringUtils.h"

const int MAX_PATH = 256;

namespace utils {
const char* headerPrefix = "#include";
const string ifPrefix = "#ifdef CLown1331";
const string ifnPrefix = "#ifndef CLown1331";
const string elifPrefix = "#elif";
const string elsePrefix = "#else";
const string endifPrefix = "#endif";
const bool shouldSkipComment = true;
map<string, bool> visited;
vector<string> headers;
string content;

void Process(filesystem::path filePath);

bool IsComment(string line) {
  library::trim(line);
  return line.rfind("//") == 0 || line.rfind("///") == 0;
}

bool ProcessIncludes(string line, filesystem::path filePath) {
  auto tokens = library::split(line, ' ');
  auto tokensFiltered = vector<string>{};
  copy_if(begin(tokens), end(tokens), back_inserter(tokensFiltered),
          [](const string& s) -> bool { return !s.empty(); });
  if (tokensFiltered[1][0] == '<') {
    return false;
  }
  assert(tokensFiltered.size() == 2 &&
         "Should be in format {#include $library_name}");
  string includePath = tokensFiltered[1];
  includePath.pop_back();
  includePath.erase(0, 1);
  filesystem::path fpath = includePath;
  Process(filesystem::path(filePath).remove_filename().concat(fpath.string()));
  return true;
}

ifstream OpenInputAndValidate(string filePathString) {
  ifstream fstream(filePathString);
  char a, b, c;
  a = fstream.get();
  b = fstream.get();
  c = fstream.get();
  if (a != static_cast<char>(0xEF) || b != static_cast<char>(0xBB) ||
      c != static_cast<char>(0xBF)) {
    fstream.seekg(0);
  } else {
    cerr << "Warning: " + filePathString +
                " contains the so-called 'UTF-8 signature'\n";
  }

  return fstream;
}

void Process(filesystem::path filePath) {
  bool skipIfBlock = false;
  auto filePathString = filePath.string();
  if (visited[filePathString]) {
    return;
  }

  visited[filePathString] = true;
  ifstream fstream = OpenInputAndValidate(filePathString);
  string line;
  string skippedContent;
  while (getline(fstream, line)) {
    library::rtrim(line);
    if (library::trim_n(line).rfind(headerPrefix) == 0 &&
        ProcessIncludes(line, filePath)) {
      continue;
    }

    bool skip = false;

    if (line.empty()) {
      skip = true;
    }

    if (IsComment(line)) {
      skip = shouldSkipComment;
    }

    if (!library::trim_n(line).rfind(ifPrefix)) {
      skipIfBlock = true;
    }

    if (skipIfBlock && (!library::trim_n(line).rfind(endifPrefix) ||
                        !library::trim_n(line).rfind(elsePrefix) ||
                        !library::trim_n(line).rfind(elifPrefix))) {
      skip = true;
      if (!library::trim_n(line).rfind(elsePrefix)) {
        skippedContent.append(ifnPrefix + "\n");
      } else if (!library::trim_n(line).rfind(elifPrefix)) {
        skippedContent.append("#" + library::trim_n(line).erase(0, 3) + "\n");
      }
      skipIfBlock = false;
    }

    if (skipIfBlock) {
      skip = true;
    }

    if (skip) {
      continue;
    }

    skippedContent.append(line + "\n");
  }

  content.append(skippedContent);
  fstream.close();
}

void WriteFile(filesystem::path path) {
  ofstream out(
      filesystem::path(path).remove_filename().concat("submission.cpp"));
  sort(headers.begin(), headers.end());
  headers.resize(unique(headers.begin(), headers.end()) - headers.begin());
  for (const auto& header : headers) {
    out << header;
  }
  out << content;
  out.close();
}

void CreateFileForSubmission() {
  auto path = filesystem::path(STARTING_FILE);
  visited.clear();
  visited[filesystem::path(path).remove_filename().concat("utils.h").string()] =
      true;
  visited[filesystem::path(path)
              .remove_filename()
              .concat("validator.h")
              .string()] = true;
  content.clear();
  Process(path);
  WriteFile(path);
}
}  // namespace utils
#endif
