/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::settings alignment is an option"

#include <boost/type_traits/is_same.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/alignment.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some alignment_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_alignment_ )
{
  using nt2::aligned_;
  using nt2::unaligned_;
  using nt2::alignment_;
  using boost::is_same;
  using nt2::meta::option;

  NT2_TEST( ( is_same < aligned_
              , option< alignment_<aligned_>, nt2::tag::alignment_ >::type 
                      >::value
            ) 
          );

  NT2_TEST( ( is_same < unaligned_
              , option< alignment_<unaligned_>, nt2::tag::alignment_ >::type 
                      >::value
            ) 
          );

}

////////////////////////////////////////////////////////////////////////////////
// Pass some alignment_ as default and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( single_alignment_default )
{
  using nt2::aligned_;
  using nt2::unaligned_;
  using nt2::alignment_;
  using boost::is_same;
  using nt2::meta::option;

  NT2_TEST( ( is_same < aligned_
              , option< void, nt2::tag::alignment_, alignment_<aligned_> >::type 
                      >::value
            ) 
          );

  NT2_TEST( ( is_same < unaligned_
              , option< void, nt2::tag::alignment_, alignment_<unaligned_> >::type 
              >::value
            ) 
          );

}

////////////////////////////////////////////////////////////////////////////////
// Pass some alignment_ as a setting and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( setting_alignment_ )
{
  using nt2::aligned_;
  using nt2::unaligned_;
  using nt2::alignment_;
  using nt2::settings;
  using boost::is_same;
  using nt2::meta::option;

  NT2_TEST( ( is_same < aligned_
              , option< settings(alignment_<unaligned_>, 
                                 alignment_<aligned_>)
                              , nt2::tag::alignment_ 
                              >::type 
                      >::value
            ) 
          );


  NT2_TEST( ( is_same < unaligned_
              , option< settings(alignment_<aligned_>, 
                                 alignment_<unaligned_>)
                              , nt2::tag::alignment_ 
                              >::type 
                      >::value
            ) 
          );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some alignment_ as a default setting and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( setting_alignment_default )
{
  using nt2::aligned_;
  using nt2::unaligned_;
  using nt2::alignment_;
  using nt2::settings;
  using boost::is_same;
  using nt2::meta::option;

  NT2_TEST( ( is_same < aligned_
              , option< settings(long,int)
                        , nt2::tag::alignment_ 
                        , alignment_<aligned_>
                        >::type 
              >::value
            ) 
          );

  NT2_TEST( ( is_same < unaligned_
              , option< settings(long,int)
                        , nt2::tag::alignment_ 
                        , alignment_<unaligned_>
                        >::type 
            >::value
            ) 
          );
}
