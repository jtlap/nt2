/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::pispace function"

#include <nt2/table.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/pispace.hpp>
#include <nt2/include/functions/exp10.hpp>
#include <nt2/include/constants/log10_pi.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <boost/dispatch/meta/nth_hierarchy.hpp>

NT2_TEST_CASE( hierarchy )
{
  using boost::mpl::_;
  using boost::mpl::int_;
  using boost::dispatch::meta::nth_hierarchy;

  NT2_TEST_EXPR_TYPE( (nt2::tag::pispace_() )
                    , (nth_hierarchy<_,int_<0> >)
                    , (nt2::tag::pispace_)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::pispace_() )
                    , (nth_hierarchy<_,int_<1> >)
                    , (nt2::ext::state_constant_< nt2::tag::pispace_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::pispace_() )
                    , (nth_hierarchy<_,int_<2> >)
                    , (nt2::ext::constant_< nt2::tag::pispace_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::pispace_() )
                    , (nth_hierarchy<_,int_<3> >)
                    , (nt2::ext::elementwise_<nt2::tag::pispace_>)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::pispace_() )
                    , (nth_hierarchy<_,int_<4> >)
                    , (nt2::ext::unspecified_<nt2::tag::pispace_>)
                    );
}

NT2_TEST_CASE_TPL( pispace, NT2_REAL_TYPES )
{
  nt2::table<T> x = nt2::pispace(T(2), 50);
  nt2::table<T> ref = nt2::exp10(nt2::linspace(T(2), nt2::Log10_pi<T>(), 50));
  NT2_TEST_EQUAL( x.extent(), nt2::of_size(1,50 ) );
  NT2_TEST_ULP_EQUAL( x, ref, 1.5 );

  ref = nt2::exp10(nt2::linspace(T(2), nt2::Log10_pi<T>(), 50));
  nt2::table<T> xd = nt2::pispace(T(2));

  NT2_TEST_EQUAL( xd.extent(), nt2::of_size(1,50 ) );
  NT2_TEST_ULP_EQUAL( xd, ref, 1.5 );

  ref = nt2::exp10(nt2::linspace(T(2), nt2::Log10_pi<T>(), 7));
  nt2::table<T> x1 = nt2::pispace(T(2),7);

  NT2_TEST_EQUAL( x1.extent(), nt2::of_size(1,7 ) );
  NT2_TEST_ULP_EQUAL( x1, ref, 1.5 );
}
