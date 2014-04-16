//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/ndims.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( fundamental_ndims )
{
  using nt2::ndims;

  NT2_TEST_EQUAL( ndims('4'), 2U  );
  NT2_TEST_EQUAL( ndims(4)  , 2U  );
  NT2_TEST_EQUAL( ndims(4.) , 2U  );
  NT2_TEST_EQUAL( ndims(4.f), 2U  );
}
