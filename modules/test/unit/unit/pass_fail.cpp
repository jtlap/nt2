//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <iostream>
#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/unit/details/main.hpp>

NT2_UNIT_MAIN_SPEC int NT2_UNIT_MAIN(int argc, char* argv[])
{
  std::cout << "Generating 10000 tests with 5000 fails ...\n";

  for(int i=0;i<10000;++i)
  {
    if(i%2) nt2::unit::error_count()++;
    nt2::unit::test_count()++;
  }

  std::cout << "# Tests : " << nt2::unit::test_count() << "\n";
  std::cout << "# Errors: " << nt2::unit::error_count() << "\n";

  bool check =  (nt2::unit::test_count() == 10000)
            &&  (nt2::unit::error_count() == 5000);

  std::cout << "Validation: " << (check ? "OK" : "NOT OK") << "\n";

  return check ? 0 : 1;
}
