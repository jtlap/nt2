//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/alignment.hpp>
#include "local_semantic.hpp"

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE( alignment_concept )
{
  using nt2::meta::option;
  using nt2::meta::match_option;

  {
    typedef option<nt2::aligned_, nt2::tag::alignment_, some_semantic_> opt;
    typedef opt::type::alignment_type alignment_option;

    NT2_TEST( (match_option< nt2::aligned_, nt2::tag::alignment_ >::value) );
    NT2_TEST_EQUAL( alignment_option::value, true );
  }

  {
    typedef option<nt2::unaligned_, nt2::tag::alignment_, some_semantic_> opt;
    typedef opt::type::alignment_type alignment_option;

    NT2_TEST( (match_option< nt2::unaligned_, nt2::tag::alignment_ >::value) );
    NT2_TEST_EQUAL( alignment_option::value, false );
  }

}

NT2_TEST_CASE( single_alignment_ )
{
  using nt2::aligned_;
  using nt2::unaligned_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( (aligned_())
                      ,(option< _, nt2::tag::alignment_, some_semantic_>)
                      ,(aligned_)
                      );

  NT2_TEST_EXPR_TYPE( (unaligned_())
                      ,(option< _, nt2::tag::alignment_, some_semantic_>)
                      ,(unaligned_)
                      );
}

NT2_TEST_CASE( alignment_default )
{
  using nt2::aligned_;
  using nt2::unaligned_;
  using nt2::settings;
  using nt2::meta::option;

  NT2_TEST_TYPE_IS( (option < settings()
                            , nt2::tag::alignment_
                            , some_semantic_
                            >::type
                    )
                  , aligned_
                  );

  NT2_TEST_TYPE_IS( (option < settings(int,void*)
                            , nt2::tag::alignment_
                            , some_semantic_
                            >::type
                    )
                  , aligned_
                  );
}

NT2_TEST_CASE( single_settings_alignment_ )
{
  using nt2::aligned_;
  using nt2::unaligned_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(aligned_)
                            , nt2::tag::alignment_
                            , some_semantic_
                            >::type
                    )
                  , (aligned_)
                  );

  NT2_TEST_TYPE_IS( (option < settings(unaligned_)
                            , nt2::tag::alignment_
                            , some_semantic_
                            >::type
                    )
                  , (unaligned_)
                  );
}

NT2_TEST_CASE( multi_settings_alignment_ )
{
  using nt2::aligned_;
  using nt2::unaligned_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(aligned_,unaligned_)
                            , nt2::tag::alignment_
                            , some_semantic_
                            >::type
                    )
                  , aligned_
                  );

  NT2_TEST_TYPE_IS( (option < settings(unaligned_,aligned_)
                            , nt2::tag::alignment_
                            , some_semantic_
                            >::type
                    )
                  , unaligned_
                  );
}

NT2_TEST_CASE( nested_settings_alignment_ )
{
  using nt2::aligned_;
  using nt2::unaligned_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(aligned_,unaligned_)
                                      )
                            , nt2::tag::alignment_
                            , some_semantic_
                            >::type
                    )
                  , aligned_
                  );

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(unaligned_,aligned_)
                                      )
                            , nt2::tag::alignment_
                            , some_semantic_
                            >::type
                    )
                  , (unaligned_)
                  );
}
