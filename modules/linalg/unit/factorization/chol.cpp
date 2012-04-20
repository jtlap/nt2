//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - chol"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of algebra components
//////////////////////////////////////////////////////////////////////////////

#include <nt2/table.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/chol.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( chol_factorization, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t b = nt2::ones(4, 4, nt2::meta::as_<T>())
            + T(10)*nt2::eye(4, 4, nt2::meta::as_<T>());

  NT2_DISP(b);

  typedef typename nt2::meta::call
          <nt2::tag::factorization::chol_(table_t const&,char)
          >::type result_type;

  result_type           res = nt2::factorization::chol(b,'U');

  NT2_DISP(res.upper_result());
  std::cout << "status : " << res.status() << "\n";

  NT2_TEST_ASSERT( nt2::factorization::chol(nt2::ones(4, 2),'U') );
}

NT2_TEST_CASE_TPL ( chol_factorization_inplace, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t b = nt2::ones(4, 4, nt2::meta::as_<T>())
            + T(10)*nt2::eye(4, 4, nt2::meta::as_<T>());

  NT2_DISP(b);

  typedef typename nt2::meta::call
          <nt2::tag::factorization::chol_ ( table_t&
                                          , char
                                          , nt2::meta::as_<nt2::details::in_place_> const&
                                          )
          >::type in_place_result_type;

  in_place_result_type ires = nt2::factorization::chol(b,'L',nt2::in_place_);
  NT2_DISP(b);
  NT2_DISP(ires.lower_result());
  std::cout << "status : " << ires.status() << "\n";

  b = nt2::ones(4, 2, nt2::meta::as_<T>());
  NT2_TEST_ASSERT( nt2::factorization::chol(b,'U',nt2::in_place_) );
}

NT2_TEST_CASE_TPL ( chol_upper, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t a , b = nt2::ones(4, 4, nt2::meta::as_<T>())
                + T(10)*nt2::eye(4, 4, nt2::meta::as_<T>());

  a = nt2::chol(b);
  NT2_DISP(a);
}

NT2_TEST_CASE_TPL ( chol_lower, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t a , b = nt2::ones(4, 4, nt2::meta::as_<T>())
                + T(10)*nt2::eye(4, 4, nt2::meta::as_<T>());

  a = nt2::chol(b, nt2::lower_);
  NT2_DISP(a);
}


