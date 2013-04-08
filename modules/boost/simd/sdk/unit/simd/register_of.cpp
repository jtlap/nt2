//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::meta::sign_of SIMD"

#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/meta/register_of.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL(register_of, BOOST_SIMD_TYPES)
{
  using boost::mpl::_;
  using boost::simd::meta::register_of;

  T a0;
  NT2_TEST_EXPR_TYPE( a0, register_of<_>, T );
}

NT2_TEST_CASE_TPL(register_of_logical, BOOST_SIMD_TYPES)
{
  using boost::mpl::_;
  using boost::simd::logical;
  using boost::simd::meta::register_of;

  logical<T> a0;
  NT2_TEST_EXPR_TYPE( a0, register_of<_>, logical<T> );
}

NT2_TEST_CASE_TPL(register_of_native, BOOST_SIMD_SIMD_TYPES)
{
  using boost::mpl::_;
  using boost::simd::native;
  using boost::simd::meta::register_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

  native<T,ext_t>  a0;
  NT2_TEST_EXPR_TYPE( a0
                    , register_of<_>
                    , (typename native<T,ext_t>::native_type)
                    );
}


NT2_TEST_CASE_TPL(sign_of_simd_native_logical, BOOST_SIMD_SIMD_TYPES)
{
  using boost::mpl::_;
  using boost::simd::native;
  using boost::simd::logical;
  using boost::simd::meta::register_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef native<logical<T>,ext_t>          native_t;

  native_t a0;
  NT2_TEST_EXPR_TYPE( a0
                    , register_of<_>
                    , typename native_t::native_type
                    );
}

NT2_TEST_CASE_TPL(sign_of_simd, BOOST_SIMD_SIMD_TYPES)
{
  using boost::mpl::_;
  using boost::simd::pack;
  using boost::simd::meta::register_of;

  typedef pack<T>                          pack_t;

  pack_t a0;
  NT2_TEST_EXPR_TYPE( a0
                    , register_of<_>
                    , typename register_of<typename pack_t::data_type>::type
                    );
}

NT2_TEST_CASE_TPL(sign_of_logical_simd, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::pack;
  using boost::simd::logical;
  using boost::mpl::_;
  using boost::simd::meta::register_of;

  typedef pack< logical<T> >            pack_t;

  pack_t a0;
  NT2_TEST_EXPR_TYPE( a0
                    , register_of<_>
                    , typename register_of<typename pack_t::data_type>::type
                    );
}
