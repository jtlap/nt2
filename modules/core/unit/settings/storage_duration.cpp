//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::settings storage_duration is an option"

#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/allocator.hpp>
#include <nt2/sdk/memory/fixed_allocator.hpp>
#include <nt2/core/settings/storage_duration.hpp>
#include <nt2/core/container/table/normalize_settings.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_duration_ as an option
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( storage_duration_ )
{
  using nt2::dynamic_;
  using nt2::automatic_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( dynamic_()
                    , (option< _, nt2::tag::storage_duration_>)
                    , (dynamic_)
                    );

  NT2_TEST_EXPR_TYPE( automatic_()
                    , (option< _, nt2::tag::storage_duration_>)
                    , (automatic_)
                    );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_duration_ as default and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( storage_duration_default )
{
  using nt2::dynamic_;
  using nt2::automatic_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( dynamic_()
                    , (option< void, nt2::tag::storage_duration_,_>)
                    , (dynamic_)
                    );

  NT2_TEST_EXPR_TYPE( automatic_()
                    , (option< void, nt2::tag::storage_duration_,_>)
                    , (automatic_)
                    );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_duration_ as a setting
////////////////////////////////////////////////////////////////////////////////
nt2::settings dyn   (nt2::automatic_, nt2::dynamic_);
nt2::settings autom (nt2::dynamic_  , nt2::automatic_);
NT2_TEST_CASE( setting_storage_duration_ )
{
  using nt2::dynamic_;
  using nt2::automatic_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( dyn
                    , (option<_ , nt2::tag::storage_duration_>)
                    , (dynamic_)
                    );

  NT2_TEST_EXPR_TYPE( autom
                    , (option<_ , nt2::tag::storage_duration_>)
                    , (automatic_)
                    );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_duration_ as a default setting
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( setting_storage_duration_default )
{
  using nt2::dynamic_;
  using nt2::automatic_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( dynamic_()
                    , (option < settings(long, int)
                              , nt2::tag::storage_duration_
                              ,_
                              >
                      )
                    , (dynamic_)
                    );

  NT2_TEST_EXPR_TYPE( automatic_()
                    , (option < settings(long, int)
                              , nt2::tag::storage_duration_
                              ,_
                              >
                      )
                    , (automatic_)
                    );
}

template<class U, class T, class S, class D = void>
struct  apply_
{
  typedef typename boost::mpl::apply <U , T, S, D>::type type;
};

////////////////////////////////////////////////////////////////////////////////
// Verify buffer generation for automatic_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( automatic_duration_apply )
{
  using boost::mpl::_;
  using nt2::settings;
  using nt2::of_size_;
  using nt2::automatic_;
  using nt2::tag::table_;
  using nt2::no_padding_;
  using nt2::padding_;
  using nt2::index_;
  using nt2::memory::cache_padding;
  using nt2::memory::array_buffer;
  using nt2::meta::normalize_settings;

  NT2_TEST_EXPR_TYPE( automatic_()
                    , (apply_ < _
                              , int
                              , normalize_settings
                                < table_
                                , int
                                , settings( automatic_
                                          , of_size_<2,2>
                                          , no_padding_
                                          )
                                >::type
                              >
                      )
                    , (array_buffer<int, 4, 1>)
                    );

  NT2_TEST_EXPR_TYPE( automatic_()
                    , (apply_ < _
                              , int
                              , normalize_settings
                                < table_
                                , int
                                , settings( automatic_
                                          , of_size_<3,12>
                                          , padding_<cache_padding>
                                          )
                                >::type
                              >
                      )
                    , (array_buffer<int, 36, 1>)
                    );

  NT2_TEST_EXPR_TYPE( automatic_()
                    , (apply_ < _
                              , int*
                              , normalize_settings
                                < table_
                                , int*
                                , settings( automatic_
                                          , of_size_<2,2>
                                          , no_padding_
                                          )
                                >::type
                              >
                      )
                    , (array_buffer<int*, 2, 1>)
                    );

  NT2_TEST_EXPR_TYPE( automatic_()
                    , (apply_ < _
                              , int*
                              , normalize_settings
                                < table_
                                , int*
                                , settings( automatic_
                                          , of_size_<3,12>
                                          , padding_<cache_padding>
                                          )
                                >::type
                              >
                      )
                    , (array_buffer<int*, 12, 1>)
                    );
}

////////////////////////////////////////////////////////////////////////////////
// Verify buffer generation for automatic_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( dynamic_duration_apply )
{
  using boost::mpl::_;
  using nt2::settings;
  using boost::simd::memory::allocator;
  using boost::simd::memory::allocator_adaptor;
  using nt2::allocator_;
  using nt2::dynamic_;
  using nt2::tag::table_;
  using nt2::no_padding_;
  using nt2::padding_;
  using nt2::index_;
  using nt2::memory::cache_padding;
  using nt2::memory::buffer;
  using nt2::meta::normalize_settings;

  NT2_TEST_EXPR_TYPE( dynamic_()
                    , (apply_ < _
                              , int
                              , normalize_settings
                                < table_
                                , int
                                , settings( dynamic_
                                          , allocator_< allocator<int> >
                                          , no_padding_
                                          )
                                >::type
                              >
                      )
                    , (buffer<int, 1, allocator<int> >)
                    );

  NT2_TEST_EXPR_TYPE( dynamic_()
                    , (apply_ < _
                              , int
                              , normalize_settings
                                < table_
                                , int
                                , settings( dynamic_
                                          , allocator_< allocator<int> >
                                          , padding_<cache_padding>
                                          )
                                >::type
                              >
                      )
                    , (buffer<int, 1, allocator<int> >)
                    );

  NT2_TEST_EXPR_TYPE( dynamic_()
                    , (apply_ < _
                              , int
                              , normalize_settings
                                < table_
                                , int
                                , settings( dynamic_
                                          , allocator_< std::allocator<int> >
                                          , no_padding_
                                          )
                                >::type
                              >
                      )
                    , (buffer<int, 1, allocator_adaptor<int,std::allocator<int> > >)
                    );

  NT2_TEST_EXPR_TYPE( dynamic_()
                    , (apply_ < _
                              , int
                              , normalize_settings
                                < table_
                                , int
                                , settings( dynamic_
                                          , allocator_< std::allocator<int> >
                                          , padding_<cache_padding>
                                          )
                                >::type
                              >
                      )
                    , (buffer<int, 1, allocator_adaptor<int,std::allocator<int> > >)
                    );
}
