#pragma  once

#include <string>
#include <memory>

#include "TextQuery.h"

//class Query;
class Query_base
{
    friend class Query;
protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;

private:
    virtual QueryResult eval(const TextQuery&) const = 0;
    virtual std::string rep() const = 0;

};

class WordQuery : public Query_base
{
    friend class Query;
    WordQuery(const std::string &s) : query_word(s) {}

    QueryResult eval(const TextQuery &t) const
    {
        return t.query(query_word);
    }
    std::string rep() const
    {
        return query_word;
    }
    std::string query_word;
};

// 讲层级关系隐藏于接口类中
// 对外提供接口, 隐藏Query_base继承体系
class WordQuery;
class Query
{
    // 这几个重载运算符才是神来之笔
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const std::string &s) : q(new WordQuery(s)) {}
    QueryResult eval (const TextQuery&t) const
    {
        return q->eval(t);
    }
    std::string rep() const
    {
        return q->rep();
    }
private:
    Query(std::shared_ptr<Query_base> query): q(query) {} // !!!!
    std::shared_ptr<Query_base> q;
};



