//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <nt2/sdk/error/exception.hpp>
#include <boost/throw_exception.hpp>

#ifdef BOOST_NO_EXCEPTIONS
namespace boost
{
  /// INTERNAL ONLY
  /// This is a custom Boost.Exception handler that catch exceptions that were
  /// not caught by any tests inside the test function. This is usually the sign
  /// of something wrong in the test.
  void throw_exception(std::exception const& e)
  {
    std::cout << "uncaught exception: " << e.what() << std::endl;
    std::abort();
  }
}
#endif
