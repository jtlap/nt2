//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/ad_df.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/ad.hpp>
#include <nt2/include/functions/ad_io.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/cat.hpp>

#include <nt2/ad/arithmetic.hpp>
#include <nt2/ad/trigonometric.hpp>
#include <nt2/ad/operator.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/table.hpp>


  template < class T > T test(const T & x)
  {
    using nt2::sqr;
    typedef typename nt2::ad::etype<T>::type sT;
    return sqr((sT(2)*x(1, nt2::_)+x(1, nt2::_)*x(2, nt2::_)+sT(3)));
  }
  template < class T > T dfdx1(const T & x)
  {
    typedef typename nt2::ad::etype<T>::type sT;
    return sT(2)*(sT(2)*x(1, nt2::_)+x(1, nt2::_)*x(2, nt2::_)+sT(3))*(sT(2)+x(2, nt2::_));
  }
  template < class T > T dfdx2(const T & x)
  {
    typedef typename nt2::ad::etype<T>::type sT;
    return   sT(2)*(sT(2)*x(1, nt2::_)+x(1,nt2::_)*x(2, nt2::_)+sT(3))*x(1, nt2::_);
  }



using nt2::ad::valder;

NT2_TEST_CASE_TPL ( ad_df,  (double))
{
  typedef nt2::table<T> tT;
  tT x = nt2::cons<T>(nt2::of_size(2, 1), 1, 2);
  tT v = nt2::cat(2, x, x);
  tT d = nt2::eye(2, nt2::meta::as_<T>());
  tT tv = test(v);
  NT2_DISPLAY(tv);
  tT dv1 = dfdx1(x);
  NT2_DISPLAY(dv1);
  tT dv2 = dfdx2(x);
  NT2_DISPLAY(dv2);
  tT dv = nt2::cons<T>(nt2::of_size(1, 2), dv1(1), dv2(1));
  valder<tT> a(v, d);
  NT2_DISPLAY(a);
  valder<tT> z = test(a);
  NT2_DISPLAY(z.val());
  NT2_DISPLAY(z.der());
  NT2_DISPLAY(z);
  NT2_TEST_ULP_EQUAL(z.der(), dv, 0.5);
  NT2_TEST_ULP_EQUAL(z.val(), test(a.val()), 0.5);
}


//   template < class T > struct pipo
//   {
//     T operator()(const T & x)const
//     {
//       using nt2::sqr;
//       typedef typename nt2::ad::etype<T>::type sT;
//       return sqr((sT(2)*x(1, nt2::_)+x(1, nt2::_)*x(2, nt2::_)+sT(3)));
//     }
//   };

NT2_TEST_CASE_TPL ( ad_df1,  (double))
{
  typedef nt2::table<T> tT;
  tT x = nt2::cons<T>(nt2::of_size(2, 3), 1, 2, 3, 4, 5, 6);
  auto f = test<nt2::ad::valder<tT>>;
  NT2_DISPLAY(nt2::type_id(f));
  tT d, v;
//  nt2::tie(v, d)= ad_df(pipo<nt2::ad::valder<tT>>(), x);
  nt2::tie(v, d)= ad_df(f,  x);
  NT2_DISPLAY(nt2::type_id(x));
  NT2_DISPLAY(x);
  NT2_DISPLAY(d);
//  NT2_TEST_ULP_EQUAL(v, f(x), 0.5);
  tT dv1 = dfdx1(x);
  NT2_DISPLAY(dv1);
  tT dv2 = dfdx2(x);
  NT2_DISPLAY(dv2);
  NT2_TEST_ULP_EQUAL(d(1, nt2::_), dv1, 0.5);
  NT2_TEST_ULP_EQUAL(d(2, nt2::_), dv2, 0.5);
  tT tv = test(x);
  NT2_TEST_ULP_EQUAL(v, tv, 0.5);
}



