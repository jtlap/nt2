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
#include <nt2/core/settings/index.hpp>
#include "local_semantic.hpp"

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE( index_concept )
{
  using nt2::index_;
  using nt2::meta::option;
  using nt2::meta::match_option;

  typedef option<nt2::index_<3,2,4,5>, nt2::tag::index_, some_semantic_> opt;
  typedef opt::type::index_type index_option;

  NT2_TEST( (match_option< nt2::index_<3,2,4,5>, nt2::tag::index_ >::value) );

  NT2_TEST_EQUAL( boost::mpl::size<index_option>::value, NT2_MAX_DIMENSIONS );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,0>::type::value), 3 );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,1>::type::value), 2 );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,2>::type::value), 4 );
  NT2_TEST_EQUAL( (boost::mpl::at_c<index_option,3>::type::value), 5 );
}

NT2_TEST_CASE( single_index_ )
{
  using nt2::index_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( (nt2::index_<3,2,4>())
                      ,(option< _, nt2::tag::index_, some_semantic_>)
                      ,(nt2::index_<3,2,4>)
                      );
}

NT2_TEST_CASE( index_default )
{
  using nt2::matlab_index_;
  using nt2::index_;
  using nt2::settings;
  using nt2::meta::option;

  NT2_TEST_TYPE_IS( (option < settings()
                            , nt2::tag::index_
                            , some_semantic_
                            >::type
                    )
                  , matlab_index_
                  );

  NT2_TEST_TYPE_IS( (option < settings(int,void*)
                            , nt2::tag::index_
                            , some_semantic_
                            >::type
                    )
                  , matlab_index_
                  );
}

NT2_TEST_CASE( single_settings_index_ )
{
  using nt2::index_;
  using nt2::C_index_;
  using nt2::matlab_index_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(index_<5,6>)
                            , nt2::tag::index_
                            , some_semantic_
                            >::type
                    )
                  , (index_<5,6>)
                  );

  NT2_TEST_TYPE_IS( (option < settings(C_index_)
                            , nt2::tag::index_
                            , some_semantic_
                            >::type
                    )
                  , (C_index_)
                  );

  NT2_TEST_TYPE_IS( (option < settings(matlab_index_)
                            , nt2::tag::index_
                            , some_semantic_
                            >::type
                    )
                  , (matlab_index_)
                  );
}

NT2_TEST_CASE( multi_settings_index_ )
{
  using nt2::C_index_;
  using nt2::matlab_index_;
  using nt2::index_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(C_index_,matlab_index_)
                            , nt2::tag::index_
                            , some_semantic_
                            >::type
                    )
                  , C_index_
                  );

  NT2_TEST_TYPE_IS( (option < settings(matlab_index_,C_index_)
                            , nt2::tag::index_
                            , some_semantic_
                            >::type
                    )
                  , matlab_index_
                  );
}

NT2_TEST_CASE( nested_settings_index_ )
{
  using nt2::C_index_;
  using nt2::matlab_index_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(C_index_,matlab_index_)
                                      )
                            , nt2::tag::index_
                            , some_semantic_
                            >::type
                    )
                  , C_index_
                  );

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(matlab_index_,C_index_)
                                      )
                            , nt2::tag::index_
                            , some_semantic_
                            >::type
                    )
                  , (matlab_index_)
                  );
}
