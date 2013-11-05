//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/fuzzy/include/functions/tolerant_floor.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>

NT2_TEST_CASE_TPL ( tolerant_floor_real_3,  NT2_SIMD_REAL_TYPES)
{
  using nt2::tolerant_floor;
  using nt2::tag::tolerant_floor_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  typedef typename nt2::meta::call<tolerant_floor_(vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);


  // specific values tests
  NT2_TEST_EQUAL(tolerant_floor(nt2::Zero<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(tolerant_floor(nt2::Eps<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(tolerant_floor(-nt2::Eps<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(tolerant_floor(-nt2::Two<vT>()*nt2::Eps<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(tolerant_floor(-nt2::Three<vT>()*nt2::Eps<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(tolerant_floor(-nt2::Four<vT>()*nt2::Eps<vT>()), nt2::Mone<r_t>());
}
