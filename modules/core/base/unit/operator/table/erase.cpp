//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 container erase"

#include <nt2/table.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/erase.hpp>

#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/cat.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

template<class T>
struct size_of
{
  typedef typename nt2::meta::settings_of<T>::type settings;
  typedef typename nt2::meta::option<settings, nt2::tag::of_size_>::type type;
};

NT2_TEST_CASE( erase_function )
{
  using nt2::_;
  using nt2::of_size_;
  using nt2::of_size;
  typedef float T;

  nt2::table<T> a = nt2::cat(boost::mpl::int_<4>(), nt2::cat(boost::mpl::int_<3>(), nt2::vertcat(_(T(1), T(4)), _(T(5), T(8)))
                                                            , nt2::cat(boost::mpl::int_<3>(), nt2::vertcat(_(T(9), T(12)), _(T(13), T(16)))
                                                                                            , nt2::vertcat(_(T(17), T(20)), _(T(21), T(24)))
                                                                      )
                                                            )
                                                  , nt2::cat(boost::mpl::int_<3>(), nt2::vertcat(_(T(25), T(28)), _(T(29), T(32)))
                                                            , nt2::cat(boost::mpl::int_<3>(), nt2::vertcat(_(T(33), T(36)), _(T(37), T(40)))
                                                                                            , nt2::vertcat(_(T(41), T(44)), _(T(45), T(48)))
                                                                      )
                                                            )
                            );
  nt2::table<T> b = nt2::cat(boost::mpl::int_<3>(), nt2::vertcat( _(T(9), T(12)), _(T(13), T(16)) )
                                                  , nt2::vertcat( _(T(17), T(20)), _(T(21), T(24)) )
                            );
  nt2::table<T> c = nt2::cat(boost::mpl::int_<3>(), nt2::vertcat( _(T(10), T(12)), _(T(14), T(16)) )
                                                  , nt2::vertcat( _(T(18), T(20)), _(T(22), T(24)) )
                            );

  nt2::erase(a, nt2::aggregate(_, _, 1, 1));
  NT2_TEST_EQUAL(a, b);

  a = b;
  nt2::erase(a, nt2::aggregate(_, 1, _));
  NT2_TEST_EQUAL(a, c);

  a = b;
  a(_, 1, _) = _();
  NT2_TEST_EQUAL(a, c);

  a = c;
  nt2::erase(a, nt2::aggregate(1, 1, 1));
  NT2_TEST_EQUAL(a, nt2::cons<T>(of_size(1, 11), 14, 11, 15, 12, 16, 18, 22, 19, 23, 20, 24));

  nt2::erase(b, nt2::aggregate(1, _, 1));
  NT2_TEST_EQUAL(b, nt2::cons<T>(of_size(1, 12), 13, 14, 15, 16, 17, 21, 18, 22, 19, 23, 20, 24));
}

NT2_TEST_CASE( erase_along )
{
  using nt2::_;
  using nt2::of_size_;
  using nt2::of_size;
  typedef float T;

  nt2::table<T> a = nt2::cat(boost::mpl::int_<3>(), nt2::vertcat(_(T(1), T(4)), _(T(5), T(8)))
                                                  , nt2::cat(boost::mpl::int_<3>(), nt2::vertcat(_(T(9), T(12)), _(T(13), T(16)))
                                                                                 , nt2::vertcat(_(T(17), T(20)), _(T(21), T(24)))
                                                            )
                            );
  nt2::table<T> b = nt2::cat(boost::mpl::int_<3>(), nt2::vertcat( _(T(9), T(12)), _(T(13), T(16)) )
                                                  , nt2::vertcat( _(T(17), T(20)), _(T(21), T(24)) )
                            );

  nt2::erase(a, 1, 3);
  NT2_TEST_EQUAL(a, b);
}
