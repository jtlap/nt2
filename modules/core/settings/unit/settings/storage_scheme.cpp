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
#include <nt2/core/settings/storage_scheme.hpp>
#include "local_semantic.hpp"

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE( storage_scheme_concept )
{
  using nt2::meta::option;
  using nt2::meta::match_option;

  {
    typedef option<nt2::conventional_, nt2::tag::storage_scheme_, some_semantic_> opt;
    NT2_TEST( (match_option< nt2::conventional_, nt2::tag::storage_scheme_ >::value) );
  }

  {
    typedef option<nt2::packed_, nt2::tag::storage_scheme_, some_semantic_> opt;

    NT2_TEST( (match_option< nt2::packed_, nt2::tag::storage_scheme_ >::value) );
  }
}

NT2_TEST_CASE( single_storage_scheme_ )
{
  using nt2::conventional_;
  using nt2::packed_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( (conventional_())
                      ,(option< _, nt2::tag::storage_scheme_, some_semantic_>)
                      ,(conventional_)
                      );

  NT2_TEST_EXPR_TYPE( (packed_())
                      ,(option< _, nt2::tag::storage_scheme_, some_semantic_>)
                      ,(packed_)
                      );
}

NT2_TEST_CASE( storage_scheme_default )
{
  using nt2::conventional_;
  using nt2::packed_;
  using nt2::settings;
  using nt2::meta::option;

  NT2_TEST_TYPE_IS( (option < settings()
                            , nt2::tag::storage_scheme_
                            , some_semantic_
                            >::type
                    )
                  , conventional_
                  );

  NT2_TEST_TYPE_IS( (option < settings(int,void*)
                            , nt2::tag::storage_scheme_
                            , some_semantic_
                            >::type
                    )
                  , conventional_
                  );
}

NT2_TEST_CASE( single_settings_storage_scheme_ )
{
  using nt2::conventional_;
  using nt2::packed_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(conventional_)
                            , nt2::tag::storage_scheme_
                            , some_semantic_
                            >::type
                    )
                  , (conventional_)
                  );

  NT2_TEST_TYPE_IS( (option < settings(packed_)
                            , nt2::tag::storage_scheme_
                            , some_semantic_
                            >::type
                    )
                  , (packed_)
                  );
}

NT2_TEST_CASE( multi_settings_storage_scheme_ )
{
  using nt2::conventional_;
  using nt2::packed_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(conventional_,packed_)
                            , nt2::tag::storage_scheme_
                            , some_semantic_
                            >::type
                    )
                  , conventional_
                  );

  NT2_TEST_TYPE_IS( (option < settings(packed_,conventional_)
                            , nt2::tag::storage_scheme_
                            , some_semantic_
                            >::type
                    )
                  , packed_
                  );
}

NT2_TEST_CASE( nested_settings_storage_scheme_ )
{
  using nt2::conventional_;
  using nt2::packed_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(conventional_,packed_)
                                      )
                            , nt2::tag::storage_scheme_
                            , some_semantic_
                            >::type
                    )
                  , conventional_
                  );

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(packed_,conventional_)
                                      )
                            , nt2::tag::storage_scheme_
                            , some_semantic_
                            >::type
                    )
                  , (packed_)
                  );
}
