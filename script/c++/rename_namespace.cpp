#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// needed when compiling without optimization turned on
#ifdef USE_SETRLIMIT
#include <sys/resource.h>
#endif

namespace fusion  = boost::fusion;
namespace phoenix = boost::phoenix;
namespace spirit  = boost::spirit;
namespace qi      = spirit::qi;

typedef std::string::iterator file_iterator;

using spirit::standard::space;
using spirit::standard::space_type;

struct namespace_grammar : qi::grammar<file_iterator, std::string()>
{
    namespace_grammar(bool debug_) : base_type(root), debug(debug_)
    {
        using namespace qi::labels;

        root
            =   (   ns > root           )   [ _val = _1 + _2 ]
            |   (   qi::attr_cast<std::string>(
                        qi::char_
                    ) >  root           )   [ _val = _1 + _2 ]
            |   (   qi::eoi             )   [ _val = std::string() ]
        ;

        ns
            =   (   qi::lit("namespace")
                    >> qi::omit[+space]
                    >> qi::lit("nt2")
                    >> qi::attr_cast<std::string>(*space)
                    >> qi::lit("{")
                    >> data
                    >> qi::lit("}")
                )
                [
                    _val = "namespace boost { namespace dispatch" + _1 + "{" + _2 + "} }"
                ]
            ;

        data
            =   (   qi::char_("{") >> data >> qi::char_("}")  >  data   )
            |   (   +(  qi::char_ - qi::char_("{}") ) > data            )
            |   qi::eps
        ;

        #define DEBUG_NODE(r)                                              \
        r.name(#r);                                                        \
        if(debug)                                                          \
            qi::debug(r);                                                  \

        DEBUG_NODE(root)
        DEBUG_NODE(ns)
        DEBUG_NODE(data)
    }

    qi::rule<file_iterator, std::string()> data;
    qi::rule<file_iterator, std::string()> ns;
    qi::rule<file_iterator, std::string()> root;

    bool debug;
};

int main(int argc, char* argv[])
{
    bool debug = false;
    bool display = false;
    int pos = 1;
    for(int i=1; i!=argc; ++i)
    {
        if(argv[i] == std::string("--debug"))
        {
            debug = true;
            if(i <= pos)
                ++pos;
        }
        else if(argv[i] == std::string("--display"))
        {
            display = true;
            if(i <= pos)
                ++pos;
        }
    }

    if(pos >= argc)
    {
        std::cerr << "No file argument" << std::endl;
        return 1;
    }

#ifdef USE_SETRLIMIT
    struct rlimit limit = { RLIM_INFINITY, RLIM_INFINITY };
    if(setrlimit(RLIMIT_STACK, &limit) < 0)
    {
        std::cerr << "Can't change stack size" << std::endl;
        return 1;
    }
#endif

    std::fstream f(argv[pos]);
    if(!f)
    {
        std::cerr << "File " << argv[pos] << " could not be opened" << std::endl;
        return 1;
    }

    if(display)
        std::cout << argv[pos] << ": parsing..." << std::endl;

    std::stringstream ss;
    ss << f.rdbuf();
    std::string buf = ss.str();

    std::string::iterator it = buf.begin();

    std::string file;
    bool b = qi::parse(it, buf.end(), namespace_grammar(debug), file);

    if(!b)
    {
        std::cerr << argv[pos] << ": failed to parse" << std::endl;
        return 1;
    }
    f.close();
    f.open(argv[pos], std::fstream::out | std::fstream::trunc);
    if(!f)
    {
        std::cerr << "File " << argv[pos] << " could not be opened" << std::endl;
        return 1;
    }

    if(display)
        std::cout << argv[pos] << ": parse successful" << std::endl;

    f << file;
    return 0;
}
