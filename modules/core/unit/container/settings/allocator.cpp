/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::settings allocator_ is an option"

#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/allocator.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some allocator_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_allocator )
{
   using std::allocator;
   using nt2::allocator_;
   using nt2::meta::option;
   using boost::mpl::_;

   NT2_TEST_EXPR_TYPE( (allocator_<allocator<float> > ())
                       ,(option< _, nt2::tag::allocator_>)
                       ,(allocator_< allocator<float> >)
                     );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some allocator_ as option with a default
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_allocator_default )
{
  using std::allocator;
  using nt2::allocator_;
  using nt2::meta::option;
  using boost::mpl::_;

   NT2_TEST_EXPR_TYPE( (allocator_<allocator<int> > ())
                       ,(option< void, nt2::tag::allocator_, _>)
                       ,(allocator_< allocator<int> >)
                     );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some allocator_ as settings
////////////////////////////////////////////////////////////////////////////////
nt2::settings alloc_int(nt2::allocator_<std::allocator<float> >
                        ,nt2::allocator_<std::allocator<int> > );
NT2_TEST_CASE( single_allocator_settings )
{
  using std::allocator;
  using nt2::allocator_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( alloc_int
                      ,(option<_ , nt2::tag::allocator_>)
                      ,(allocator_<allocator<int> >)
                      );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some allocator_ as settings with a default
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_allocator_settings_default )
{
  using std::allocator;
  using nt2::allocator_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

   NT2_TEST_EXPR_TYPE((allocator_<allocator<int> > ())
                      ,(option< settings(double,long), nt2::tag::allocator_, _>)
                      ,(allocator_< allocator<int> >)
                     );
}
