//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/core/settings/buffer.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include "local_kind.hpp"
#include <vector>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE( buffer_concept )
{
  using std::vector;
  using nt2::built_in_;
  using boost::mpl::_;
  using nt2::meta::option;
  using nt2::meta::match_option;
  using nt2::memory::buffer;

  NT2_TEST( (match_option< built_in_  , nt2::tag::buffer_>::value) );
  NT2_TEST( (match_option< vector<int>, nt2::tag::buffer_>::value) );
}

NT2_TEST_CASE( single_buffer_ )
{
  using nt2::built_in_;
  using nt2::meta::option;
  using std::vector;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( built_in_()
                    , (option< _, nt2::tag::buffer_, some_kind_>)
                    , (built_in_)
                    );

  NT2_TEST_EXPR_TYPE( vector<int>()
                    , (option< _, nt2::tag::buffer_, some_kind_>)
                    , (std::vector<int>)
                    );
}

NT2_TEST_CASE( buffer_default )
{
  using nt2::built_in_;
  using nt2::meta::option;
  using std::vector;
  using boost::mpl::_;
  using nt2::settings;

  NT2_TEST_TYPE_IS( (option < settings()
                            , nt2::tag::buffer_
                            , some_kind_
                            >::type
                    )
                  , built_in_
                  );

  NT2_TEST_TYPE_IS( (option < settings(int,void*)
                            , nt2::tag::buffer_
                            , some_kind_
                            >::type
                    )
                  , built_in_
                  );
}

NT2_TEST_CASE( single_settings_buffer_ )
{
  using std::vector;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(vector<float>)
                            , nt2::tag::buffer_
                            , some_kind_
                            >::type
                    )
                  , (vector<float>)
                  );
}

NT2_TEST_CASE( multi_settings_buffer_ )
{
  using std::vector;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(vector<float>,vector<int>)
                            , nt2::tag::buffer_
                            , some_kind_
                            >::type
                    )
                  , vector<float>
                  );

  NT2_TEST_TYPE_IS( (option < settings(vector<int>,vector<float>)
                            , nt2::tag::buffer_
                            , some_kind_
                            >::type
                    )
                  , vector<int>
                  );
}

NT2_TEST_CASE( nested_settings_buffer_ )
{
  using std::vector;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(vector<int>,vector<float>)
                                      )
                            , nt2::tag::buffer_
                            , some_kind_
                            >::type
                    )
                  , vector<int>
                  );

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(vector<float>,vector<int>)
                                      )
                            , nt2::tag::buffer_
                            , some_kind_
                            >::type
                    )
                  , vector<float>
                  );
}
