//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::dispatch::meta counter test"

#include <boost/dispatch/meta/counter.hpp>
#include <boost/mpl/int.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

BOOST_DISPATCH_COUNTER_INIT(counter_test)

using boost::mpl::int_;
using boost::mpl::_;

static void f()
{
  NT2_TEST_EXPR_TYPE( int_< BOOST_DISPATCH_COUNTER_VALUE(counter_test) >()
                    , _
                    , int_<0>
                    );
}

BOOST_DISPATCH_COUNTER_INCREMENT(counter_test)

static void g()
{
  NT2_TEST_EXPR_TYPE( int_< BOOST_DISPATCH_COUNTER_VALUE(counter_test) >()
                    , _
                    , int_<1>
                    );
}

template<class T>
static void foo(T const&)
{
#if 0 // not implemented reliably yet
  NT2_TEST_EXPR_TYPE( int_< BOOST_DISPATCH_COUNTER_VALUE(counter_test) >()
                    , _
                    , int_<1>
                    );
#endif
}

template<class T>
static void bar(T const&)
{
  NT2_TEST_EXPR_TYPE( int_< BOOST_DISPATCH_COUNTER_VALUE_TPL(counter_test, T) >()
                    , _
                    , int_<2>
                    );
}

BOOST_DISPATCH_COUNTER_INCREMENT(counter_test)

static void h()
{
  NT2_TEST_EXPR_TYPE( int_< BOOST_DISPATCH_COUNTER_VALUE(counter_test) >()
                    , _
                    , int_<2>
                    );
}

NT2_TEST_CASE(counter)
{
  f();
  g();
  h();
  foo(0);
  bar(0);
}
