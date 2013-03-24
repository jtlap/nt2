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
#include <nt2/core/settings/storage_duration.hpp>
#include <nt2/sdk/memory/container.hpp>
#include "local_semantic.hpp"

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE( storage_duration_concept )
{
  using nt2::meta::option;
  using nt2::meta::match_option;
  using boost::mpl::size_t;
  using boost::mpl::_;

  {
    typedef option<nt2::dynamic_, nt2::tag::storage_duration_, some_semantic_> opt;
    NT2_TEST( (match_option< nt2::dynamic_, nt2::tag::storage_duration_ >::value) );
  }

  {
    typedef option<nt2::automatic_, nt2::tag::storage_duration_, some_semantic_> opt;
    NT2_TEST( (match_option< nt2::automatic_, nt2::tag::storage_duration_ >::value) );
  }
}

NT2_TEST_CASE( single_storage_duration_ )
{
  using nt2::dynamic_;
  using nt2::automatic_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( (dynamic_())
                      ,(option< _, nt2::tag::storage_duration_, some_semantic_>)
                      ,(dynamic_)
                      );

  NT2_TEST_EXPR_TYPE( (automatic_())
                      ,(option< _, nt2::tag::storage_duration_, some_semantic_>)
                      ,(automatic_)
                      );
}

NT2_TEST_CASE( storage_duration_default )
{
  using nt2::dynamic_;
  using nt2::automatic_;
  using nt2::settings;
  using nt2::meta::option;

  NT2_TEST_TYPE_IS( (option < settings()
                            , nt2::tag::storage_duration_
                            , some_semantic_
                            >::type
                    )
                  , dynamic_
                  );

  NT2_TEST_TYPE_IS( (option < settings(int,void*)
                            , nt2::tag::storage_duration_
                            , some_semantic_
                            >::type
                    )
                  , dynamic_
                  );
}

NT2_TEST_CASE( single_settings_storage_duration_ )
{
  using nt2::dynamic_;
  using nt2::automatic_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(dynamic_)
                            , nt2::tag::storage_duration_
                            , some_semantic_
                            >::type
                    )
                  , (dynamic_)
                  );

  NT2_TEST_TYPE_IS( (option < settings(automatic_)
                            , nt2::tag::storage_duration_
                            , some_semantic_
                            >::type
                    )
                  , (automatic_)
                  );
}

NT2_TEST_CASE( multi_settings_storage_duration_ )
{
  using nt2::dynamic_;
  using nt2::automatic_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings(dynamic_,automatic_)
                            , nt2::tag::storage_duration_
                            , some_semantic_
                            >::type
                    )
                  , dynamic_
                  );

  NT2_TEST_TYPE_IS( (option < settings(automatic_,dynamic_)
                            , nt2::tag::storage_duration_
                            , some_semantic_
                            >::type
                    )
                  , automatic_
                  );
}

NT2_TEST_CASE( nested_settings_storage_duration_ )
{
  using nt2::dynamic_;
  using nt2::automatic_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(dynamic_,automatic_)
                                      )
                            , nt2::tag::storage_duration_
                            , some_semantic_
                            >::type
                    )
                  , dynamic_
                  );

  NT2_TEST_TYPE_IS( (option < settings( settings(void*,int)
                                      , settings(automatic_,dynamic_)
                                      )
                            , nt2::tag::storage_duration_
                            , some_semantic_
                            >::type
                    )
                  , (automatic_)
                  );
}

template<class U, class C>
struct  apply_
{
  typedef typename boost::mpl::apply <U , C>::type type;
};

NT2_TEST_CASE( automatic_duration_apply )
{
  using boost::mpl::_;
  using nt2::settings;
  using nt2::of_size_;
  using nt2::automatic_;
  using nt2::index_;
  using nt2::memory::container;
  using nt2::memory::array_buffer;

  NT2_TEST_EXPR_TYPE( automatic_()
                    , (apply_ < _
                              , container
                                < int
                                , settings(automatic_, of_size_<2,2>)
                                , some_semantic_
                                >
                              >
                      )
                    , (array_buffer<int, boost::mpl::integral_c<size_t,4> >)
                    );

  NT2_TEST_EXPR_TYPE( automatic_()
                    , (apply_ < _
                              , container
                                < int
                                , settings(automatic_, of_size_<12,3>)
                                , some_semantic_
                                >
                              >
                      )
                    , (array_buffer<int, boost::mpl::integral_c<size_t,36> >)
                    );
}

NT2_TEST_CASE( dynamic_duration_apply )
{
  using boost::mpl::_;
  using nt2::settings;
  using nt2::memory::container;
  using boost::simd::allocator;
  using boost::simd::allocator_adaptor;
  using nt2::dynamic_;
  using nt2::index_;
  using nt2::memory::buffer;

  NT2_TEST_EXPR_TYPE( dynamic_()
                    , (apply_ < _
                              , container
                                < int
                                , settings(dynamic_, allocator<int>)
                                , some_semantic_
                                >
                              >
                      )
                    , (buffer<int, allocator<int> >)
                    );

  NT2_TEST_EXPR_TYPE( dynamic_()
                    , (apply_ < _
                              , container
                                < int
                                , settings(dynamic_)
                                , some_semantic_
                                >
                              >
                      )
                    , (buffer<int, allocator_adaptor<std::allocator<int> > >)
                    );
}
