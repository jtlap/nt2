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
#include <nt2/core/settings/storage_order.hpp>
#include "local_semantic.hpp"

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <nt2/sdk/meta/permute_view.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/array.hpp>

template<class T, class U>
struct column_major_apply_ : nt2::column_major_::apply<T, U> {};

template<class T, class U>
struct row_major_apply_ : nt2::row_major_::apply<T, U> {};

NT2_TEST_CASE( storage_order_concept )
{
  using nt2::meta::option;
  using nt2::meta::match_option;
  using boost::mpl::size_t;
  using boost::mpl::_;

  {
    typedef option<nt2::column_major_, nt2::tag::storage_order_, some_semantic_> opt;
    NT2_TEST( (match_option< nt2::column_major_, nt2::tag::storage_order_ >::value) );
    NT2_TEST_EXPR_TYPE((size_t<0>()),(column_major_apply_<size_t<4>,_>),(size_t<0>));
    NT2_TEST_EXPR_TYPE((size_t<1>()),(column_major_apply_<size_t<4>,_>),(size_t<1>));
    NT2_TEST_EXPR_TYPE((size_t<2>()),(column_major_apply_<size_t<4>,_>),(size_t<2>));
    NT2_TEST_EXPR_TYPE((size_t<3>()),(column_major_apply_<size_t<4>,_>),(size_t<3>));
  }

  {
    typedef option<nt2::row_major_, nt2::tag::storage_order_, some_semantic_> opt;

    NT2_TEST( (match_option< nt2::row_major_, nt2::tag::storage_order_ >::value) );
    NT2_TEST_EXPR_TYPE((size_t<0>()),(row_major_apply_<size_t<4>,_>),(size_t<3>));
    NT2_TEST_EXPR_TYPE((size_t<1>()),(row_major_apply_<size_t<4>,_>),(size_t<2>));
    NT2_TEST_EXPR_TYPE((size_t<2>()),(row_major_apply_<size_t<4>,_>),(size_t<1>));
    NT2_TEST_EXPR_TYPE((size_t<3>()),(row_major_apply_<size_t<4>,_>),(size_t<0>));
  }
}

NT2_TEST_CASE( single_storage_order_ )
{
  using nt2::column_major_;
  using nt2::row_major_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( (column_major_())
                      ,(option< _, nt2::tag::storage_order_, some_semantic_>)
                      ,(column_major_)
                      );

  NT2_TEST_EXPR_TYPE( (row_major_())
                      ,(option< _, nt2::tag::storage_order_, some_semantic_>)
                      ,(row_major_)
                      );
}

NT2_TEST_CASE( storage_order_default )
{
  using nt2::column_major_;
  using nt2::row_major_;
  using nt2::settings;
  using nt2::meta::option;

  NT2_TEST_TYPE_IS( (option < settings()
                            , nt2::tag::storage_order_
                            , some_semantic_
                            >::type
                    )
                  , column_major_
                  );

  NT2_TEST_TYPE_IS( (option < settings(int,void*)
                            , nt2::tag::storage_order_
                            , some_semantic_
                            >::type
                    )
                  , column_major_
                  );
}

NT2_TEST_CASE( single_settings_storage_order_ )
{
  using nt2::column_major_;
  using nt2::row_major_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(column_major_)
                            , nt2::tag::storage_order_
                            , some_semantic_
                            >::type
                    )
                  , (column_major_)
                  );

  NT2_TEST_TYPE_IS( (option < settings(row_major_)
                            , nt2::tag::storage_order_
                            , some_semantic_
                            >::type
                    )
                  , (row_major_)
                  );
}

NT2_TEST_CASE( multi_settings_storage_order_ )
{
  using nt2::column_major_;
  using nt2::row_major_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(column_major_,row_major_)
                            , nt2::tag::storage_order_
                            , some_semantic_
                            >::type
                    )
                  , column_major_
                  );

  NT2_TEST_TYPE_IS( (option < settings(row_major_,column_major_)
                            , nt2::tag::storage_order_
                            , some_semantic_
                            >::type
                    )
                  , row_major_
                  );
}

NT2_TEST_CASE( nested_settings_storage_order_ )
{
  using nt2::column_major_;
  using nt2::row_major_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(column_major_,row_major_)
                                      )
                            , nt2::tag::storage_order_
                            , some_semantic_
                            >::type
                    )
                  , column_major_
                  );

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(row_major_,column_major_)
                                      )
                            , nt2::tag::storage_order_
                            , some_semantic_
                            >::type
                    )
                  , (row_major_)
                  );
}
