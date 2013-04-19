//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_XERBLA_LAPACK_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_XERBLA_LAPACK_HPP_INCLUDED

#include <boost/assert.hpp>

extern "C"
{
  void xerbla(char* srname, int* info, int len)
  {
    BOOST_ASSERT_MSG(info <= 0, "Error in BLAS/LAPACK kernel call parameters");
  }
}

#endif
