//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::settings sharing is an option"

#include <nt2/core/settings/sharing.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/core/container/table/semantic.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// Pass some sharing_ as an option
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( sharing_ )
{
  using nt2::owned_;
  using nt2::shared_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( shared_()
                    , (option< _, nt2::tag::sharing_>)
                    , (shared_)
                    );

  NT2_TEST_EXPR_TYPE( owned_()
                    , (option< _, nt2::tag::sharing_>)
                    , (owned_)
                    );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some sharing_ as default and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( sharing_default )
{
  using nt2::owned_;
  using nt2::shared_;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( owned_()
                    , (option< void, nt2::tag::sharing_,_>)
                    , (owned_)
                    );

  NT2_TEST_EXPR_TYPE( shared_()
                    , (option< void, nt2::tag::sharing_,_>)
                    , (shared_)
                    );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some sharing_ as a setting
////////////////////////////////////////////////////////////////////////////////
nt2::settings own   (nt2::shared_, nt2::owned_);
nt2::settings share (nt2::owned_ , nt2::shared_);

NT2_TEST_CASE( setting_sharing_ )
{
  using nt2::owned_;
  using nt2::shared_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( own
                    , (option<_ , nt2::tag::sharing_>)
                    , (owned_)
                    );

  NT2_TEST_EXPR_TYPE( share
                    , (option<_ , nt2::tag::sharing_>)
                    , (shared_)
                    );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some storage_duration_ as a default setting
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( setting_sharing_default )
{
  using nt2::owned_;
  using nt2::shared_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( shared_()
                    , (option < settings(long, int)
                              , nt2::tag::sharing_
                              ,_
                              >
                      )
                    , (shared_)
                    );

  NT2_TEST_EXPR_TYPE( owned_()
                    , (option < settings(long, int)
                              , nt2::tag::sharing_
                              ,_
                              >
                      )
                    , (owned_)
                    );
}

template<class U, class T, class S>
struct  apply_
{
  typedef typename boost::mpl::apply <U , T, S>::type type;
};

////////////////////////////////////////////////////////////////////////////////
// Verify buffer generation for shared_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( shared_apply )
{
  using boost::mpl::_;
  using nt2::settings;
  using nt2::shared_;
  using nt2::allocator_;
  using nt2::memory::buffer;
  using nt2::tag::table_;
  using nt2::memory::fixed_allocator;
  using nt2::meta::normalize;

  NT2_TEST_EXPR_TYPE( shared_()
                    , (apply_ < _
                              , int
                              , normalize
                                < table_
                                , int
                                , settings( shared_ )
                                >::type
                              >
                      )
                    , (buffer<int, fixed_allocator<int> >)
                    );
}

////////////////////////////////////////////////////////////////////////////////
// Verify buffer generation for owned_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( owned_apply )
{
  using boost::mpl::_;
  using nt2::settings;
  using nt2::of_size_;
  using nt2::owned_;
  using nt2::automatic_;
  using nt2::dynamic_;
  using nt2::allocator_;
  using nt2::memory::buffer;
  using nt2::memory::array_buffer;
  using boost::simd::memory::allocator;
  using boost::simd::memory::allocator_adaptor;
  using nt2::meta::normalize;
  using nt2::tag::table_;

  NT2_TEST_EXPR_TYPE( owned_()
                    , (apply_ < _
                              , int
                              , normalize
                                < table_
                                , int
                                , settings( automatic_
                                          , of_size_<2,2>
                                          )
                                >::type
                              >
                      )
                    , (array_buffer<int, boost::mpl::integral_c<size_t,4> >)
                    );

  NT2_TEST_EXPR_TYPE( owned_()
                    , (apply_ < _
                              , int
                              , normalize
                                < table_
                                , int
                                , settings( dynamic_
                                          , of_size_<2,2>
                                          , allocator_< std::allocator<int> >
                                          )
                                >::type
                              >
                      )
                    , (buffer<int,allocator_adaptor< int, std::allocator<int> > >)
                    );
}
