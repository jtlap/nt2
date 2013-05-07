//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - rem_pio2_cephes/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of trigonometric components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 11/02/2011
///
#include <nt2/trigonometric/include/functions/rem_pio2_cephes.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/pio_4.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/pi.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

template < class T, class N>
inline T correct(N n, const T& a)
{
  T z = a+n*nt2::Pio_2<T>();
  return  (z > nt2::Pi<T>()) ? z-2*nt2::Pi<T>() :z;
}

NT2_TEST_CASE_TPL ( rem_pio2_cephes_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::rem_pio2_cephes;
  using nt2::tag::rem_pio2_cephes_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<rem_pio2_cephes_(T)>::type r_t;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<rem_pio2_cephes_(T)>::type)
                  , (std::pair<iT,T>)
                  );


  {
    r_t res = rem_pio2_cephes(nt2::Zero<T>());
    NT2_TEST_ULP_EQUAL( res.first, nt2::Zero<T>(), 0.5);
    NT2_TEST_ULP_EQUAL( res.second, nt2::Zero<iT>(), 0.5);
  }

  {
    r_t res = rem_pio2_cephes(nt2::Pi<T>());
    std::cout << nt2::Pi<T>() << std::endl;
    std::cout << correct(res.first, res.second) << std::endl;
    std::cout << res.first << std::endl;
    std::cout << res.second << std::endl;
    res = rem_pio2_cephes(3*nt2::Pi<T>()/4);
    std::cout << 3*nt2::Pi<T>()/4 << std::endl;
    std::cout << correct(res.first, res.second)<< std::endl;
    std::cout << res.first << std::endl;
    std::cout << res.second << std::endl;

    res = rem_pio2_cephes(-3*nt2::Pi<T>()/4);
    std::cout << -3*nt2::Pi<T>()/4 << std::endl;
    std::cout << correct(res.first, res.second)<< std::endl;
    std::cout << res.first << std::endl;

    std::cout << res.second << std::endl;
    res = rem_pio2_cephes(nt2::Pi<T>()/2);
    std::cout << correct(res.first, res.second)<< std::endl;
    std::cout << nt2::Pi<T>()/2 << std::endl;
    std::cout << res.first << std::endl;

    std::cout << res.second << std::endl;
    res = rem_pio2_cephes(-nt2::Pi<T>()/2);
    std::cout << correct(res.first, res.second)<< std::endl;
    std::cout << -nt2::Pi<T>()/2 << std::endl;
    std::cout << res.first << std::endl;

    std::cout << res.second << std::endl;
  }
} // end of test for floating_
