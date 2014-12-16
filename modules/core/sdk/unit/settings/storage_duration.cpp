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
#include <boost/simd/memory/allocator.hpp>

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
    NT2_TEST( (match_option< nt2::dynamic_, nt2::tag::storage_duration_ >::value) );
  }

  {
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
                      ,(option< _, nt2::tag::storage_duration_, some_kind_>)
                      ,(dynamic_)
                      );

  NT2_TEST_EXPR_TYPE( (automatic_())
                      ,(option< _, nt2::tag::storage_duration_, some_kind_>)
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
                            , some_kind_
                            >::type
                    )
                  , dynamic_
                  );

  NT2_TEST_TYPE_IS( (option < settings(int,void*)
                            , nt2::tag::storage_duration_
                            , some_kind_
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
                            , some_kind_
                            >::type
                    )
                  , (dynamic_)
                  );

  NT2_TEST_TYPE_IS( (option < settings(automatic_)
                            , nt2::tag::storage_duration_
                            , some_kind_
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
                            , some_kind_
                            >::type
                    )
                  , dynamic_
                  );

  NT2_TEST_TYPE_IS( (option < settings(automatic_,dynamic_)
                            , nt2::tag::storage_duration_
                            , some_kind_
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

  typedef settings shadow(double,int);
  typedef settings option1(dynamic_,automatic_);
  typedef settings option2(automatic_,dynamic_);

  NT2_TEST_TYPE_IS( (option < settings(shadow,option1)
                            , nt2::tag::storage_duration_
                            , some_kind_
                            >::type
                    )
                  , dynamic_
                  );

  NT2_TEST_TYPE_IS( (option < settings(shadow,option2)
                            , nt2::tag::storage_duration_
                            , some_kind_
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
  using boost::simd::aligned_array;

  NT2_TEST_EXPR_TYPE( automatic_()
                    , (apply_ < _
                              , container
                                < some_kind_
                                , int
                                , settings(automatic_, of_size_<2,2>)
                                >
                              >
                      )
                    , (aligned_array<int, 4>)
                    );

  NT2_TEST_EXPR_TYPE( automatic_()
                    , (apply_ < _
                              , container
                                < some_kind_
                                , int
                                , settings(automatic_, of_size_<12,3>)
                                >
                              >
                      )
                    , (aligned_array<int, 36 >)
                    );
}

NT2_TEST_CASE( dynamic_duration_apply )
{
  using boost::mpl::_;
  using nt2::settings;
  using nt2::memory::container;
  using boost::simd::allocator;
  using nt2::dynamic_;
  using nt2::index_;
  using nt2::memory::buffer;

  NT2_TEST_EXPR_TYPE( dynamic_()
                    , (apply_ < _
                              , container
                                < some_kind_
                                , int
                                , settings(dynamic_, allocator<int>)
                                >
                              >
                      )
                    , (buffer<int, allocator<int> >)
                    );

  NT2_TEST_EXPR_TYPE( dynamic_()
                    , (apply_ < _
                              , container
                                < some_kind_
                                , int
                                , settings(dynamic_)
                                >
                              >
                      )
                    , (buffer<int, std::allocator<int> >)
                    );
}
