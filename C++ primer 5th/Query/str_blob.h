#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

//////////////////////////////////////

class StrBlobPtr;
class StrBlob
{
    friend class StrBlobPtr;
public:
    using size_type = std::vector<std::string>::size_type;

    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    ~StrBlob() {}
    //StrBlob(const StrBlob& rhs){}

    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}
    void push_back(const std::string &t) {data->push_back(t);}
    void pop_back();

    std::string& front();
    std::string& back();

    std::string& operator[](size_type i) const
    {
        check(i + 1, "front on empty StrBlob");
        return (*data)[i];
    }

    StrBlobPtr begin();

    StrBlobPtr end();

private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const;
};

class StrBlobPtr
{
public:
    StrBlobPtr() : curr(0){}
    StrBlobPtr(StrBlob& a, size_t sz = 0) :
        wptr(a.data), curr(sz) {}
    std::string & deref() const
    {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }

    std::string& operator[](size_t i) const
    {
        auto p = check(i, "operator[] failed");
        return (*p)[i];
    }

    StrBlobPtr& incr()
    {
        check(curr, "increment past end of StrBlobPtr");
        ++curr;
        return *this;
    }

private:
    std::shared_ptr<std::vector<std::string>>
        check(std::size_t, const std::string&) const;

private:
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};

