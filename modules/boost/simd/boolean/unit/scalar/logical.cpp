//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.boolean toolbox - logical<T>"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of logical<T> in scalar mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/sdk/unit/tests.hpp> 
#include <nt2/sdk/unit/module.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/simd/toolbox/boolean/logical.hpp>

NT2_TEST_CASE_TPL ( logical_integral, BOOST_SIMD_INTEGRAL_TYPES )
{
  using boost::simd::logical;

  logical<T> bool_true(true);
  NT2_TEST_EQUAL( bool(bool_true), true );

  logical<T> bool_false(false);
  NT2_TEST_EQUAL( bool(bool_false), false );

  logical<T> val_true( T(1) );
  NT2_TEST_EQUAL( bool(val_true), true );

  logical<T> val_false( T(0) );
  NT2_TEST_EQUAL( bool(val_false), false );
}

NT2_TEST_CASE_TPL ( logical_real, BOOST_SIMD_REAL_TYPES )
{
  using boost::simd::logical;

  logical<T> bool_true(true);
  NT2_TEST_EQUAL( bool(bool_true), true );

  logical<T> bool_false(false);
  NT2_TEST_EQUAL( bool(bool_false), false );

  logical<T> val_true( T(1) );
  NT2_TEST_EQUAL( bool(val_true), true );

  logical<T> val_false( T(0) );
  NT2_TEST_EQUAL( bool(val_false), false );
  
  logical<T> val_mzero( T(-0.) );
  NT2_TEST_EQUAL( bool(val_mzero), false );
}

NT2_TEST_CASE_TPL ( logical_value_of, BOOST_SIMD_TYPES )
{
  using boost::is_same;
  using boost::simd::logical;
  using boost::dispatch::meta::value_of;

  NT2_TEST( (is_same<T        , typename value_of< logical<T> >::type>::value       ));
  NT2_TEST( (is_same<T&       , typename value_of< logical<T>& >::type>::value      ));
  NT2_TEST( (is_same<T const  , typename value_of< logical<T> const>::type>::value  ));
  NT2_TEST( (is_same<T const& , typename value_of< logical<T> const&>::type>::value ));
}

NT2_TEST_CASE_TPL ( logical_model_of, BOOST_SIMD_TYPES )
{
  using boost::is_same;
  using boost::mpl::apply;
  using boost::simd::logical;
  using boost::dispatch::meta::model_of;

  typedef typename model_of< logical<T> >::type model_;

  NT2_TEST( (is_same<logical<T>, typename apply<model_, T>::type >::value ));
}

NT2_TEST_CASE_TPL ( logical_hierarchy_of, BOOST_SIMD_TYPES )
{
  using boost::is_same;
  using boost::simd::logical;
  using boost::dispatch::meta::logical_;
  using boost::dispatch::meta::hierarchy_of;

  NT2_TEST((is_same < logical_< logical<T> >
                    , typename hierarchy_of< logical<T> >::type 
                    >::value 
          ));
}