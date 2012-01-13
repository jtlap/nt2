//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::settings buffer is an option"

#include <nt2/core/settings/buffer.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/memory/iliffe_buffer.hpp>
#include <nt2/core/container/table/normalize_settings.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

//==============================================================================
// Pass some buffer_ as an option
//==============================================================================
NT2_TEST_CASE( buffer_ )
{
  using nt2::buffer_;
  using boost::mpl::_;
  using nt2::meta::option;
  using nt2::memory::buffer;

  NT2_TEST_EXPR_TYPE( buffer_<>()
                    , (option< _, nt2::tag::buffer_>)
                    , (buffer_<>)
                    );

  NT2_TEST_EXPR_TYPE( (buffer_< buffer<int,-2> >() )
                    , (option< _, nt2::tag::buffer_>)
                    , (buffer_< buffer<int,-2> >)
                    );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some buffer_ as default and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( buffer_default )
{
  using nt2::buffer_;
  using nt2::memory::buffer;
  using nt2::meta::option;
  using boost::mpl::_;

  NT2_TEST_EXPR_TYPE( buffer_<>()
                    , (option< void, nt2::tag::buffer_,_>)
                    , (buffer_<>)
                    );

  NT2_TEST_EXPR_TYPE( (buffer_< buffer<int,-2> >())
                    , (option< void, nt2::tag::buffer_,_>)
                    , (buffer_< buffer<int,-2> >)
                    );
}

////////////////////////////////////////////////////////////////////////////////
// Pass some buffer_ as a setting
////////////////////////////////////////////////////////////////////////////////
nt2::settings s_no_buffer(nt2::buffer_<>);
nt2::settings s_int_buffer(nt2::buffer_< nt2::memory::buffer<int,1> >);

NT2_TEST_CASE( setting_buffer_ )
{
  using nt2::buffer_;
  using nt2::settings;
  using nt2::meta::option;
  using boost::mpl::_;
  using nt2::memory::buffer;

  NT2_TEST_EXPR_TYPE( (s_no_buffer)
                    , (option<_ , nt2::tag::buffer_>)
                    , (buffer_<>)
                    );

  NT2_TEST_EXPR_TYPE( s_int_buffer
                    , (option<_ , nt2::tag::buffer_>)
                    , (buffer_< buffer<int,1> >)
                    );
}

template<class U, class M, class T, class S>
struct  apply_
{
  typedef typename boost::mpl::apply <U , M, T, S>::type type;
};

////////////////////////////////////////////////////////////////////////////////
// Verify buffer generation for buffer_(X)
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( buffer_forced )
{
  using boost::mpl::_;
  using nt2::settings;
  using nt2::of_size_;
  using nt2::shared_;
  using nt2::buffer_;
  using nt2::automatic_;
  using nt2::no_padding_;
  using nt2::meta::normalize_settings;
  using nt2::tag::table_;
  using nt2::memory::buffer;

  NT2_TEST_EXPR_TYPE( (buffer_< buffer<int,1> >())
                    , (apply_ < _
                              , void
                              , int
                              , normalize_settings
                                < table_
                                , int
                                , settings
                                  ( of_size_<2,2>
                                  , no_padding_
                                  , automatic_
                                  )
                                >::type
                              >
                      )
                    , (buffer<int,1>)
                    );
}

////////////////////////////////////////////////////////////////////////////////
// Verify buffer generation for buffer_()
////////////////////////////////////////////////////////////////////////////////
struct make_iliffe
{
  template<class Dims, class Data, class Index>
  struct apply
  {
    typedef nt2::memory::iliffe_buffer<Data,Index> type;
  };
};

NT2_TEST_CASE( buffer_natural )
{
  using boost::mpl::_;
  using nt2::settings;
  using nt2::of_size_;
  using nt2::shared_;
  using nt2::automatic_;
  using nt2::buffer_;
  using nt2::no_padding_;
  using nt2::meta::normalize_settings;
  using nt2::tag::table_;
  using nt2::memory::iliffe_buffer;
  using nt2::memory::array_buffer;

  NT2_TEST_EXPR_TYPE( buffer_<>()
                    , (apply_ < _
                              , make_iliffe
                              , int
                              , normalize_settings
                                < table_
                                , int
                                , settings
                                  ( of_size_<2,2>
                                  , no_padding_
                                  , automatic_
                                  )
                                >::type
                              >
                      )
                    , ( iliffe_buffer < array_buffer<int , 4ul, 1>
                                      , array_buffer<int*, 2ul, 1>
                                      >
                      )
                    );
}
