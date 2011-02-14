//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 predicates toolbox - majority/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of predicates components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by $author$ the $date$
/// modified by $author$ the $date$
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/toolbox/predicates/include/majority.hpp>
// specific includes for arity 3 tests
#include <nt2/sdk/meta/logical.hpp>

NT2_TEST_CASE_TPL ( majority_real__3,  NT2_REAL_TYPES)
{
  using nt2::majority;
  using nt2::tag::majority_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<majority_(vT,vT,vT)>::type r_t;

  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_SIMD_BUFFER(a0,T, NR, T(-10000), T(10000));
    NT2_CREATE_SIMD_BUFFER(a1,T, NR, T(-10000), T(10000));
    NT2_CREATE_SIMD_BUFFER(a2,T, NR, T(-10000), T(10000));
    double ulp0 = 0.0, ulpd = 0.0;
    for(int j = 0; j < NR/cardinal_of<n_t>::value; j++)
      {
        vT a0 = load<n_t>(&tab_a0[0],j);
        vT a1 = load<n_t>(&tab_a1[0],j);
        vT a2 = load<n_t>(&tab_a2[0],j);
        r_t v = majority(a0,a1,a2);
        for(int i = 0; i< cardinal_of<n_t>::value; i++)
        {
          int k = i+j*cardinal_of<n_t>::value;
          NT2_TEST_ULP_EQUAL( v[i]!=0,nt2::majority(tab_a0[k],tab_a1[k],tab_a2[k]),0);
          ulp0 = nt2::max(ulpd,ulp0);
        }
      }
    std::cout << "max ulp found is: " << ulp0 << std::endl; 
  }
} // end of test for real_

NT2_TEST_CASE_TPL ( majority_signed_int__3,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::majority;
  using nt2::tag::majority_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<majority_(vT,vT,vT)>::type r_t;

  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_SIMD_BUFFER(a0,T, NR, T(-10000), T(10000));
    NT2_CREATE_SIMD_BUFFER(a1,T, NR, T(-10000), T(10000));
    NT2_CREATE_SIMD_BUFFER(a2,T, NR, T(-10000), T(10000));
    double ulp0 = 0.0, ulpd = 0.0;
    for(int j = 0; j < NR/cardinal_of<n_t>::value; j++)
      {
        vT a0 = load<n_t>(&tab_a0[0],j);
        vT a1 = load<n_t>(&tab_a1[0],j);
        vT a2 = load<n_t>(&tab_a2[0],j);
        r_t v = majority(a0,a1,a2);
        for(int i = 0; i< cardinal_of<n_t>::value; i++)
        {
          int k = i+j*cardinal_of<n_t>::value;
          NT2_TEST_ULP_EQUAL( v[i]!=0,nt2::majority(tab_a0[k],tab_a1[k],tab_a2[k]),0);
          ulp0 = nt2::max(ulpd,ulp0);
        }
      }
    std::cout << "max ulp found is: " << ulp0 << std::endl; 
  }
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( majority_unsigned_int__3,  NT2_UNSIGNED_TYPES)
{
  using nt2::majority;
  using nt2::tag::majority_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<majority_(vT,vT,vT)>::type r_t;

  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_SIMD_BUFFER(a0,T, NR, T(-10000), T(10000));
    NT2_CREATE_SIMD_BUFFER(a1,T, NR, T(-10000), T(10000));
    NT2_CREATE_SIMD_BUFFER(a2,T, NR, T(-10000), T(10000));
    double ulp0 = 0.0, ulpd = 0.0;
    for(int j = 0; j < NR/cardinal_of<n_t>::value; j++)
      {
        vT a0 = load<n_t>(&tab_a0[0],j);
        vT a1 = load<n_t>(&tab_a1[0],j);
        vT a2 = load<n_t>(&tab_a2[0],j);
        r_t v = majority(a0,a1,a2);
        for(int i = 0; i< cardinal_of<n_t>::value; i++)
        {
          int k = i+j*cardinal_of<n_t>::value;
          NT2_TEST_ULP_EQUAL( v[i]!=0,nt2::majority(tab_a0[k],tab_a1[k],tab_a2[k]),0);
          ulp0 = nt2::max(ulpd,ulp0);
        }
      }
    std::cout << "max ulp found is: " << ulp0 << std::endl; 
  }
} // end of test for unsigned_int_