#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <fstream>
#include <sstream>

#include "str_blob.h"

class QueryResult;

class TextQuery
{
    //friend class QueryResult;
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::fstream& is);
    QueryResult query(const std::string & sought) const;

private:
    StrBlob file;
    //std::shared_ptr<std::vector<std::string>> file;   //总的内容
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;  // 统计每个单词的所在的所有行数
};

class QueryResult
{
    friend std::ostream& print(std::ostream &, const QueryResult&);
public:
    QueryResult(std::string s,
        std::shared_ptr<std::set<TextQuery::line_no>> p,
        /*std::shared_ptr<std::vector<std::string>>*/StrBlob f) :
        sought(s), lines(p), file(f)  { }

    std::set<TextQuery::line_no>::iterator begin()
    {
        return lines->begin();
    }
    std::set<TextQuery::line_no>::iterator end()
    {
        return lines->end();
    }
    StrBlob get_line()
    {
        return file;
    }

private:
    std::string sought;
    std::shared_ptr<std::set<TextQuery::line_no>> lines;
    StrBlob file;
    //std::shared_ptr<std::vector<std::string>> file;
};
