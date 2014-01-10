//==============================================================================
//         Copyright 2009 - 2013 LRI  UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013             MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/bench/args.hpp>
#include <cstdlib>

namespace nt2
{
  namespace details
  {
    NT2_TEST_BENCHMARK_DECL std::map<std::string,std::string> args_map;

    void NT2_TEST_BENCHMARK_DECL fill_args_map(int argc, const char** argv)
    {
      for(int i=1;i<argc;++i)
      {
        std::string opt(argv[i]);

        // Options are prefixed by -o
        if(opt == "-o")
        {
          // and followed by <name> <value>
          if( argc <= i+2)
          {
            std::cerr << "Incomplete option specification\n";
            std::exit(EXIT_FAILURE);
          }

          args_map[argv[i+1]] = argv[i+2];
        }
      }
    }
  }
}
