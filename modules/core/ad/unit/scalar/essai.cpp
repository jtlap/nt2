//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/ad.hpp>
#include <nt2/include/functions/ad_io.hpp>
#include <nt2/include/functions/linspace.hpp>
//#include <nt2/include/functions/ad_df.hpp>
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
    using nt2::sin;
    typedef typename nt2::ad::etype<T>::type sT;
    NT2_DISPLAY(nt2::type_id<T>());
    NT2_DISPLAY(nt2::type_id<sT>());
    return sin(sqr((sT(2)*x+sT(1))*x+sT(3)));
  }
  template < class T > T dtest(const T & x)
  {
    typedef typename nt2::ad::etype<T>::type sT;
    using nt2::sqr;
    using nt2::cos;
    return cos(sqr((sT(2)*x+sT(1))*x+sT(3)))*sT(2)*((sT(2)*x+sT(1))*x+sT(3))*(sT(2)*sT(2)*x+sT(1));
  }



using nt2::ad::valder;

NT2_TEST_CASE_TPL ( essai,  (double))
{

  valder<T> a(T(3));
  valder<T> z = test(a);
  NT2_DISPLAY(z.val());
  NT2_DISPLAY(z.der());
  NT2_DISPLAY(z);
  NT2_TEST_ULP_EQUAL(z.der(), dtest(a.val()), 0.5);
  NT2_TEST_ULP_EQUAL(z.val(), test(a.val()), 0.5);
}


  template < class T > T testc(const T & x)
  {
    using nt2::sqr;
    using nt2::sin;
    NT2_DISPLAY("testc");
    typedef typename nt2::ad::etype<T>::type sT;
    NT2_DISPLAY(nt2::type_id<T>());
    NT2_DISPLAY(nt2::type_id<sT>());

    return sqr((sT(2)*x+sT(1))*x+sT(3));
  }
  template < class T > T dtestc(const T & x)
  {
    typedef typename nt2::ad::etype<T>::type sT;
    using nt2::sqr;
    using nt2::cos;
    NT2_DISPLAY("dtestc");
    NT2_DISPLAY(nt2::type_id<T>());
    NT2_DISPLAY(nt2::type_id<sT>());
    return nt2::Two<sT>()*((sT(2)*x+sT(1))*x+sT(3))*(nt2::Two<sT>()*sT(2)*x+sT(1));
  }


NT2_TEST_CASE_TPL ( essaic,  (double))//NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  valder<cT> a(cT(3, 1));
  NT2_DISPLAY(a);
  valder<cT> z = testc(a);
  NT2_DISPLAY(z.val());
  NT2_DISPLAY(z.der());
  NT2_DISPLAY(z);
  NT2_TEST_ULP_EQUAL(z.der(), dtestc(a.val()), 0.5);
  NT2_TEST_ULP_EQUAL(z.val(), testc(a.val()), 0.5);
}

NT2_TEST_CASE_TPL ( essaia,  (double))//NT2_REAL_TYPES)
{
  typedef nt2::table<T> tT;
  valder<tT> a(nt2::linspace(T(1), T(5), 5));
  NT2_DISPLAY(a);
  NT2_DISPLAY(a.val());
  NT2_DISPLAY(a.der());
  NT2_DISPLAY(testc(a.val()));
  NT2_DISPLAY(testc(a.der()));
  valder<tT> z = testc(a);

  NT2_DISPLAY(z.val());
  NT2_DISPLAY(z.der());
  NT2_DISPLAY(z);
  NT2_DISPLAY(z.val());
  NT2_DISPLAY(z.der());
  NT2_TEST_ULP_EQUAL(z.der(), dtestc(a.val()), 0.5);
  NT2_TEST_ULP_EQUAL(z.val(), testc(a.val()), 0.5);
}

