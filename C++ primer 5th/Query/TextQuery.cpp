#include "TextQuery.h"

TextQuery::TextQuery(std::fstream& is) : file(/*new std::vector<std::string>*/)
{
    std::string text;
    while (std::getline(is, text))
    {
        file.push_back(text);
        int n = file.size() - 1;
        std::istringstream line(text);

        printf("%s.\n", text.c_str());
        std::string word;
        while (line >> word)
        {
            auto &lines = wm[word];
            if (!lines)
                lines.reset(new std::set<line_no>);
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const std::string & sought) const
{
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto loc = wm.find(sought);
    if (loc == wm.end())
    {
        return QueryResult(sought, nodata, file);
    }
    else
    {
        return QueryResult(sought, loc->second, file); //返回查询的单词, 单词所在的所有行, 以及所有文本的指针
    }
}