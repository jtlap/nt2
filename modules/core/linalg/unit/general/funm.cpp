//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - funm"

#include <nt2/table.hpp>
#include <nt2/include/functions/funm.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/exp_1.hpp>
#include <nt2/include/functions/expm.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/cosh.hpp>
#include <nt2/include/functions/sinh.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_odd.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/blkdiag.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/table.hpp>
#include <boost/dispatch/meta/strip.hpp>


struct fexp
{
  template<class Sig>
  struct result;

  template<class This, class X>
  struct result<This(X)>
  {
    typedef nt2::table< typename boost::dispatch::meta::strip<X>::type::value_type > type;
  };

  template < class X, class N> inline
  nt2::table< typename X::value_type> operator()(const X & x, const N& ) const
  {
    return nt2::exp(x);
  }

};

struct fcosh
{
  template<class Sig>
  struct result;

  template<class This, class X>
  struct result<This(X)>
  {
    typedef nt2::table< typename boost::dispatch::meta::strip<X>::type::value_type > type;
  };

  template < class X, class N> inline
  nt2::table< typename X::value_type> operator()(const X & x, const N& n ) const
  {
    if(nt2::is_odd(n))
      return nt2::sinh(x);
    else
      return nt2::cosh(x);
  }

};

NT2_TEST_CASE_TPL(funm1, NT2_REAL_TYPES)
{
  using nt2::funm;
  using nt2::tag::funm_;
  nt2::table<T> n =  nt2::from_diag(T(2)*nt2::_((1),T(3)));
  nt2::table<T> funmn = nt2::funm(fexp(), n);
  nt2::table<T> expmn = nt2::expm(n);
  NT2_TEST_ULP_EQUAL(expmn, funmn, 8);
}

NT2_TEST_CASE_TPL(funm2, NT2_REAL_TYPES)
{
  using nt2::expm;
  using nt2::tag::expm_;

  nt2::table<T> n =  nt2::trans(nt2::cons<T>(nt2::of_size(3, 3),
                                             6.931471805599453e-01,     1.732867951399863e-01,      5.672862738622911e-01,
                                             0,     1.386294361119891e+00,                       -2.027325540540822e-01,
                                             0,                         0,                        1.791759469228055e+00
                                            ));
  nt2::table<T> r =  nt2::trans(nt2::cons<T>(nt2::of_size(3, 3),
                                             2,0.5, 2,
                                             0,4, -1,
                                             0, 0, 6
                                            ));
  nt2::table<T> expmn = nt2::expm(n);
  nt2::table<T> funmn  = nt2::funm(fexp(), n);
  NT2_TEST_ULP_EQUAL(expmn, r, 8);
  NT2_TEST_ULP_EQUAL(funmn, r, 8);
 }


NT2_TEST_CASE_TPL(funm3, NT2_REAL_TYPES)
{
  nt2::table<T> n =  nt2::trans(nt2::cons<T>(nt2::of_size(4, 4),
                                             2.0000,    0.5000,    0,         0,
                                             0,    2.0000,    1.0000,         0,
                                             0,         0,    4.0000,    1.0000,
                                             0,         0,         0,    4.0000
                                            ));
  nt2::table<T> r =  nt2::trans(nt2::cons<T>(nt2::of_size(4, 4),
                                             3.762195691083631e+00,     1.813430203923510e+00,     2.036539541154852e+00,            9.213425575052394e-01,
                                             0,                         3.762195691083631e+00,     1.177301857246643e+01,            7.758449312330661e+00,
                                             0,                                                    0,     2.730823283601649e+01,     2.728991719712775e+01,
                                             0,                                                    0,                         0,     2.730823283601649e+01
                                            ));
  nt2::table<T> funmn  = nt2::funm(fcosh(), n);
  NT2_TEST_ULP_EQUAL(funmn, r, 8);
 }
