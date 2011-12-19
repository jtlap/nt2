/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::settings storage_duration is an option"

#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/allocator.hpp>
#include <nt2/core/container/memory/buffer.hpp>
#include <nt2/core/container/memory/fixed_allocator.hpp>
#include <nt2/core/settings/storage_duration.hpp>

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
  using nt2::no_padding_;
  using nt2::lead_padding_strategy_;
  using nt2::global_padding_strategy_;
  using nt2::memory::array_buffer;

  NT2_TEST_EXPR_TYPE( automatic_()
                    , (apply_ < _
                              , int
                              , settings
                                ( of_size_<2,2>
                                , no_padding_
                                )
                              >
                      )
                    , (array_buffer<int, 4>)
                    );

  NT2_TEST_EXPR_TYPE( automatic_()
                    , (apply_ < _
                              , int
                              , settings
                                ( of_size_<3,2>
                                , lead_padding_strategy_<8>
                                , global_padding_strategy_<>
                                )
                              >
                      )
                    , (array_buffer<int, 16>)
                    );

  NT2_TEST_EXPR_TYPE( automatic_()
                    , (apply_ < _
                              , int
                              , settings
                                ( of_size_<3,2>
                                , lead_padding_strategy_<1>
                                , global_padding_strategy_<8>
                                )
                              >
                      )
                    , (array_buffer<int, 8>)
                    );                   

  NT2_TEST_EXPR_TYPE( automatic_()
                    , (apply_ < _
                              , int
                              , settings
                                ( of_size_<3,2>
                                , lead_padding_strategy_<4>
                                , global_padding_strategy_<32>
                                )
                              >
                      )
                    , (array_buffer<int, 32>)
                    );                                        
}

////////////////////////////////////////////////////////////////////////////////
// Verify buffer generation for dynamic_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( dynamic_duration_apply )
{
  using boost::mpl::_;
  using nt2::settings;
  using nt2::allocator_;
  using nt2::aligned_;
  using nt2::unaligned_;
  using nt2::dynamic_;
  using nt2::no_padding_;
  using nt2::lead_padding_strategy_;
  using nt2::global_padding_strategy_;
  using nt2::memory::buffer;
  using boost::simd::memory::allocator_adaptor;
  using boost::simd::memory::allocator;

  NT2_TEST_EXPR_TYPE( dynamic_()
                    , (apply_ < _
                              , int
                              , settings
                                ( no_padding_
                                , allocator_< std::allocator<int> >
                                , aligned_
                                )
                              >
                      )
                    , (buffer<int, std::allocator<int> >)
                    );

  NT2_TEST_EXPR_TYPE( dynamic_()
                    , (apply_ < _
                              , int
                              , settings
                                ( no_padding_
                                , allocator_< std::allocator<int> >
                                , unaligned_
                                )
                              >
                      )
                    , (buffer<int, allocator_adaptor<int,std::allocator<int> > >)
                    );

  NT2_TEST_EXPR_TYPE( dynamic_()
                    , (apply_ < _
                              , int
                              , settings
                                ( no_padding_
                                , allocator_< allocator<int> >
                                , aligned_
                                )
                              >
                      )
                    , (buffer<int, allocator<int> >)
                    );

  NT2_TEST_EXPR_TYPE( dynamic_()
                    , (apply_ < _
                              , int
                              , settings
                                ( no_padding_
                                , allocator_< allocator<int> >
                                , unaligned_
                                )
                              >
                      )
                    , (buffer<int, allocator<int> >)
                    );

}

////////////////////////////////////////////////////////////////////////////////
// Verify buffer generation for dynamic_ with special allocator
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( dynamic_duration_apply_with_allocator )
{
  using boost::mpl::_;
  using nt2::settings;
  using nt2::allocator_;
  using nt2::aligned_;
  using nt2::unaligned_;
  using nt2::dynamic_;
  using nt2::no_padding_;
  using nt2::lead_padding_strategy_;
  using nt2::global_padding_strategy_;
  using nt2::memory::buffer;
  using nt2::memory::fixed_allocator;
  using boost::simd::memory::allocator_adaptor;
  using boost::simd::memory::allocator;

  NT2_TEST_EXPR_TYPE( dynamic_()
                    , (apply_ < _
                              , int
                              , settings
                                ( no_padding_
                                , allocator_< std::allocator<int> >
                                , aligned_
                                )
                              , allocator_< fixed_allocator<int> >
                              >
                      )
                    , (buffer<int, fixed_allocator<int> >)
                    );

  NT2_TEST_EXPR_TYPE( dynamic_()
                    , (apply_ < _
                              , int
                              , settings
                                ( no_padding_
                                , allocator_< std::allocator<int> >
                                , unaligned_
                                )
                              , allocator_< fixed_allocator<int> >
                              >
                      )
                    , (buffer<int, allocator_adaptor<int,fixed_allocator<int> > >)
                    );
}
