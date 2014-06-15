//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 is_vector"

#include <nt2/core/functions/table/details/is_definitely_vector.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE( is_col_vector )
{
  using nt2::details::is_col_vector;
  using nt2::of_size_;
  using namespace nt2::meta;

  NT2_TEST_TYPE_IS( (is_col_vector< of_size_<> >::type), true_ );
  NT2_TEST_TYPE_IS( (is_col_vector< of_size_<-1> >::type), true_ );
  NT2_TEST_TYPE_IS( (is_col_vector< of_size_<-1, -1> >::type), indeterminate_ );
  NT2_TEST_TYPE_IS( (is_col_vector< of_size_<1, -1> >::type), indeterminate_ );
  NT2_TEST_TYPE_IS( (is_col_vector< of_size_<1, -1, -1> >::type), indeterminate_ );
}

NT2_TEST_CASE( is_row_vector )
{
  using nt2::details::is_row_vector;
  using nt2::of_size_;
  using namespace nt2::meta;

  NT2_TEST_TYPE_IS( (is_row_vector< of_size_<> >::type), true_ );
  NT2_TEST_TYPE_IS( (is_row_vector< of_size_<-1> >::type), false_ );
  NT2_TEST_TYPE_IS( (is_row_vector< of_size_<-1, -1> >::type), indeterminate_ );
  NT2_TEST_TYPE_IS( (is_row_vector< of_size_<1, -1> >::type), true_ );
  NT2_TEST_TYPE_IS( (is_row_vector< of_size_<1, -1, -1> >::type), indeterminate_ );
}
