//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::settings allocator_ is an option"

#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/allocator.hpp>
#include "local_semantic.hpp"

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE( allocator_concept )
{
  using nt2::tag::allocator_;
  using nt2::meta::match_option;
  using nt2::meta::option;
  using std::allocator;

  NT2_TEST( (match_option< allocator<int>, allocator_>::value) );

  NT2_TEST_TYPE_IS( (option < allocator<int>
                            , nt2::tag::allocator_
                            , some_semantic_
                            >::type::rebind<float>::other
                    )
                  , allocator<float>
                  );
}

NT2_TEST_CASE( single_allocator_ )
{
  using nt2::tag::allocator_;
  using nt2::meta::option;
  using std::allocator;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( allocator<int>()
                    , (option< _, nt2::tag::allocator_, some_semantic_>)
                    , allocator<int>
                    );
}

NT2_TEST_CASE( allocator_default )
{
  using nt2::tag::allocator_;
  using nt2::meta::option;
  using std::allocator;
  using boost::mpl::_;
  using nt2::settings;

  NT2_TEST_TYPE_IS( (option < settings()
                            , nt2::tag::allocator_
                            , some_semantic_
                            >::type
                    )
                  , allocator<void*>
                  );

  NT2_TEST_TYPE_IS( (option < settings(int,void*)
                            , nt2::tag::allocator_
                            , some_semantic_
                            >::type
                    )
                  , allocator<void*>
                  );
}

NT2_TEST_CASE( single_settings_allocator_ )
{
  using nt2::tag::allocator_;
  using std::allocator;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(allocator<float>)
                            , nt2::tag::allocator_
                            , some_semantic_
                            >::type
                    )
                  , (allocator<float>)
                  );
}

NT2_TEST_CASE( multi_settings_allocator_ )
{
  using std::allocator;
  using nt2::tag::allocator_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(allocator<float>,allocator<int>)
                            , nt2::tag::allocator_
                            , some_semantic_
                            >::type
                    )
                  , allocator<float>
                  );

  NT2_TEST_TYPE_IS( (option < settings(allocator<int>,allocator<float>)
                            , nt2::tag::allocator_
                            , some_semantic_
                            >::type
                    )
                  , allocator<int>
                  );
}

NT2_TEST_CASE( nested_settings_allocator_ )
{
  using nt2::tag::allocator_;
  using std::allocator;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(allocator<int>,allocator<float>)
                                      )
                            , nt2::tag::allocator_
                            , some_semantic_
                            >::type
                    )
                  , allocator<int>
                  );

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(allocator<float>,allocator<int>)
                                      )
                            , nt2::tag::allocator_
                            , some_semantic_
                            >::type
                    )
                  , allocator<float>
                  );
}
