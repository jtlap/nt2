//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::first_index & last_index"

#include <nt2/table.hpp>
#include <nt2/include/functions/last_index.hpp>
#include <nt2/include/functions/first_index.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests.hpp>

NT2_TEST_CASE( empty_first_last )
{
  using nt2::last_index;
  using nt2::first_index;

  {
    nt2::table<float> x;
    NT2_TEST_EQUAL(first_index<1>(x), 1);
    NT2_TEST_EQUAL(first_index<2>(x), 1);
    NT2_TEST_EQUAL(first_index<3>(x), 1);
    NT2_TEST_EQUAL(first_index<4>(x), 1);
    NT2_TEST_EQUAL(first_index(x,1) , 1);
    NT2_TEST_EQUAL(first_index(x,2) , 1);
    NT2_TEST_EQUAL(first_index(x,3) , 1);
    NT2_TEST_EQUAL(first_index(x,4) , 1);
    NT2_TEST_EQUAL(last_index<1>(x) , 0);
    NT2_TEST_EQUAL(last_index<2>(x) , 1);
    NT2_TEST_EQUAL(last_index<3>(x) , 1);
    NT2_TEST_EQUAL(last_index<4>(x) , 1);
    NT2_TEST_EQUAL(last_index(x,1)  , 0);
    NT2_TEST_EQUAL(last_index(x,2)  , 1);
    NT2_TEST_EQUAL(last_index(x,3)  , 1);
    NT2_TEST_EQUAL(last_index(x,4)  , 1);
  }

  {
    nt2::table<float, nt2::index_<-2,-1,0,1> > x;
    NT2_TEST_EQUAL(first_index<1>(x), -2);
    NT2_TEST_EQUAL(first_index(x,1) , -2);
    NT2_TEST_EQUAL(last_index<1>(x) , -3);
    NT2_TEST_EQUAL(last_index(x,1)  , -3);

    NT2_TEST_EQUAL(first_index<2>(x), -1);
    NT2_TEST_EQUAL(first_index(x,2) , -1);
    NT2_TEST_EQUAL(last_index<2>(x) , -1);
    NT2_TEST_EQUAL(last_index(x,2)  , -1);

    NT2_TEST_EQUAL(first_index<3>(x), 0);
    NT2_TEST_EQUAL(first_index(x,3) , 0);
    NT2_TEST_EQUAL(last_index<3>(x) , 0);
    NT2_TEST_EQUAL(last_index(x,3)  , 0);

    NT2_TEST_EQUAL(first_index<4>(x), 1);
    NT2_TEST_EQUAL(first_index(x,4) , 1);
    NT2_TEST_EQUAL(last_index<4>(x) , 1);
    NT2_TEST_EQUAL(last_index(x,4)  , 1);
  }
}

NT2_TEST_CASE( non_empty_first_last )
{
  using nt2::last_index;
  using nt2::first_index;
  using nt2::of_size;

  {
    nt2::table<float> x( of_size(4,5));
    NT2_TEST_EQUAL(first_index<1>(x), 1);
    NT2_TEST_EQUAL(first_index(x,1) , 1);
    NT2_TEST_EQUAL(last_index<1>(x) , 4);
    NT2_TEST_EQUAL(last_index(x,1)  , 4);

    NT2_TEST_EQUAL(first_index<2>(x), 1);
    NT2_TEST_EQUAL(first_index(x,2) , 1);
    NT2_TEST_EQUAL(last_index<2>(x) , 5);
    NT2_TEST_EQUAL(last_index(x,2)  , 5);

    NT2_TEST_EQUAL(first_index<3>(x), 1);
    NT2_TEST_EQUAL(first_index(x,3) , 1);
    NT2_TEST_EQUAL(last_index<3>(x) , 1);
    NT2_TEST_EQUAL(last_index(x,3)  , 1);

    NT2_TEST_EQUAL(first_index<4>(x), 1);
    NT2_TEST_EQUAL(first_index(x,4) , 1);
    NT2_TEST_EQUAL(last_index<4>(x) , 1);
    NT2_TEST_EQUAL(last_index(x,4)  , 1);
  }

  {
    nt2::table<float, nt2::index_<-2,-1,0,1> > x( of_size(5,3,3,4) );
    NT2_TEST_EQUAL(first_index<1>(x), -2);
    NT2_TEST_EQUAL(first_index(x,1) , -2);
    NT2_TEST_EQUAL(last_index<1>(x) ,  2);
    NT2_TEST_EQUAL(last_index(x,1)  ,  2);

    NT2_TEST_EQUAL(first_index<2>(x), -1);
    NT2_TEST_EQUAL(first_index(x,2) , -1);
    NT2_TEST_EQUAL(last_index<2>(x) ,  1);
    NT2_TEST_EQUAL(last_index(x,2)  ,  1);

    NT2_TEST_EQUAL(first_index<3>(x), 0);
    NT2_TEST_EQUAL(first_index(x,3) , 0);
    NT2_TEST_EQUAL(last_index<3>(x) , 2);
    NT2_TEST_EQUAL(last_index(x,3)  , 2);

    NT2_TEST_EQUAL(first_index<4>(x), 1);
    NT2_TEST_EQUAL(first_index(x,4) , 1);
    NT2_TEST_EQUAL(last_index<4>(x) , 4);
    NT2_TEST_EQUAL(last_index(x,4)  , 4);
  }
}
