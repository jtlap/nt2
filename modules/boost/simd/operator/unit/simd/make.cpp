//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 operator toolbox - make/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of operator components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <boost/simd/toolbox/operator/include/functions/make.hpp>
#include <boost/simd/sdk/simd/native.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>

int fibo(int n)
{
  if(n == 0) return 0;
  if(n == 1) return 1;
  return fibo(n-1) + fibo(n-2);
}

#define M1(z, n, t) T(fibo(n))
#define M0(z, n, t)                                                            \
template<class T>                                                              \
struct make_fibo<T, n>                                                         \
{                                                                              \
  typedef boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> type;           \
  static type call()                                                           \
  {                                                                            \
    return boost::simd::make<type>(BOOST_PP_ENUM(n, M1, ~));                   \
  }                                                                            \
};                                                                             \
/**/
template<class T, std::size_t N = boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>::static_size>
struct make_fibo;
BOOST_SIMD_PP_REPEAT_POWER_OF_2(M0, ~)
#undef M0
#undef M1

NT2_TEST_CASE_TPL ( make_fibonnaci,  BOOST_SIMD_SIMD_TYPES)
{
  typedef boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;
  vT x = make_fibo<T>::call();
  for(std::size_t i=0; i!=boost::simd::meta::cardinal_of<vT>::value; ++i)
    NT2_TEST_EQUAL(x[i], T(fibo(i)));
}
