/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container relative_index"

#include <nt2/table.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/relative_index.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE( integral_subscript )
{
  using nt2::_;
  using nt2::table;
  using nt2::of_size;
  typedef double T;
  boost::dispatch::meta::as_< boost::dispatch::meta::as_integer<T>::type > tgt;

  table<T> a;

  for(int i=1;i<=5;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(a(1337,_)))
                    , 1, 5, i-1, tgt
                    )
                  , 1336
                  );
}

NT2_TEST_CASE( colon_subscript )
{
  using nt2::_;
  using nt2::table;
  using nt2::of_size;
  typedef double T;
  boost::dispatch::meta::as_< boost::dispatch::meta::as_integer<T>::type > tgt;

  table<T> a;

  for(int i=1;i<=5;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(a(_,1)))
                    , 1, 5, i-1, tgt
                    )
                  , i-1
                  );
}

NT2_TEST_CASE( unity_colon_subscript )
{
  using nt2::_;
  using nt2::table;
  using nt2::of_size;
  typedef double T;
  boost::dispatch::meta::as_< boost::dispatch::meta::as_integer<T>::type > tgt;

  table<T> a;

  for(int i=1;i<=3;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(a(_(2,4),1)))
                    , 1, 5, i-1, tgt
                    )
                  , i
                  );
}

NT2_TEST_CASE( strided_colon_subscript )
{
  using nt2::_;
  using nt2::table;
  using nt2::of_size;
  typedef double T;
  boost::dispatch::meta::as_< boost::dispatch::meta::as_integer<T>::type > tgt;

  table<T> a;

  for(int i=1;i<=5;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(a(_(2,3,14),1)))
                    , 1, 5, i-1, tgt
                    )
                  , 3*(i-1)+1
                  );
}

template<class A0, class I0>
typename boost::proto::result_of::
make_expr< nt2::tag::function_
         , A0&
         , typename nt2::meta::
           call< nt2::tag::aggregate_
                 ( I0 const&
                 )
               >::type
         , nt2::box< typename nt2::make_size<1>::type >
         >::type
at_expr(A0& a0, I0 const& i0)
{
  return boost::proto::make_expr<nt2::tag::function_>
         ( boost::ref(a0)
         , nt2::aggregate(i0)
         , nt2::boxify(typename nt2::make_size<1>::type(a0.extent()))
         );
}

template<class A0, class I0, class I1>
typename boost::proto::result_of::
make_expr< nt2::tag::function_
         , A0&
         , typename nt2::meta::
           call< nt2::tag::aggregate_
                 ( I0 const&
                 , I1 const&
                 )
               >::type
         , nt2::box< typename nt2::make_size<2>::type >
         >::type
at_expr(A0& a0, I0 const& i0, I1 const& i1)
{
  return boost::proto::make_expr<nt2::tag::function_>
         ( boost::ref(a0)
         , nt2::aggregate(i0, i1)
         , nt2::boxify(typename nt2::make_size<2>::type(a0.extent()))
         );
}

NT2_TEST_CASE( begin_subscript )
{
  using nt2::begin_;
  using nt2::table;
  using nt2::of_size;
  typedef double T;
  boost::dispatch::meta::as_< boost::dispatch::meta::as_integer<T>::type > tgt;

  table<T> a;
  for(int i=1;i<=5;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(at_expr(a,begin_,1)))
                    , 1, 5, i-1, tgt
                    )
                  , 0
                  );

  for(int i=1;i<=5;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(at_expr(a,begin_+3,1)))
                    , 1, 5, i-1, tgt
                    )
                  , 3
                  );

  for(int i=1;i<=5;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(at_expr(a,2+begin_,1)))
                    , 1, 5, i-1, tgt
                    )
                  , 2
                  );

  for(int i=1;i<=5;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(at_expr(a,begin_,1)))
                    , 0, 5, i-1, tgt
                    )
                  , 0
                  );

  for(int i=1;i<=5;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(at_expr(a,begin_+3,1)))
                    , 0, 5, i-1, tgt
                    )
                  , 3
                  );

  for(int i=1;i<=5;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(at_expr(a,2+begin_,1)))
                    , 0, 5, i-1, tgt
                    )
                  , 2
                  );
}

NT2_TEST_CASE( end_subscript )
{
  using nt2::end_;
  using nt2::table;
  using nt2::of_size;
  typedef double T;
  boost::dispatch::meta::as_< boost::dispatch::meta::as_integer<T>::type > tgt;

  table<T> a;
  for(int i=1;i<=5;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(at_expr(a,end_,1)))
                    , 1, 5, i-1, tgt
                    )
                  , 4
                  );

  for(int i=1;i<=5;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(at_expr(a,end_-3,1)))
                    , 1, 5, i-1, tgt
                    )
                  , 1
                  );

  for(int i=1;i<=5;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(at_expr(a,end_,1)))
                    , 0, 5, i-1, tgt
                    )
                  , 4
                  );

  for(int i=1;i<=5;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(at_expr(a,end_-3,1)))
                    , 0, 5, i-1, tgt
                    )
                  , 1
                  );
}

NT2_TEST_CASE( colon_end_subscript )
{
  using nt2::_;
  using nt2::end_;
  using nt2::begin_;
  using nt2::table;
  using nt2::of_size;
  typedef double T;
  boost::dispatch::meta::as_< boost::dispatch::meta::as_integer<T>::type > tgt;

  table<T> a;

  for(int i=1;i<=5;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(a(_(begin_,end_),1)))
                    , 1, 5, i-1, tgt
                    )
                  , i-1
                  );

  for(int i=1;i<=5;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(a(_(1,end_),1)))
                    , 1, 5, i-1, tgt
                    )
                  , i-1
                  );

  for(int i=1;i<=3;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(a(_(1,end_-2),1)))
                    , 1, 5, i-1, tgt
                    )
                  , i-1
                  );

  for(int i=1;i<=3;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(a(_(3,end_),1)))
                    , 1, 5, i-1, tgt
                    )
                  , i+1
                  );
}

NT2_TEST_CASE( colon_begin_subscript )
{
  using nt2::_;
  using nt2::end_;
  using nt2::begin_;
  using nt2::table;
  using nt2::of_size;
  typedef double T;
  boost::dispatch::meta::as_< boost::dispatch::meta::as_integer<T>::type > tgt;

  table<T> a;

  for(int i=1;i<=5;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(a(_(begin_,5),1)))
                    , 1, 5, i-1, tgt
                    )
                  , i-1
                  );

  for(int i=1;i<=3;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(a(_(begin_,3),1)))
                    , 1, 5, i-1, tgt
                    )
                  , i-1
                  );

  for(int i=1;i<=3;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(a(_(begin_+2,5),1)))
                    , 1, 5, i-1, tgt
                    )
                  , i+1
                  );

  for(int i=1;i<=3;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(a(_(1+begin_,4),1)))
                    , 1, 5, i-1, tgt
                    )
                  , i
                  );

  for(int i=1;i<=3;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(a(_(1+begin_+1,5),1)))
                    , 1, 5, i-1, tgt
                    )
                  , i+1
                  );
}

NT2_TEST_CASE( colon_begin_step_end_subscript )
{
  using nt2::_;
  using nt2::end_;
  using nt2::begin_;
  using nt2::table;
  using nt2::of_size;
  typedef double T;
  boost::dispatch::meta::as_< boost::dispatch::meta::as_integer<T>::type > tgt;

  table<T> a;

  for(int i=1;i<=5;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(a(_(end_,-1,begin_),1)))
                    , 1, 5, i-1, tgt
                    )
                  , 4 + -1 *(i-1)
                  );

  for(int i=1;i<=3;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(a(_(begin_,2,end_),1)))
                    , 1, 5, i-1, tgt
                    )
                  , 2*(i-1)
                  );

  for(int i=1;i<=2;i++)
    NT2_TEST_EQUAL( nt2::relative_index
                    ( boost::proto::
                      child_c<0>(boost::proto::child_c<1>(a(_(begin_+1,2,end_-1),1)))
                    , 1, 5, i-1, tgt
                    )
                  , 1+2*(i-1)
                  );

}
