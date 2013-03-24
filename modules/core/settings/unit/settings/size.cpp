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
#include <nt2/core/settings/size.hpp>
#include "local_semantic.hpp"

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE( of_size_concept )
{
  using nt2::of_size_;
  using nt2::meta::option;
  using nt2::meta::match_option;
  using boost::mpl::_;

  typedef option<nt2::of_size_<3,2,-1,5>, nt2::tag::of_size_, some_semantic_> opt;
  opt::type::of_size_type of_size_option;

  NT2_TEST( (match_option<nt2::of_size_<3,2,-1,5>, nt2::tag::of_size_>::value) );

  NT2_TEST_EQUAL( of_size_option.size(), 4u );
  NT2_TEST_EQUAL( of_size_option[0], 3u );
  NT2_TEST_EQUAL( of_size_option[1], 2u );
  NT2_TEST_EQUAL( of_size_option[2], 0u );
  NT2_TEST_EQUAL( of_size_option[3], 5u );
}

NT2_TEST_CASE( single_of_size_ )
{
  using nt2::_2D;
  using nt2::of_size_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( (_2D())
                      ,(option< _, nt2::tag::of_size_, some_semantic_>)
                      ,(_2D)
                      );

  NT2_TEST_EXPR_TYPE( (of_size_<3,4>())
                      ,(option< _, nt2::tag::of_size_, some_semantic_>)
                      ,(of_size_<3,4>)
                      );
}

NT2_TEST_CASE( of_size_default )
{
  using nt2::_4D;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::meta::option;

  NT2_TEST_TYPE_IS( (option < settings()
                            , nt2::tag::of_size_
                            , some_semantic_
                            >::type
                    )
                  , _4D
                  );

  NT2_TEST_TYPE_IS( (option < settings(int,void*)
                            , nt2::tag::of_size_
                            , some_semantic_
                            >::type
                    )
                  , _4D
                  );
}

NT2_TEST_CASE( single_settings_of_size_ )
{
  using nt2::_2D;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(_2D)
                            , nt2::tag::of_size_
                            , some_semantic_
                            >::type
                    )
                  , _2D
                  );

  NT2_TEST_TYPE_IS( (option < settings(of_size_<3,4>)
                            , nt2::tag::of_size_
                            , some_semantic_
                            >::type
                    )
                  , (of_size_<3,4>)
                  );
}

NT2_TEST_CASE( multi_settings_of_size_ )
{
  using nt2::_2D;
  using nt2::_4D;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(_2D,_4D)
                            , nt2::tag::of_size_
                            , some_semantic_
                            >::type
                    )
                  , _2D
                  );

  NT2_TEST_TYPE_IS( (option < settings(of_size_<3,4>,_4D)
                            , nt2::tag::of_size_
                            , some_semantic_
                            >::type
                    )
                  , (of_size_<3,4>)
                  );
}

NT2_TEST_CASE( nested_settings_of_size_ )
{
  using nt2::_2D;
  using nt2::_3D;
  using nt2::_4D;
  using nt2::of_size_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(settings(void*,int), settings(_2D,_4D))
                            , nt2::tag::of_size_
                            , some_semantic_
                            >::type
                    )
                  , _2D
                  );

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(of_size_<3,4>,_4D)
                                      )
                            , nt2::tag::of_size_
                            , some_semantic_
                            >::type
                    )
                  , (of_size_<3,4>)
                  );
}
