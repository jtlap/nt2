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

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <nt2/core/settings/forward/alignment.hpp>
#include <nt2/core/settings/forward/index.hpp>
#include <nt2/core/settings/forward/storage_order.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/utility/position/position.hpp>
#include <nt2/core/utility/position/adapted.hpp>
#include <nt2/core/utility/position/alignment.hpp>

template<class T> struct hierarchy
{
  typedef typename boost::dispatch::meta::hierarchy_of<T>::type type;
};

template<class T> struct hierarchy_parent
{
  typedef typename boost::dispatch::meta::hierarchy_of<T>::type::parent type;
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
  using boost::mpl::_;
  using namespace nt2;

  // Aligned
  position<vector<int, int>,
           index_<1l, 1l>,
           matlab_order_,
           aligned_
    > p1(make_vector(12,13));

  NT2_TEST_EQUAL(size(p1), 2);
  NT2_TEST_EQUAL(at_c<0>(p1), 12);
  NT2_TEST_EQUAL(at_c<1>(p1), 13);

  // Unaligned
  position<vector<int, int>,
           index_<1l, 1l>,
           matlab_order_,
           unaligned_
    > p2(make_vector(12,13));

  NT2_TEST_EQUAL(size(p2), 2);
  NT2_TEST_EQUAL(at_c<0>(p2), 12);
  NT2_TEST_EQUAL(at_c<1>(p2), 13);

  // From a fusion view
  position<vector<int, int>,
           index_<1l, 1l>,
           matlab_order_,
           unaligned_
    > p3(p2);
  NT2_TEST_EQUAL(size(p3), 2);
  NT2_TEST_EQUAL(at_c<0>(p3), 12);
  NT2_TEST_EQUAL(at_c<1>(p3), 13);

  // From a fusion view with a different alignment
  position<vector<int, int>,
           index_<1l, 1l>,
           matlab_order_,
           unaligned_
    > p4(p1);
  NT2_TEST_EQUAL(size(p4), 2);
  NT2_TEST_EQUAL(at_c<0>(p4), 12);
  NT2_TEST_EQUAL(at_c<1>(p4), 13);
}

////////////////////////////////////////////////////////////////////////////////
// Test make_position
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( make_position )
{
  using boost::fusion::vector;
  using boost::fusion::make_vector;
  using boost::mpl::_;
  using namespace nt2;

  typedef container::table<float, _2D> table_type;
  typedef vector<int, int> seq_type;
  typedef typename meta::make_position<table_type, seq_type>::type position_type;

  seq_type s = make_vector(12, 13);
  position_type p(s);

  NT2_TEST_EXPR_TYPE( p,
                      model<_>,
                      (model<position<vector<int, int>,
                       index_<1l, 1l>,
                       matlab_order_,
                       aligned_> >::type)
                    );
}

////////////////////////////////////////////////////////////////////////////////
// Test that hierarchy_of is correct for position
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( hierarchy_of_position )
{
  using boost::fusion::vector;
  using boost::fusion::make_vector;
  using boost::fusion::at_c;
  using boost::mpl::int_;
  using boost::mpl::_;
  using namespace nt2;
  using namespace boost::dispatch::meta;

  typedef position<vector<int, int>,
            index_<1l, 1l>,
            matlab_order_,
            aligned_
          > aligned_2d_position;
  typedef position<vector<int, int, int>,
            index_<1l, 1l>,
            matlab_order_,
            aligned_
          > aligned_2d_position_a;
  typedef position<vector<unsigned long long int, unsigned long long int>,
            index_<1l, 1l>,
            matlab_order_,
            aligned_
          > aligned_2d_position_b;

  aligned_2d_position p1(make_vector(12,13)); 
  aligned_2d_position_a p1a(make_vector(12,13,14)); 
  aligned_2d_position_b p1b(make_vector(12,13));
 
  NT2_TEST_EXPR_TYPE( p1,
                      hierarchy<_>,
                      (position_<aligned_2d_position,
                       aligned_>)
                    );
  NT2_TEST_EXPR_TYPE( p1a,
                      hierarchy<_>,
                      (position_<aligned_2d_position_a,
                       aligned_> )
                    );
  NT2_TEST_EXPR_TYPE( p1b,
                      hierarchy<_>,
                      (position_<aligned_2d_position_b,
                       aligned_> )
                    );

  typedef position<vector<int, int>,
            index_<1l, 1l>,
            matlab_order_,
            unaligned_
          > unaligned_2d_position;
  typedef position<vector<int, int, int>,
            index_<1l, 1l>,
            matlab_order_,
            unaligned_
          > unaligned_2d_position_a;
  typedef position<vector<unsigned long long int, unsigned long long int>,
            index_<1l, 1l>,
            matlab_order_,
            unaligned_
          > unaligned_2d_position_b;

  unaligned_2d_position p2(make_vector(12,13));
  unaligned_2d_position_a p2a(make_vector(12,13,14));
  unaligned_2d_position_b p2b(make_vector(12,13));

  NT2_TEST_EXPR_TYPE( p2,
                      hierarchy<_>,
                      (boost::dispatch::meta::position_<unaligned_2d_position,
                       unaligned_> )
                    );
  NT2_TEST_EXPR_TYPE( p2a,
                      hierarchy<_>,
                      (boost::dispatch::meta::position_<unaligned_2d_position_a,
                       unaligned_> )
                    );
  NT2_TEST_EXPR_TYPE( p2b,
                      hierarchy<_>,
                      (boost::dispatch::meta::position_<unaligned_2d_position_b,
                       unaligned_> )
                    );

  typedef container::table<float, _2D> table_type;
  typedef typename meta::make_position<table_type, vector<> >::type position_type;
  position_type p3(make_vector());

  NT2_TEST_EXPR_TYPE( p3,
                      hierarchy<_>,
                      (position_<position_type, aligned_>)
                    );

  NT2_TEST_EXPR_TYPE( p1,
                      hierarchy_parent<_>,
                      (position_<aligned_2d_position, unaligned_>)
                    );

  NT2_TEST_EXPR_TYPE( p2,
                      hierarchy_parent<_>,
                      (fusion_sequence_<unaligned_2d_position>)
                    );
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
  using namespace nt2;

  position<vector<int, int>,
           index_<1l, 1l>,
           matlab_order_,
           unaligned_
    > p1(make_vector(12,13));

  position<vector<int, int>,
           index_<1l, 1l>,
           matlab_order_,
           aligned_
    > p2 = as_aligned(p1);

  NT2_TEST_EXPR_TYPE( as_aligned(p1),
                      model<_>,
                      (model<position<vector<int, int>,
                        index_<1l, 1l>,
                        matlab_order_,
                        aligned_> >::type)
                    );

  vector<int, int> seq = make_vector(12, 13);
  NT2_TEST_EXPR_TYPE( as_aligned(p1, seq),
                      model<_>,
                      (model<position<vector<int, int>,
                        index_<1l, 1l>,
                        matlab_order_,
                        aligned_> >::type)
                    );
  
  NT2_TEST_EXPR_TYPE( as_aligned(seq),
                      model<_>,
                      (model<position<vector<int, int>,
                        index_<1l, 1l>,
                        matlab_order_,
                        aligned_> >::type)
                    );

  NT2_TEST_EXPR_TYPE( as_aligned(seq, index_<1l, 1l>()),
                      model<_>,
                      (model<position<vector<int, int>,
                        index_<1l, 1l>,
                        matlab_order_,
                        aligned_> >::type)
                    );

  NT2_TEST_EXPR_TYPE( as_aligned(seq, index_<1l, 1l>(), C_order_()),
                      model<_>,
                      (model<position<vector<int, int>,
                        index_<1l, 1l>,
                        C_order_,
                        aligned_> >::type)
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
  using namespace nt2;

  position<vector<int, int>,
           index_<1l, 1l>,
           matlab_order_,
           aligned_
    > p1(make_vector(12,13));

  position<vector<int, int>,
           index_<1l, 1l>,
           matlab_order_,
           unaligned_
    > p2 = as_unaligned(p1);

  NT2_TEST_EXPR_TYPE( as_unaligned(p1),
                      model<_>,
                      (model<position<vector<int, int>,
                        index_<1l, 1l>,
                        matlab_order_,
                        unaligned_> >::type)
                    );

  vector<int, int> seq = make_vector(12, 13);
  NT2_TEST_EXPR_TYPE( as_unaligned(p1, seq),
                      model<_>,
                      (model<position<vector<int, int>,
                        index_<1l, 1l>,
                        matlab_order_,
                        unaligned_> >::type)
                    );

  NT2_TEST_EXPR_TYPE( as_unaligned(seq),
                      model<_>,
                      (model<position<vector<int, int>,
                        index_<1l, 1l>,
                        matlab_order_,
                        unaligned_> >::type)
                    );

  NT2_TEST_EXPR_TYPE( as_unaligned(seq, index_<1l, 1l>()),
                      model<_>,
                      (model<position<vector<int, int>,
                        index_<1l, 1l>,
                        matlab_order_,
                        unaligned_> >::type)
                    );

  NT2_TEST_EXPR_TYPE( as_unaligned(seq, index_<1l, 1l>(), C_order_()),
                      model<_>,
                      (model<position<vector<int, int>,
                        index_<1l, 1l>,
                        C_order_,
                        unaligned_> >::type)
                    );
}
