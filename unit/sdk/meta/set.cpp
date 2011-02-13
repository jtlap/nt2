/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::set"

#include <nt2/sdk/meta/set.hpp>
#include <nt2/sdk/meta/join.hpp>
#include <nt2/sdk/meta/is_set.hpp>
#include <nt2/sdk/meta/has_key.hpp>

#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/int.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test empty set 'emptyness'
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(empty_set)
{
  using nt2::meta::set;
  using nt2::meta::is_set;
  using nt2::meta::has_key;

  NT2_TEST( is_set< set<> >::value            );
  NT2_TEST( !(has_key< set<> ,void>::value )  );
  NT2_TEST( !(has_key< set<> ,int>::value  )  );
  NT2_TEST( !(has_key< set<> ,float>::value)  );
}

////////////////////////////////////////////////////////////////////////////////
// Test set access
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(normal_set)
{
  using nt2::meta::set;
  using nt2::meta::is_set;
  using nt2::meta::has_key;

  // Is it detected as a set
  NT2_TEST( (is_set < set<int,float,void> >::value) );

  // Check for element inside the set
  NT2_TEST(  (has_key< set<int,float,void>, void  >::value) );
  NT2_TEST(  (has_key< set<int,float,void>, int   >::value) );
  NT2_TEST(  (has_key< set<int,float,void>, float >::value) );
  NT2_TEST( !(has_key< set<int,float,void>, double>::value) );
  NT2_TEST( !(has_key< set<int,float,void>, int** >::value) );
}

////////////////////////////////////////////////////////////////////////////////
// Test set join
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(join_set)
{
  using nt2::meta::set;
  using nt2::meta::is_set;
  using nt2::meta::has_key;
  using nt2::meta::join;

  NT2_TEST( (is_set< join< set<float>,set<int> > >::value)        );
  NT2_TEST( (has_key< join< set<float>,set<int> >, float >::value));
  NT2_TEST( (has_key< join< set<float>,set<int> >, int >::value)  );

  NT2_TEST(  (is_set< join< set<int>,set<> > >::value)        );
  NT2_TEST( !(has_key< join< set<int>,set<> >, float >::value));
  NT2_TEST(  (has_key< join< set<int>,set<> >, int >::value)  );

  NT2_TEST(  (is_set< join< set<>,set<int> > >::value)        );
  NT2_TEST( !(has_key< join< set<>,set<int> >, float >::value));
  NT2_TEST(  (has_key< join< set<>,set<int> >, int >::value)  );

  NT2_TEST( (is_set< join< set<>,set<> > >::value)          );
  NT2_TEST( !(has_key< join< set<>,set<> >, float >::value) );
  NT2_TEST( !(has_key< join< set<>,set<> >, int >::value)   );
}

////////////////////////////////////////////////////////////////////////////////
// Test lambda set
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(lambda_set)
{
  using nt2::meta::lambda_set;
  using nt2::meta::is_set;
  using nt2::meta::has_key;

  typedef boost::mpl::equal_to< boost::mpl::sizeof_<boost::mpl::_>
                              , boost::mpl::int_<4>
                              >  has_32bits;
  NT2_TEST( (is_set< lambda_set< has_32bits > >::value)
          );
  NT2_TEST( (has_key< lambda_set< has_32bits >, float >::value));
  NT2_TEST( (has_key< lambda_set< has_32bits >, int>::value)  );
  NT2_TEST( !(has_key< lambda_set< has_32bits >, char >::value)  );
  NT2_TEST( !(has_key< lambda_set< has_32bits >, double >::value)  );
}

////////////////////////////////////////////////////////////////////////////////
// Test join and lambda set
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(lambda_join_set)
{
  using nt2::meta::set;
  using nt2::meta::lambda_set;
  using nt2::meta::is_set;
  using nt2::meta::has_key;
  using nt2::meta::join;

  typedef boost::mpl::equal_to< boost::mpl::sizeof_<boost::mpl::_>
                              , boost::mpl::int_<4>
                              >  has_32bits;
  NT2_TEST( (is_set< join< set<char>,lambda_set< has_32bits > > >::value)
          );
  NT2_TEST( (has_key< lambda_set< has_32bits >, float >::value));
  NT2_TEST( (has_key< lambda_set< has_32bits >, int >::value)  );
  NT2_TEST( !(has_key< lambda_set< has_32bits >, char >::value)  );
  NT2_TEST( !(has_key< lambda_set< has_32bits >, double >::value)  );
}
