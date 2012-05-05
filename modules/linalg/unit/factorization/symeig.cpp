//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - symeig factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/symeig.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(symeig_factorization, NT2_REAL_TYPES)
{
  using nt2::tag::factorization::symeig_;

  typedef nt2::table<T> t_t;
  t_t b =       nt2::ones (4, 4, nt2::meta::as_<T>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>());

  typedef typename nt2::meta::call<symeig_(t_t const&,char)>::type result_type;

  result_type res = nt2::factorization::symeig(b, 'V', 'U');

  NT2_DISP(b);
  NT2_DISP(res.w());
  NT2_DISP(res.v());
  NT2_DISP(res.cond());
  NT2_DISP(res.rank());

  b = nt2::zeros(4, 4, nt2::meta::as_<T>());
  b(1,1) = 1;
  NT2_DISP(b);
  res = nt2::factorization::symeig(b,'V', 'U');
  NT2_DISP(b);

  NT2_DISP(res.w());
  NT2_DISP(res.v());
  NT2_DISP(res.cond());
  NT2_DISP(res.rank());

  NT2_TEST_ASSERT( nt2::factorization::symeig(nt2::ones(4, 2),'V', 'U') );
}

NT2_TEST_CASE_TPL ( symeig_factorization_inplace, NT2_REAL_TYPES)
{
  using nt2::tag::factorization::symeig_;
  using nt2::meta::as_;

  typedef nt2::table<T> t_t;
  t_t b =       nt2::ones (4, 4, nt2::meta::as_<T>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>());
  NT2_DISP(b);

  typedef typename nt2::meta::call
          <symeig_(t_t&, char, char, as_<nt2::details::in_place_> const&)>::type ip_t;

  ip_t ires = nt2::factorization::symeig(b,'V','L',nt2::in_place_);

  NT2_DISP(b);
  NT2_DISP(ires.w());
  NT2_DISP(ires.v());
  NT2_DISP(ires.cond());
  NT2_DISP(ires.rank());

  b = nt2::zeros(4, 4, nt2::meta::as_<T>());
  b(1,1) = 1;
  NT2_DISP(b);
  ires = nt2::factorization::symeig(b,'V', 'U',nt2::in_place_);

  NT2_DISP(b);
  NT2_DISP(ires.w());
  NT2_DISP(ires.v());
  NT2_DISP(ires.cond());
  NT2_DISP(ires.rank());

  b = nt2::ones(4, 2, nt2::meta::as_<T>());
  NT2_TEST_ASSERT( nt2::factorization::symeig(b,'V', 'U',nt2::in_place_) );
}
