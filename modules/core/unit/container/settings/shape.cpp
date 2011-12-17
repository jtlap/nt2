/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::settings shape is an option"

#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/shape.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some shape_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( shape_ )
{
  using nt2::rectangular_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( rectangular_()
                      ,(option< _, nt2::tag::shape_>)
                      ,(rectangular_)
                      );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some shape_ as default and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( shape_default )
{
  using nt2::rectangular_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( rectangular_()
                      ,(option< void, nt2::tag::shape_,_>)
                      ,(rectangular_)
                      );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some shape_ as a setting and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
nt2::settings rect  (nt2::rectangular_, nt2::rectangular_);
NT2_TEST_CASE( setting_shape_ )
{
  using nt2::rectangular_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;


  NT2_TEST_EXPR_TYPE( rect
                      ,(option<_ , nt2::tag::shape_>)
                      ,(rectangular_)
                      );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some shape_ as a default setting and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( setting_shape_default )
{
  using nt2::rectangular_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( rectangular_()
                      ,(option< settings(long,int), nt2::tag::shape_,_>)
                      ,(rectangular_)
                      );
}
