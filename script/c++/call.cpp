#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/adapted/struct/define_struct.hpp>
#include <boost/foreach.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace phoenix = boost::phoenix;
namespace spirit  = boost::spirit;
namespace qi      = spirit::qi;

typedef std::string::iterator file_iterator;

using spirit::ascii::space_type;

std::string add_scalar(const std::string& arg)
{
    std::string::const_iterator it = arg.begin();
    std::string arg2;
    if(qi::phrase_parse(it, arg.end(), *qi::lit('(') >> "simd_", spirit::ascii::space))
        return arg;
        
    return "scalar_< " + arg + " >";
}




BOOST_FUSION_DEFINE_STRUCT(, dispatch_t,
    (std::string, tag)
    (std::string, site)
    (std::vector<std::string>, template_args)
    (std::vector<std::string>, args)
);

std::ostream& operator<<(std::ostream& os, dispatch_t const& dispatch)
{
    os << "  NT2_FUNCTOR_IMPLEMENTATION( ";
    os << dispatch.tag << ", " << dispatch.site << "\n";
    os << "                            , ";
    BOOST_FOREACH(const std::string& arg, dispatch.template_args)
      os << '(' << arg << ')';
    os << "\n                            , ";
    BOOST_FOREACH(const std::string& arg, dispatch.args)
      os << '(' << add_scalar(arg) << ')';
    os << "\n                            )\n";
    return os;
}

BOOST_FUSION_DEFINE_STRUCT(, call_t,
    (std::string, prefix)
    (std::string, comment)
    (dispatch_t, dispatch)
    (std::string, result)
    (std::string, code)
);

std::ostream& operator<<(std::ostream& os, call_t const& call)
{
    os << call.prefix;
    os << call.comment;
    os << "namespace nt2 { namespace meta\n";
    os << "{\n";
    os << call.dispatch;
    os << "  {\n\n";
    os << "    typedef " << call.result << " result_type;\n\n";
    os << "    NT2_FUNCTOR_CALL(" << call.dispatch.args.size() << ")\n";
    os << "    {";
    os << call.code << "}\n";
    os << "  };\n";
    os << "} }\n";
    return os;
}

BOOST_FUSION_DEFINE_STRUCT(, file_t,
    (std::vector<call_t>, specializations)
    (std::string, epilogue)
);

std::ostream& operator<<(std::ostream& os, file_t const& file)
{
    os << "//==============================================================================\n";
    os << "//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II       \n";
    os << "//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI       \n";
    os << "//                                                                              \n";
    os << "//          Distributed under the Boost Software License, Version 1.0.          \n";
    os << "//                 See accompanying file LICENSE.txt or copy at                 \n";
    os << "//                     http://www.boost.org/LICENSE_1_0.txt                     \n";
    os << "//==============================================================================\n";
    
    BOOST_FOREACH(const call_t& call, file.specializations)
        os << call;
        
    os << file.epilogue;
    os << "#endif\n";
    return os;
}

struct call_file : qi::grammar<file_iterator, space_type, file_t()>
{
    call_file(bool debug_) : base_type(root), debug(debug_)
    {
        using namespace qi::labels;
        
        specialization
            =   (   qi::no_skip[!spirit::ascii::space] >> comment
                >>  register_dispatch
                >>  qi::lit("namespace") >> qi::lit("nt2")
                >>  qi::lit('{')
                    >>  qi::lit("namespace") >> qi::lit("ext")
                    >>  qi::lit('{')
                        >>  call
                    >>  qi::lit('}')
                >>  qi::lit('}')
                )[
                    _val = phoenix::construct<call_t>("", _1, _2, phoenix::at_c<0>(_3), phoenix::at_c<1>(_3))
                ]
            |   (   qi::no_skip[qi::char_] >> specialization    )
                [
                    // prepend character to first member of call_t
                    phoenix::insert(phoenix::at_c<0>(_2), phoenix::begin(phoenix::at_c<0>(_2)), _1),
                    _val = _2
                ]
        ;
        
        register_dispatch
            =   qi::lit("NT2_REGISTER_DISPATCH")
                >>  qi::lit('(')
                    >> full_name >> qi::lit(',') // tag
                    >> full_name >> qi::lit(',') // site
                    >> *(qi::lit('(') >> name >> qi::lit(')')) >> qi::lit(',') // template args
                    >> *(qi::lit('(') >> full_name >> qi::lit(')')) // args
                >>  qi::lit(')')
                >>  -qi::lit(';')
        ;
        
        call
            =   template_declare
                >>  qi::lit("struct") >> qi::lit("call")
                >> qi::omit
                [
                    qi::lit('<')
                        >> full_name
                        >> qi::lit('(')
                            >> (full_name % ',')
                        >> qi::lit(')') >> qi::lit(',')
                        >>  full_name >> qi::lit(',')
                        >>  qi::lit("Dummy")
                    >>  qi::lit('>')
                ]
                >>  qi::lit(':') >> qi::lit("callable")
                >>  qi::lit('{')
                    >> result
                    >> operator_
                >>  qi::lit('}') >> qi::lit(';')
        ;
        
        result
            =   (   qi::lit("typedef") >> full_name >> qi::lit("result_type")   )
            |   (   template_declare
                    >>  qi::lit("struct") >> qi::lit("result") >> qi::lit(';')
                    >>  template_declare >> qi::lit("struct") >> qi::lit("result")
                    >>  qi::omit
                    [
                        qi::lit('<')
                            >> full_name
                            >> qi::lit('(')
                                >> (full_name % ',')
                            >> qi::lit(')')
                        >> qi::lit('>')
                    ]
                    >>  (   (   qi::lit(':')
                                >> full_name >> qi::lit('{') >> qi::lit('}')
                            )   [ _val = "typename " + _1 + "::type"    ]
                        |   (   qi::lit('{')
                                >>  qi::lit("typedef") >> full_name >> qi::lit("type") >> qi::lit(';')
                                >>  qi::lit('}')
                            )
                        )
                )
                >> qi::lit(';')
        ;
        
        operator_
            =   qi::lit("NT2_FUNCTOR_CALL(") >> qi::omit[qi::int_] >> qi::lit(')')
                >> qi::lit('{')
                >> qi::no_skip[code]
                >> qi::lit('}')
        ;

        template_declare
            =   qi::lit("template")
                >> qi::lit('<')
                    >>  (   (   qi::lit("class")
                            |   qi::lit("typename")
                            ) >> name
                        ) % ','
                >> qi::lit('>')
        ;
        
        name = qi::raw[+qi::char_("a-zA-Z0-9_")];
        
        full_name
            =   qi::raw[
                    (   qi::lit('(') >> (full_name % qi::char_(',')) >> qi::lit(')')   )
                    |   (   +(qi::char_("a-zA-Z0-9_:"))
                    >> -(   qi::char_('<') >> (full_name % qi::char_(',')) >> qi::char_('>')   )
                    )
                ]
        ;
        
        code
            =   (   qi::lit('{') >> code >> qi::lit('}')        )
            |   (   +(qi::char_ - qi::char_("{}"))  >> -code    )
        ;
        
        root
            =   qi::omit[comment]
                >>  *specialization
                >>  epilogue
        ;
        
        epilogue
            =   ( qi::no_skip["#endif"] >> qi::omit[comment >> qi::eoi]  )
            |   ( qi::no_skip[qi::char_] >> epilogue )
        ;

        comment
            =   qi::raw
                [
                    (   *qi::lexeme[qi::lit("//") >> *(qi::char_ - qi::eol)]                            )
                |   (   *qi::lexeme[qi::lit("/*") >> *(qi::char_ - qi::char_("*/")) >> qi::lit("*/")]   )
                ]
        ;
        
        #define DEBUG_NODE(r)                                              \
        r.name(#r);                                                        \
        if(debug)                                                          \
            qi::debug(r);                                                  \
        
        DEBUG_NODE(root)
        DEBUG_NODE(comment)
        DEBUG_NODE(epilogue)
            
        DEBUG_NODE(specialization)
        DEBUG_NODE(register_dispatch)
        DEBUG_NODE(call)
        DEBUG_NODE(result)
        DEBUG_NODE(operator_)
        
        DEBUG_NODE(template_declare)
        DEBUG_NODE(name)
        DEBUG_NODE(full_name)
        DEBUG_NODE(code)
    }

    
    qi::rule<file_iterator, space_type, file_t()> root;
    qi::rule<file_iterator, space_type, std::string()> epilogue;
    qi::rule<file_iterator, space_type, std::string()> comment;
    
    qi::rule<file_iterator, space_type, call_t()> specialization;
    qi::rule<file_iterator, space_type, dispatch_t()> register_dispatch;
    qi::rule<file_iterator, space_type, boost::fusion::vector2<std::string, std::string>()> call;
    qi::rule<file_iterator, space_type, std::string()> result;
    qi::rule<file_iterator, space_type, std::string()> operator_;
    
    qi::rule<file_iterator, space_type> template_declare;
    qi::rule<file_iterator, space_type, std::string()> name;
    qi::rule<file_iterator, space_type, std::string()> full_name;
    qi::rule<file_iterator, std::string()> code;
    
    bool debug;
};

int main(int argc, char* argv[])
{
    bool debug = false;
    int pos = 1;
    for(int i=1; i!=argc; ++i)
    {
        if(argv[i] == std::string("--debug"))
        {
            debug = true;
            if(i <= pos)
                ++pos;
        }
    }
    
    if(pos >= argc)
    {
        std::cerr << "No file argument" << std::endl;
        return 1;
    }
    
    std::fstream f(argv[pos]);
    if(!f)
    {
        std::cerr << "File " << argv[pos] << " could not be opened" << std::endl;
        return 1;
    }
    
    std::stringstream ss;
    ss << f.rdbuf();
    std::string buf = ss.str();
    
    std::string::iterator it = buf.begin();
    
    file_t file;
    bool b = qi::phrase_parse(it, buf.end(), call_file(debug), spirit::ascii::space, file);
    
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
    f << file;
    return 0;
}
