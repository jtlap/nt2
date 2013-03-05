//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::dispatch::meta::all"

#include <boost/dispatch/meta/all.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test any with 1 sequence argument
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(unary_sequence)
{
  using boost::dispatch::meta::all_seq;
  using boost::is_same;
  using boost::mpl::_1;
  using boost::mpl::vector;

  NT2_TEST(  (all_seq< is_same<_1,bool  >, vector<bool,bool,bool> >::value)     );
  NT2_TEST( !(all_seq< is_same<_1,double>, vector<int,double,bool> >::value)    );
  NT2_TEST( !(all_seq< is_same<_1,double>, vector<bool,double,double> >::value) );
  NT2_TEST( !(all_seq< is_same<_1,double>, vector<double,double,bool> >::value) );
  NT2_TEST( !(all_seq< is_same<_1,double>, vector<double,int,double> >::value)  );
}

////////////////////////////////////////////////////////////////////////////////
// Test any with 1 non-sequence argument
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(unary_non_sequence)
{
  using boost::dispatch::meta::all;
  using boost::is_same;
  using boost::mpl::_1;

  NT2_TEST(  (all< is_same<_1,bool  >, bool >::value) );
  NT2_TEST( !(all< is_same<_1,double>, bool >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test any with non-sequence arguments
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(non_sequences)
{
  using boost::dispatch::meta::all;
  using boost::is_same;
  using boost::mpl::_1;

  // Work
  NT2_TEST((all< is_same<_1,bool>, bool, bool             >::value) );
  NT2_TEST((all< is_same<_1,bool>, bool, bool, bool       >::value) );
  NT2_TEST((all< is_same<_1,bool>, bool, bool, bool, bool	>::value) );

  // Don't work
  NT2_TEST( !(all< is_same<_1,bool>, float, bool              	>::value) );
  NT2_TEST( !(all< is_same<_1,bool>, float, double, bool       	>::value) );
  NT2_TEST( !(all< is_same<_1,bool>, float, double, float, bool	>::value) );
}

