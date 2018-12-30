
#include "Query_class_impl.h"
#include <fstream>

std::ostream &
operator<<(std::ostream &os, const Query &query)
{
    return os << query.rep();
}

////////////////////////////////////////////////////////////////

std::string make_plural(size_t ctr, const std::string& word, const std::string& ending)
{
    return (ctr > 1) ? word + ending : word;
}

//////////////////////////////

std::ostream& print(std::ostream& os, const QueryResult &qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " "
        << make_plural(qr.lines->size(), "time", "s") << std::endl;
    for (auto num : *qr.lines)
    {
        os << "\t(line " << num + 1 << ")"
            << (qr.file)[num] << std::endl;
    }
    return os;
}

/*
void runQueries(std::fstream &infile)
{
    TextQuery tq(infile);
    do
    {
        std::cout << "enter word to look for, or q to quit:";
        std::string s;

        if (!(std::cin >> s) || s == "q") break;

        print(std::cout, tq.query(s)) << std::endl;

    } while (true);
}
*/

void runQueries(std::fstream &infile)
{
    TextQuery tq(infile);
    do
    {
        //std::cout << "enter word to look for, or q to quit:";
        //std::string s;

        //if (!(std::cin >> s) || s == "q") break;

        Query q = Query("fiery") & Query("bird") | Query("wind");
        q.eval(tq);

        print(std::cout, q.eval(tq)) << std::endl;

    } while (false);
}


int main()
{
    std::fstream file;
    file.open("c:\\work\\work space for vs\\file", std::ios::in);
    if (!file)
    {
        printf("%s, open file is failed.\n", __FUNCTION__);
        getchar();
        return 0;
    }

    runQueries(file);
    getchar();
    
    return 0;
}

#if 0
class Test
{
public:
    Test(int data = 10): mb (data), ma(data){}
    void show() const
    {
        std::cout<< "ma : "<<ma<< " "<<"mb: "<<mb<<std::endl;
    }
    Test& operator=(const Test& rhs)
    {
        this->ma = 20;
        printf("rhs.ma: %d.\n", rhs.ma);
        ma = rhs.ma;
        mb = rhs.mb;
        return *this;
    }
private:
    int ma;
    int mb;
};

int main()
{
    /*
    Test t1(10);
    t1 = t1;
    system("pause");
    return 0;
    */
    //system("");
    //return 0;

    std::ifstream file;
    runQueries(file);
    /*
    int idex = 0, n = 14;
    std::allocator<std::string> alloc_str;
    auto const p = alloc_str.allocate(n);
    std::string s;
    std::string * temp_p = p;
    while (std::cin >> s && ++ idex != n)
    {
        alloc_str.construct(temp_p, s);
        std::cout<<temp_p->c_str()<<std::endl;
        temp_p++;
    }
    while (temp_p != p)
    {
        alloc_str.destroy(--temp_p);
    }
    alloc_str.deallocate(p, n);
    */
}


#endif