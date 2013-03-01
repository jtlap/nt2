//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef SOME_EXCEPTION_HPP_INCLUDED
#define SOME_EXCEPTION_HPP_INCLUDED

#include <nt2/sdk/error/exception.hpp>

struct some_exception : nt2::exception
{
  some_exception() : nt2::exception("some exception was thrown") {}
};

#endif
