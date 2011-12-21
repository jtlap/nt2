//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::settings alignment is an option"

#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/alignment.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some alignment_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( alignment_ )
{
  using nt2::aligned_;
  using nt2::unaligned_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( aligned_()
                      ,(option< _, nt2::tag::alignment_>)
                      ,(aligned_)
                      );

  NT2_TEST_EXPR_TYPE( unaligned_()
                      ,(option< _, nt2::tag::alignment_>)
                      ,(unaligned_)
                      );

}

////////////////////////////////////////////////////////////////////////////////
// Pass some alignment_ as default and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( alignment_default )
{
  using nt2::aligned_;
  using nt2::unaligned_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( aligned_()
                      ,(option< void, nt2::tag::alignment_, _>)
                      ,(aligned_)
                      );

  NT2_TEST_EXPR_TYPE( unaligned_()
                      ,(option< void, nt2::tag::alignment_, _>)
                      ,(unaligned_)
                      );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some alignment_ as a setting and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
nt2::settings align  (nt2::unaligned_, nt2::aligned_);
nt2::settings unalign(nt2::aligned_  , nt2::unaligned_);
NT2_TEST_CASE( setting_alignment_ )
{
  using nt2::aligned_;
  using nt2::unaligned_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( align
                      ,(option<_ , nt2::tag::alignment_>)
                      ,(aligned_)
                      );

  NT2_TEST_EXPR_TYPE( unalign
                      ,(option<_ , nt2::tag::alignment_>)
                      ,(unaligned_)
                      );

}

////////////////////////////////////////////////////////////////////////////////
// Pass some alignment_ as a default setting and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( setting_alignment_default )
{
  using nt2::aligned_;
  using nt2::unaligned_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( aligned_()
                      ,(option<settings(long,int), nt2::tag::alignment_,_>)
                      ,(aligned_)
                      );

  NT2_TEST_EXPR_TYPE( unaligned_()
                      ,(option<settings(long,int), nt2::tag::alignment_,_>)
                      ,(unaligned_)
                      );
}
