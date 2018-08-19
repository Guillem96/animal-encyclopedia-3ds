#include "CsvIterator.h"

CsvIterator::CsvIterator(const std::string &path, const std::string &delimiter) : m_delimiter(delimiter)
{
    m_file = fopen((char *)path.c_str(), "r");
    if (m_file)
    {
        printf("Reading %s\n", path.c_str());
        std::string nextLine = m_readLine();
        if(m_hasNext)
            m_tokens = m_tokenizer(nextLine.c_str());
    }
    else
    {
        m_hasNext = false;
        printf("Error opening %s\n", path.c_str());
    }
}

CsvIterator::~CsvIterator() {}

bool CsvIterator::hasNext()
{
    return m_hasNext;
}

std::vector<std::string> CsvIterator::next()
{
    std::vector<std::string> currentTokens = m_tokens;

    if (!m_hasNext)
    {
        // TODO: Throw exception
    }
    else
    {
        // Step further
        std::string nextLine = m_readLine();
        if(m_hasNext)
            m_tokens = m_tokenizer(nextLine.c_str());    }

    return currentTokens;
}

std::string CsvIterator::m_readLine()
{
    char line[512];

    if (fgets(line, sizeof(line), m_file) != NULL)
        m_hasNext = true;
    else
        m_hasNext = false;

    if (feof(m_file))
    {
        m_hasNext = false;
    }

    line[strlen(line) - 1] = '\0';

    std::string result(line);
    return result;
}

std::vector<std::string> CsvIterator::m_tokenizer(const char *s)
{
    std::vector<std::string> tokens;
    char *token;

    token = strtok((char *)s, (char *)m_delimiter.c_str());

    while (token != NULL)
    {
        std::string tokenStr(token);
        tokens.push_back(tokenStr);
        token = strtok(NULL, (char *)m_delimiter.c_str());
    }

    return tokens;
}
