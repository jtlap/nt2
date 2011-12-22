//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::settings size is an option"

#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some of_size_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_of_size_ )
{
  using nt2::_2D;
  using nt2::of_size_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( (_2D())
                      ,(option< _, nt2::tag::of_size_>)
                      ,(_2D)
                      );

  NT2_TEST_EXPR_TYPE( (of_size_<3,4>())
                      ,(option< _, nt2::tag::of_size_>)
                      ,(of_size_<3,4>)
                      );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some of_size_ as default and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_of_size_default )
{
  using nt2::_2D;
  using nt2::of_size_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( (_2D())
                      ,(option< void, nt2::tag::of_size_,_>)
                      ,(_2D)
                      );

  NT2_TEST_EXPR_TYPE( (of_size_<3,4>())
                      ,(option< void, nt2::tag::of_size_,_>)
                      ,(of_size_<3,4>)
                      );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some of_size_ as a setting and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( setting_of_size_ )
{
  using nt2::_2D;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  nt2::settings dim_2D      (of_size_<3,4>, _2D);
  nt2::settings dim_of_size (_2D  , of_size_<3,4>);

  NT2_TEST_EXPR_TYPE( dim_2D
                      ,(option< void, nt2::tag::of_size_,_>)
                      ,(_2D)
                      );

  NT2_TEST_EXPR_TYPE( dim_of_size
                      ,(option< void, nt2::tag::of_size_,_>)
                      ,(of_size_<3,4>)
                      );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some of_size_ as a default setting and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( setting_of_size_default )
{
  using nt2::_2D;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( (_2D())
                      ,(option< settings(long,int), nt2::tag::of_size_,_>)
                      ,(_2D)
                      );

  NT2_TEST_EXPR_TYPE( (of_size_<3,4>())
                      ,(option< settings(long,int), nt2::tag::of_size_,_>)
                      ,(of_size_<3,4>)
                      );
}
