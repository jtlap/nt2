//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "position"

#include <boost/fusion/sequence.hpp>
#include <boost/fusion/include/sequence.hpp>
#include <boost/array.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <nt2/core/utility/position/position.hpp>
#include <nt2/core/utility/position/adapted.hpp>
#include <nt2/core/utility/position/alignment.hpp>
#include <nt2/core/settings/storage_order.hpp>
#include <nt2/core/settings/alignment.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

template<class T> struct hierarchy
{
  typedef typename boost::dispatch::meta::hierarchy_of<T>::type type;
};

template<class T> struct model
{
  typedef typename boost::dispatch::meta::model_of<T>::type type;
};

////////////////////////////////////////////////////////////////////////////////
// Test position
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( position )
{
  using boost::fusion::vector;
  using boost::fusion::make_vector;
  using boost::fusion::at_c;
  using boost::mpl::int_;
  using nt2::position;

  // Aligned
  position<vector<int, int>,
           int_<2>,
           int_<0>,
           nt2::matlab_order_,
           nt2::aligned_
    > p1(make_vector(12,13));

  NT2_TEST_EQUAL(size(p1), 2);
  NT2_TEST_EQUAL(at_c<0>(p1), 12);
  NT2_TEST_EQUAL(at_c<1>(p1), 13);

  // Unaligned
  position<vector<int, int>,
           int_<2>,
           int_<0>,
           nt2::matlab_order_,
           nt2::unaligned_
    > p2(make_vector(12,13));

  NT2_TEST_EQUAL(size(p2), 2);
  NT2_TEST_EQUAL(at_c<0>(p2), 12);
  NT2_TEST_EQUAL(at_c<1>(p2), 13);

  // From a fusion view
  position<vector<int, int>,
           int_<2>,
           int_<0>,
           nt2::matlab_order_,
           nt2::unaligned_
    > p3(p2);
  NT2_TEST_EQUAL(size(p3), 2);
  NT2_TEST_EQUAL(at_c<0>(p3), 12);
  NT2_TEST_EQUAL(at_c<1>(p3), 13);

  // From a fusion view with a different alignment
  position<vector<int, int>,
           int_<2>,
           int_<0>,
           nt2::matlab_order_,
           nt2::unaligned_
    > p4(p1);
  NT2_TEST_EQUAL(size(p4), 2);
  NT2_TEST_EQUAL(at_c<0>(p4), 12);
  NT2_TEST_EQUAL(at_c<1>(p4), 13);
}

////////////////////////////////////////////////////////////////////////////////
// Test that hierarchy_of is correct for position
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(hierarchy_of_position)
{
  using boost::fusion::vector;
  using boost::fusion::make_vector;
  using boost::fusion::at_c;
  using boost::mpl::int_;
  using boost::mpl::_;
  using nt2::position;

  using boost::is_same;
  using namespace boost::dispatch::meta;

  typedef position<vector<int, int>,
            int_<2>,
            int_<0>,
            nt2::matlab_order_,
            nt2::aligned_
          > aligned_2d_position;
  typedef position<vector<int, int, int>,
            int_<3>,
            int_<0>,
            nt2::matlab_order_,
            nt2::aligned_
          > aligned_2d_position_a;
  typedef position<vector<unsigned long long int, unsigned long long int>,
            int_<2>,
            int_<0>,
            nt2::matlab_order_,
            nt2::aligned_
          > aligned_2d_position_b;

  aligned_2d_position p1(make_vector(12,13)); 
  aligned_2d_position_a p1a(make_vector(12,13,14)); 
  aligned_2d_position_b p1b(make_vector(12,13));
 
  NT2_TEST_EXPR_TYPE( p1,
                      hierarchy<_>,
                      (boost::dispatch::meta::position_<vector<int, int>,
                       nt2::aligned_, aligned_2d_position>));
  NT2_TEST_EXPR_TYPE( p1a,
                      hierarchy<_>,
                      (boost::dispatch::meta::position_<vector<int, int, int>,
                       nt2::aligned_, aligned_2d_position_a> ));
  NT2_TEST_EXPR_TYPE( p1b,
                      hierarchy<_>,
                      (boost::dispatch::meta::position_<vector<unsigned long long int, unsigned long long int>,
                       nt2::aligned_, aligned_2d_position_b> ));

  typedef position<vector<int, int>,
            int_<2>,
            int_<0>,
            nt2::matlab_order_,
            nt2::unaligned_
          > unaligned_2d_position;
  typedef position<vector<int, int, int>,
            int_<3>,
            int_<0>,
            nt2::matlab_order_,
            nt2::unaligned_
          > unaligned_2d_position_a;
  typedef position<vector<unsigned long long int, unsigned long long int>,
            int_<2>,
            int_<0>,
            nt2::matlab_order_,
            nt2::unaligned_
          > unaligned_2d_position_b;

  unaligned_2d_position p2(make_vector(12,13));
  unaligned_2d_position_a p2a(make_vector(12,13,14)); 
  unaligned_2d_position_b p2b(make_vector(12,13));

  NT2_TEST_EXPR_TYPE( p2,
                      hierarchy<_>,
                      (boost::dispatch::meta::position_<vector<int, int>,
                       nt2::unaligned_, unaligned_2d_position> ));
  NT2_TEST_EXPR_TYPE( p2a,
                      hierarchy<_>,
                      (boost::dispatch::meta::position_<vector<int, int, int>,
                       nt2::unaligned_, unaligned_2d_position_a> ));
  NT2_TEST_EXPR_TYPE( p2b,
                      hierarchy<_>,
                      (boost::dispatch::meta::position_<vector<unsigned long long int, unsigned long long int>,
                       nt2::unaligned_, unaligned_2d_position_b> ));
}

////////////////////////////////////////////////////////////////////////////////
// Test as_aligned
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( as_aligned )
{
  using boost::fusion::vector;
  using boost::fusion::make_vector;
  using boost::fusion::at_c;
  using boost::mpl::int_;
  using boost::mpl::_;
  using nt2::position;

  using boost::is_same;

  position<vector<int, int>,
           int_<2>,
           int_<0>,
           nt2::matlab_order_,
           nt2::unaligned_
    > p1(make_vector(12,13));

  position<vector<int, int>,
           int_<2>,
           int_<0>,
           nt2::matlab_order_,
           nt2::aligned_
    > p2 = as_aligned(p1);

  NT2_TEST_EXPR_TYPE( as_aligned(p1),
                      model<_>,
                      (model<position<vector<int, int>,
                        int_<2>,
                        int_<0>,
                        nt2::matlab_order_,
                        nt2::aligned_> >::type)
                    );
}

////////////////////////////////////////////////////////////////////////////////
// Test as_unaligned
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( as_unaligned )
{
  using boost::fusion::vector;
  using boost::fusion::make_vector;
  using boost::fusion::at_c;
  using boost::mpl::int_;
  using boost::mpl::_;
  using nt2::position;

  using boost::is_same;

  position<vector<int, int>,
           int_<2>,
           int_<0>,
           nt2::matlab_order_,
           nt2::aligned_
    > p1(make_vector(12,13));

  position<vector<int, int>,
           int_<2>,
           int_<0>,
           nt2::matlab_order_,
           nt2::unaligned_
    > p2 = as_unaligned(p1);

  NT2_TEST_EXPR_TYPE( as_unaligned(p1),
                      model<_>,
                      (model<position<vector<int, int>,
                        int_<2>,
                        int_<0>,
                        nt2::matlab_order_,
                        nt2::unaligned_> >::type)
                    );
}
