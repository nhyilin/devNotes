//
// Created by 裴奕霖 on 2023/4/21.
//

#ifndef MARKDOWN2LATEX__MDFILE_H_
#define MARKDOWN2LATEX__MDFILE_H_

class MdFile {
 public:
  MdFile() = delete;
  MdFile(std::string file_path);

  ~MdFile();
 private:
  std::string path;
  std::string content;

  struct CodeBlock {
    std::string language;
    std::string content;
  };

  struct Enumerate_Num {
    std::string content;
    int num;//start from 1
  };

  struct Enumerate_None {
    std::string content;
    int index;//start from 1
  };

};

#endif //MARKDOWN2LATEX__MDFILE_H_
