//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ad/include/functions/multiplies.hpp>
#include <nt2/ad/include/functions/plus.hpp>
#include <nt2/ad/include/functions/sin.hpp>
#include <nt2/ad/include/functions/cos.hpp>
#include <nt2/ad/include/functions/sqr.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/table.hpp>

namespace nt2 {
  namespace ad
  {
    template < class T>
    valder<T> zsin(const valder<T>&u)
    {
      return valder<T>(nt2::sin(u.val()), nt2::cos(u.val())*u.der());
    };
  }
}

template < class T >
struct vtype
{
  typedef   T type;
};
template < class T >
struct vtype < nt2::ad::valder < T > >
{
  typedef  T type;
};

using namespace nt2::ad;

  template < class T > T test(const T & x)//->decltype( (T(2)*x+T(1))*x+T(3))
  {
    typedef typename vtype<T>::type sT;
    return sin(sT(2)*x+sT(1))*x+sT(3);
  }
  template < class T > T dtest(const T & x)//->decltype((T(4)*x+T(1)))
  {
    typedef typename vtype<T>::type sT;
    return cos(sT(2)*x+sT(1))*x+sT(3)*(sT(4)*x+sT(1));
  }



using nt2::ad::valder;

NT2_TEST_CASE_TPL ( essai,  (double))//NT2_REAL_TYPES)
{

  valder<T> a(3);
//   valder<T> b;
//   b = nt2::ad::plus(a, a);
  valder<T> z = test(a);
  NT2_DISPLAY(z.val());
  NT2_DISPLAY(z.der());
  NT2_TEST_ULP_EQUAL(z.der(), dtest(a.val()), 0.5);
  NT2_TEST_ULP_EQUAL(z.val(), test(a.val()), 0.5);
}




