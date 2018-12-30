#pragma once
#include "Query_class.h"

// 这个include 不能再被另外一个include 引用了.
//////////////////////////////////////////////
class NotQuery : public Query_base
{
    friend Query operator~(const Query&);
    NotQuery(const Query &q) : query(q) {}

    std::string rep() const
    {
        return "~(" + query.rep() + ")";
    }
    QueryResult eval(const TextQuery&) const;
    Query query;
};

inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base>( new NotQuery(operand));
}

///////////////////////////////////
class BinaryQuery : public Query_base
{
protected:
    BinaryQuery(const Query&l, const Query&r, std::string s) :
        lhs(l), rhs(r), opSym(s) {}

    std::string rep() const 
    {
        return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
    }

    Query lhs, rhs;
    std::string opSym;
};

class AndQuery : public BinaryQuery
{
    friend Query operator& (const Query&, const Query&);
    AndQuery(const Query &left, const Query&right):
        BinaryQuery(left, right, "&") {}
    QueryResult eval(const TextQuery&) const;
};

inline Query operator&(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base> (new AndQuery(lhs, rhs));
}


class OrQuery : public BinaryQuery
{
    friend Query operator | (const Query&, const Query&);
    OrQuery(const Query &left, const Query &right):
        BinaryQuery(left, right, "|") {}
    QueryResult eval(const TextQuery&) const;
};

inline Query operator | (const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}