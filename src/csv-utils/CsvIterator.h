#pragma once

#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>

class CsvIterator
{
  private:
    bool m_hasNext;
    std::vector<std::string> m_tokens;
    FILE *m_file;
    std::string m_delimiter;
    std::string m_readLine();
    std::vector<std::string> m_tokenizer(const char *s);
    void m_getNextElement();

  public:
    CsvIterator(const std::string &path,
                const std::string &delimiter,
                bool skipHeader);
    ~CsvIterator();

    bool hasNext();
    std::vector<std::string> next();
};