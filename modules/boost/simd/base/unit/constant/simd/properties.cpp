//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/constants/properties.hpp>
#include <boost/simd/include/functions/splat.hpp>
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

  NT2_CHECK_CONSTANT(Allbits , boost::simd::Allbits<T>() , T);
}

NT2_TEST_CASE_TPL(bitincrement, BOOST_SIMD_SIMD_TYPES)
{

  NT2_CHECK_CONSTANT(Bitincrement , boost::simd::Bitincrement<T>() , T);
}

NT2_TEST_CASE_TPL(signmask, BOOST_SIMD_SIMD_TYPES)
{

  NT2_CHECK_CONSTANT(Signmask , boost::simd::Signmask<T>() , T);
}

NT2_TEST_CASE_TPL(sqrtvalmax, BOOST_SIMD_SIMD_TYPES)
{

  NT2_CHECK_CONSTANT(Sqrtvalmax , boost::simd::Sqrtvalmax<T>() , T);
}

NT2_TEST_CASE_TPL(valmax, BOOST_SIMD_SIMD_TYPES)
{

  NT2_CHECK_CONSTANT(Valmax , boost::simd::Valmax<T>() , T);
}

NT2_TEST_CASE_TPL(valmin, BOOST_SIMD_SIMD_TYPES)
{

  NT2_CHECK_CONSTANT(Valmin , boost::simd::Valmin<T>() , T);
}

NT2_TEST_CASE_TPL(maxleftshift, BOOST_SIMD_SIMD_TYPES)
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>  n_t;

  typedef typename boost::dispatch::meta::as_integer<n_t,signed>::type result_type;
  NT2_TEST_EXPR_TYPE( boost::simd::Maxleftshift<n_t>()
                    , boost::mpl::_
                    , (result_type)
                    );

  NT2_TEST_EQUAL( boost::simd::Maxleftshift<n_t>()
                , boost::simd::splat<result_type>(boost::simd::Maxleftshift<T>())
                );
}

NT2_TEST_CASE_TPL(ieee, BOOST_SIMD_SIMD_TYPES)
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<T,ext_t>  n_t;

  typedef typename boost::dispatch::meta
                                  ::as_integer<n_t>::type type;

//   typedef typename boost::dispatch::meta
//                                   ::as_integer<n_t,signed>::type s_type;

  NT2_TEST_EXPR_TYPE( boost::simd::Nbmantissabits<n_t>()
                    , boost::mpl::_
                    , (type)
                    );

  NT2_TEST_EXPR_TYPE( boost::simd::Nbexponentbits<n_t>()
                    , boost::mpl::_
                    , (type)
                    );


  NT2_TEST_EXPR_TYPE( boost::simd::Maxexponent<n_t>()
                    , boost::mpl::_
                    , (type)
                    );


  NT2_TEST_EXPR_TYPE( boost::simd::Minexponent<n_t>()
                    , boost::mpl::_
                    , (type)
                    );


  NT2_TEST_EXPR_TYPE( boost::simd::Ldexpmask<n_t>()
                    , boost::mpl::_
                    , (type)
                    );


  NT2_TEST_EXPR_TYPE( boost::simd::Nbdigits<n_t>()
                    , boost::mpl::_
                    , (type)
                    );

  NT2_TEST_EQUAL( boost::simd::Nbmantissabits<n_t>()
                , boost::simd::splat<type>(boost::simd::Nbmantissabits<T>())
                );

  NT2_TEST_EQUAL( boost::simd::Nbexponentbits<n_t>()
                , boost::simd::splat<type>(boost::simd::Nbexponentbits<T>())
                );

  NT2_TEST_EQUAL( boost::simd::Maxexponent<n_t>()
                , boost::simd::splat<type>(boost::simd::Maxexponent<T>())
                );

  NT2_TEST_EQUAL( boost::simd::Minexponent<n_t>()
                , boost::simd::splat<type>(boost::simd::Minexponent<T>())
                );

  NT2_TEST_EQUAL( boost::simd::Ldexpmask<n_t>()
                , boost::simd::splat<type>(boost::simd::Ldexpmask<T>())
                );

  NT2_TEST_EQUAL( boost::simd::Nbdigits<n_t>()
                , boost::simd::splat<type>(boost::simd::Nbdigits<T>())
                );
}
