//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/dispatch/meta/nth_hierarchy.hpp>

NT2_TEST_CASE( hierarchy )
{
  using boost::mpl::_;
  using boost::mpl::int_;
  using boost::dispatch::meta::nth_hierarchy;

  NT2_TEST_EXPR_TYPE( (nt2::tag::ind2sub_() )
                    , (nth_hierarchy<_,int_<0> >)
                    , (nt2::tag::ind2sub_)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::ind2sub_() )
                    , (nth_hierarchy<_,int_<1> >)
                    , (nt2::ext::tieable_< nt2::tag::ind2sub_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::ind2sub_() )
                    , (nth_hierarchy<_,int_<2> >)
                    , (nt2::ext::unspecified_<nt2::tag::ind2sub_>)
                    );
}

NT2_TEST_CASE_TPL( value_type, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::table;
  using nt2::of_size;
  using nt2::meta::value_type_;

  nt2::table<int> sz( of_size(1,4) );

  // IND is a scalar + all variants od size/base
  NT2_TEST_EXPR_TYPE( ( nt2::ind2sub(1,T(1)) )
                    , (value_type_<_>)
                    , (T)
                    );

  NT2_TEST_EXPR_TYPE( ( nt2::ind2sub( of_size(2,2),T(1) ) )
                    , (value_type_<_>)
                    , (T)
                    );

  NT2_TEST_EXPR_TYPE( ( nt2::ind2sub( sz, T(1) ) )
                    , (value_type_<_>)
                    , (T)
                    );

  NT2_TEST_EXPR_TYPE( ( nt2::ind2sub(1,T(1), 0) )
                    , (value_type_<_>)
                    , (T)
                    );

  NT2_TEST_EXPR_TYPE( ( nt2::ind2sub( of_size(2,2),T(1), 0) )
                    , (value_type_<_>)
                    , (T)
                    );

  NT2_TEST_EXPR_TYPE( ( nt2::ind2sub( sz, T(1), 0 ) )
                    , (value_type_<_>)
                    , (T)
                    );

  // IND is a expr + all variants od size/base
  nt2::table<T> inds;

  NT2_TEST_EXPR_TYPE( ( nt2::ind2sub(1,inds) )
                    , (value_type_<_>)
                    , (T)
                    );

  NT2_TEST_EXPR_TYPE( ( nt2::ind2sub(of_size(2,2),inds) )
                    , (value_type_<_>)
                    , (T)
                    );

  NT2_TEST_EXPR_TYPE( ( nt2::ind2sub( sz, inds ) )
                    , (value_type_<_>)
                    , (T)
                    );

  NT2_TEST_EXPR_TYPE( ( nt2::ind2sub(1,inds,0) )
                    , (value_type_<_>)
                    , (T)
                    );

  NT2_TEST_EXPR_TYPE( ( nt2::ind2sub(of_size(2,2),inds,0) )
                    , (value_type_<_>)
                    , (T)
                    );

  NT2_TEST_EXPR_TYPE( ( nt2::ind2sub( sz, inds,0 ) )
                    , (value_type_<_>)
                    , (T)
                    );
}

NT2_TEST_CASE_TPL( ind2sub, (double)(float)(int) )
{
  using nt2::table;
  using nt2::ind2sub;
  using nt2::of_size;
  using nt2::tie;
  using nt2::cons;
  using nt2::ones;

  table<T> inds,x,y,z,w;

  table<T> rx = cons(T(1),T(2),T(1),T(2),T(1),T(2),T(1),T(2));
  table<T> ry = cons(T(1),T(1),T(2),T(2),T(3),T(3),T(4),T(4));
  table<T> rz = cons(T(1),T(1),T(1),T(1),T(2),T(2),T(2),T(2));

  inds = cons(T(1),T(2),T(3),T(4),T(5),T(6),T(7),T(8));

  x = ind2sub(of_size(2,2,2), inds);
  NT2_TEST_EQUAL(x, inds);
  NT2_TEST_EQUAL(x.extent(), inds.extent());

  nt2::tie(x,y) = ind2sub(of_size(2,4), inds);
  NT2_TEST_EQUAL(x, rx);
  NT2_TEST_EQUAL(x.extent(), inds.extent());
  NT2_TEST_EQUAL(y, ry);
  NT2_TEST_EQUAL(y.extent(), inds.extent());

  ry = cons(T(1),T(1),T(2),T(2),T(1),T(1),T(2),T(2));
  nt2::tie(x,y,z,w) = ind2sub(of_size(2,2,2), inds);
  NT2_TEST_EQUAL(x, rx);
  NT2_TEST_EQUAL(x.extent(), inds.extent());
  NT2_TEST_EQUAL(y, ry);
  NT2_TEST_EQUAL(y.extent(), inds.extent());
  NT2_TEST_EQUAL(z, rz);
  NT2_TEST_EQUAL(z.extent(), inds.extent());
  NT2_TEST_EQUAL(w, ones(inds.extent()));
  NT2_TEST_EQUAL(w.extent(), inds.extent());
}

NT2_TEST_CASE_TPL( ind2sub_index, (double)(float)(int) )
{
  using nt2::table;
  using nt2::ind2sub;
  using nt2::of_size;
  using nt2::tie;
  using nt2::cons;
  using nt2::ones;

  table<T> inds,x,y,z,w;

  table<T> rx = cons(T(0),T(1),T(0),T(1),T(0),T(1),T(0),T(1));
  table<T> ry = cons(T(0),T(0),T(1),T(1),T(2),T(2),T(3),T(3));
  table<T> rz = cons(T(0),T(0),T(0),T(0),T(1),T(1),T(1),T(1));

  inds = cons(T(0),T(1),T(2),T(3),T(4),T(5),T(6),T(7));

  x = ind2sub(of_size(2,2,2), inds, 0);
  NT2_TEST_EQUAL(x, inds);
  NT2_TEST_EQUAL(x.extent(), inds.extent());

  nt2::tie(x,y) = ind2sub(of_size(2,4), inds, 0);
  NT2_TEST_EQUAL(x, rx);
  NT2_TEST_EQUAL(x.extent(), inds.extent());
  NT2_TEST_EQUAL(y, ry);
  NT2_TEST_EQUAL(y.extent(), inds.extent());

  ry = cons(T(0),T(0),T(1),T(1),T(0),T(0),T(1),T(1));
  nt2::tie(x,y,z,w) = ind2sub(of_size(2,2,2), inds, 0);
  NT2_TEST_EQUAL(x, rx);
  NT2_TEST_EQUAL(x.extent(), inds.extent());
  NT2_TEST_EQUAL(y, ry);
  NT2_TEST_EQUAL(y.extent(), inds.extent());
  NT2_TEST_EQUAL(z, rz);
  NT2_TEST_EQUAL(z.extent(), inds.extent());
  NT2_TEST_EQUAL(w, zeros(inds.extent()));
  NT2_TEST_EQUAL(w.extent(), inds.extent());
}
