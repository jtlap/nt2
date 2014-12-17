//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/constants/properties.hpp>
#include <nt2/include/functions/splat.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include "../constant.hpp"

// unary minus applied to unsigned
#ifdef BOOST_MSVC
  #pragma warning(disable: 4146)
#endif

NT2_TEST_CASE_TPL(allbits, BOOST_SIMD_SIMD_TYPES)
{
  NT2_CHECK_CONSTANT(Allbits , nt2::Allbits<T>() , T);
}

NT2_TEST_CASE_TPL(bitincrement, BOOST_SIMD_SIMD_TYPES)
{
  NT2_CHECK_CONSTANT(Bitincrement , nt2::Bitincrement<T>() , T);
}

NT2_TEST_CASE_TPL(signmask, BOOST_SIMD_SIMD_TYPES)
{
  NT2_CHECK_CONSTANT(Signmask , nt2::Signmask<T>() , T);
}

NT2_TEST_CASE_TPL(sqrtvalmax, BOOST_SIMD_SIMD_TYPES)
{
  NT2_CHECK_CONSTANT(Sqrtvalmax , nt2::Sqrtvalmax<T>() , T);
}

NT2_TEST_CASE_TPL(valmax, BOOST_SIMD_SIMD_TYPES)
{
  NT2_CHECK_CONSTANT(Valmax , nt2::Valmax<T>() , T);
}

NT2_TEST_CASE_TPL(valmin, BOOST_SIMD_SIMD_TYPES)
{
  NT2_CHECK_CONSTANT(Valmin , nt2::Valmin<T>() , T);
}

NT2_TEST_CASE_TPL(maxleftshift, BOOST_SIMD_SIMD_TYPES)
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>  n_t;

  typedef typename boost::dispatch::meta::as_integer<n_t,signed>::type result_type;
  NT2_TEST_EXPR_TYPE( nt2::Maxleftshift<n_t>()
                    , boost::mpl::_
                    , (result_type)
                    );

  NT2_TEST_EQUAL( nt2::Maxleftshift<n_t>()
                , nt2::splat<result_type>(nt2::Maxleftshift<T>())
                );
}

NT2_TEST_CASE_TPL(ieee, BOOST_SIMD_SIMD_TYPES)
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>  n_t;

  typedef typename boost::dispatch::meta
                                  ::as_integer<n_t>::type type;

  NT2_TEST_EXPR_TYPE( nt2::Nbmantissabits<n_t>()
                    , boost::mpl::_
                    , (type)
                    );

  NT2_TEST_EXPR_TYPE( nt2::Nbexponentbits<n_t>()
                    , boost::mpl::_
                    , (type)
                    );


  NT2_TEST_EXPR_TYPE( nt2::Maxexponent<n_t>()
                    , boost::mpl::_
                    , (type)
                    );


  NT2_TEST_EXPR_TYPE( nt2::Minexponent<n_t>()
                    , boost::mpl::_
                    , (type)
                    );


  NT2_TEST_EXPR_TYPE( nt2::Ldexpmask<n_t>()
                    , boost::mpl::_
                    , (type)
                    );


  NT2_TEST_EXPR_TYPE( nt2::Nbdigits<n_t>()
                    , boost::mpl::_
                    , (type)
                    );

  NT2_TEST_EQUAL( nt2::Nbmantissabits<n_t>()
                , nt2::splat<type>(nt2::Nbmantissabits<T>())
                );

  NT2_TEST_EQUAL( nt2::Nbexponentbits<n_t>()
                , nt2::splat<type>(nt2::Nbexponentbits<T>())
                );

  NT2_TEST_EQUAL( nt2::Maxexponent<n_t>()
                , nt2::splat<type>(nt2::Maxexponent<T>())
                );

  NT2_TEST_EQUAL( nt2::Minexponent<n_t>()
                , nt2::splat<type>(nt2::Minexponent<T>())
                );

  NT2_TEST_EQUAL( nt2::Ldexpmask<n_t>()
                , nt2::splat<type>(nt2::Ldexpmask<T>())
                );

  NT2_TEST_EQUAL( nt2::Nbdigits<n_t>()
                , nt2::splat<type>(nt2::Nbdigits<T>())
                );
}
