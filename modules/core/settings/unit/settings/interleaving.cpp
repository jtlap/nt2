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
#include <nt2/core/settings/interleaving.hpp>
#include "local_semantic.hpp"

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE( interleaving_concept )
{
  using nt2::meta::option;
  using nt2::meta::match_option;

  {
    typedef option<nt2::interleaved_, nt2::tag::interleaving_, some_semantic_> opt;
    typedef opt::type::interleaving_type interleaving_option;

    NT2_TEST( (match_option< nt2::interleaved_, nt2::tag::interleaving_ >::value) );
    NT2_TEST_EQUAL( interleaving_option::value, false );
  }

  {
    typedef option<nt2::deinterleaved_, nt2::tag::interleaving_, some_semantic_> opt;
    typedef opt::type::interleaving_type interleaving_option;

    NT2_TEST( (match_option< nt2::deinterleaved_, nt2::tag::interleaving_ >::value) );
    NT2_TEST_EQUAL( interleaving_option::value, true );
  }

}

NT2_TEST_CASE( single_interleaving_ )
{
  using nt2::interleaved_;
  using nt2::deinterleaved_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( (interleaved_())
                      ,(option< _, nt2::tag::interleaving_, some_semantic_>)
                      ,(interleaved_)
                      );

  NT2_TEST_EXPR_TYPE( (deinterleaved_())
                      ,(option< _, nt2::tag::interleaving_, some_semantic_>)
                      ,(deinterleaved_)
                      );
}

NT2_TEST_CASE( interleaving_default )
{
  using nt2::interleaved_;
  using nt2::deinterleaved_;
  using nt2::settings;
  using nt2::meta::option;

  NT2_TEST_TYPE_IS( (option < settings()
                            , nt2::tag::interleaving_
                            , some_semantic_
                            >::type
                    )
                  , interleaved_
                  );

  NT2_TEST_TYPE_IS( (option < settings(int,void*)
                            , nt2::tag::interleaving_
                            , some_semantic_
                            >::type
                    )
                  , interleaved_
                  );
}

NT2_TEST_CASE( single_settings_interleaving_ )
{
  using nt2::interleaved_;
  using nt2::deinterleaved_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(interleaved_)
                            , nt2::tag::interleaving_
                            , some_semantic_
                            >::type
                    )
                  , (interleaved_)
                  );

  NT2_TEST_TYPE_IS( (option < settings(deinterleaved_)
                            , nt2::tag::interleaving_
                            , some_semantic_
                            >::type
                    )
                  , (deinterleaved_)
                  );
}

NT2_TEST_CASE( multi_settings_interleaving_ )
{
  using nt2::interleaved_;
  using nt2::deinterleaved_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(interleaved_,deinterleaved_)
                            , nt2::tag::interleaving_
                            , some_semantic_
                            >::type
                    )
                  , interleaved_
                  );

  NT2_TEST_TYPE_IS( (option < settings(deinterleaved_,interleaved_)
                            , nt2::tag::interleaving_
                            , some_semantic_
                            >::type
                    )
                  , deinterleaved_
                  );
}

NT2_TEST_CASE( nested_settings_interleaving_ )
{
  using nt2::interleaved_;
  using nt2::deinterleaved_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(interleaved_,deinterleaved_)
                                      )
                            , nt2::tag::interleaving_
                            , some_semantic_
                            >::type
                    )
                  , interleaved_
                  );

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(deinterleaved_,interleaved_)
                                      )
                            , nt2::tag::interleaving_
                            , some_semantic_
                            >::type
                    )
                  , (deinterleaved_)
                  );
}
