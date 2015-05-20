//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/whereijk.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/constants/eps.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

struct dd
{
  template<class Sig> struct result;

  template<class This, class A0, class A1, class A2>
  struct result<This(A0,A1,A2)>
  {
    typedef typename nt2::meta::strip<A0>::type a0_t;
    typedef typename nt2::meta::as_logical<a0_t>::type type;
  };

  template < class A0, class A1, class A2>
  typename nt2::meta::as_logical<A0>::type
  operator()(const A0&i, const A1&j  , const A2& k) const
  {
    std::cout << "i " << i <<  "  j " << j << " k " << k << std::endl;
    return nt2::eq(k, j);
  }
};
NT2_TEST_CASE_TPL( whereijk_scalar, NT2_TYPES)
{
  T e = nt2::whereijk(dd(), T(42), T(69));
  NT2_TEST_EQUAL(e, T(42));
}


NT2_TEST_CASE_TPL( whereijk, NT2_TYPES)
{
  nt2::table<T>  a = nt2::zeros( nt2::of_size(1, 3, 3), nt2::meta::as_<T>());
  nt2::table<T>  e = nt2::whereijk(dd(), nt2::Eps<T>(), a);
  nt2::table<T>  f =  nt2::Eps<T>()*reshape(nt2::eye(3, nt2::meta::as_<T>()), 1, 3, 3);


  NT2_DISPLAY(f);
  NT2_TEST_EQUAL(e, f);

}
