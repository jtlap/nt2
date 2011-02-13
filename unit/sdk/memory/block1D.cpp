/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory::block - 1D"

#include <iostream>
#include <nt2/sdk/memory/block.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/sdk/memory/lead_padding.hpp>

#include <boost/array.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test for 1D dynamic buffer default ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(  block_1d_default_dyn_ctor
                  , (double)(float)
                    (nt2::uint64_t)(nt2::uint32_t)(nt2::uint16_t)(nt2::uint8_t)
                    (nt2::int64_t)(nt2::int32_t)(nt2::int16_t)(nt2::int8_t)
                  )
{
  using boost::is_same;
  using nt2::memory::block;
  using nt2::memory::allocator;

  typedef block < T,1, boost::array<int,1>, boost::array<int,1>
                , boost::mpl::vector_c<int,0>
                , nt2::memory::no_padding, allocator<T>
                >
  block_type;

  NT2_TEST((is_same<typename block_type::bases_type,boost::array<int,1> >::value));
  NT2_TEST((is_same<typename block_type::sizes_type,boost::array<int,1> >::value));
  NT2_TEST((is_same<typename block_type::stored_bases_type,boost::array<int,1> >::value));
  NT2_TEST((is_same<typename block_type::stored_sizes_type,boost::array<int,1> >::value));

  block_type b;

  NT2_TEST_EQUAL( b.template size<1>()          ,  0      );
  NT2_TEST_EQUAL( b.template lower<1>()         ,  0      );
  NT2_TEST_EQUAL( b.template upper<1>()         , -1      );
  NT2_TEST_EQUAL( b.template data<1>().origin() , (T*)(0) );
  NT2_TEST_EQUAL( b.template data<1>().begin()  , (T*)(0) );
  NT2_TEST_EQUAL( b.template data<1>().end()    , (T*)(0) );
}

////////////////////////////////////////////////////////////////////////////////
// Test for 1D static buffer default ctor
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(  block_1d_default_stc_ctor
                  , (double)(float)
                    (nt2::uint64_t)(nt2::uint32_t)(nt2::uint16_t)(nt2::uint8_t)
                    (nt2::int64_t)(nt2::int32_t)(nt2::int16_t)(nt2::int8_t)
                  )
{
  using boost::is_same;
  using nt2::memory::block;
  using nt2::memory::allocator;

  typedef block < T,1
                , boost::mpl::vector_c<int,1>
                , boost::mpl::vector_c<int,5>
                , boost::mpl::vector_c<int,0>
                , nt2::memory::no_padding, allocator<T>
                >
  block_type;

  NT2_TEST((is_same<typename block_type::bases_type,boost::mpl::vector_c<int,1> >::value));
  NT2_TEST((is_same<typename block_type::sizes_type,boost::mpl::vector_c<int,5> >::value));
  NT2_TEST((is_same<typename block_type::stored_bases_type,boost::mpl::vector_c<int,1> >::value));
  NT2_TEST((is_same<typename block_type::stored_sizes_type,boost::mpl::vector_c<int,5> >::value));

  block_type b;

  NT2_TEST_EQUAL( b.template size<1>()          ,  5      );
  NT2_TEST_EQUAL( b.template lower<1>()         ,  1      );
  NT2_TEST_EQUAL( b.template upper<1>()         ,  5      );
  NT2_TEST_NOT_EQUAL( b.template data<1>().origin() , (T*)(0) );
  NT2_TEST_EQUAL( b.template data<1>().begin()  , b.template data<1>().origin() - 1 );
  NT2_TEST_EQUAL( b.template data<1>().end()  , b.template data<1>().origin() + 4 );
}

////////////////////////////////////////////////////////////////////////////////
// Test for 1D dynamic buffer default ctor with funky storage order
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(  block_1d_default_dyn_ctor_storage
                  , (double)(float)
                    (nt2::uint64_t)(nt2::uint32_t)(nt2::uint16_t)(nt2::uint8_t)
                    (nt2::int64_t)(nt2::int32_t)(nt2::int16_t)(nt2::int8_t)
                  )
{
  using boost::is_same;
  using nt2::memory::block;
  using nt2::memory::allocator;

  typedef block < T,1, boost::array<int,1>, boost::array<int,1>
                , boost::mpl::vector_c<int,2>
                , nt2::memory::no_padding , allocator<T>
                >
  block_type;

  NT2_TEST((is_same<typename block_type::bases_type,boost::array<int,1> >::value));
  NT2_TEST((is_same<typename block_type::sizes_type,boost::array<int,1> >::value));
  NT2_TEST((is_same<typename block_type::stored_bases_type,boost::array<int,1> >::value));
  NT2_TEST((is_same<typename block_type::stored_sizes_type,boost::array<int,1> >::value));

  block_type b;

  NT2_TEST_EQUAL( b.template size<1>()          , 0       );
  NT2_TEST_EQUAL( b.template lower<1>()         , 0       );
  NT2_TEST_EQUAL( b.template upper<1>()         , -1      );
  NT2_TEST_EQUAL( b.template data<1>().origin() , (T*)(0) );
  NT2_TEST_EQUAL( b.template data<1>().begin()  , (T*)(0) );
  NT2_TEST_EQUAL( b.template data<1>().end()    , (T*)(0) );
}

////////////////////////////////////////////////////////////////////////////////
// Test for 1D static buffer default ctor with funky storage_order
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(  block_1d_default_stc_ctor_storage
                  , (double)(float)
                    (nt2::uint64_t)(nt2::uint32_t)(nt2::uint16_t)(nt2::uint8_t)
                    (nt2::int64_t)(nt2::int32_t)(nt2::int16_t)(nt2::int8_t)
                  )
{
  using boost::is_same;
  using nt2::memory::block;
  using nt2::memory::allocator;

  typedef block < T,1
                , boost::mpl::vector_c<int,1>
                , boost::mpl::vector_c<int,5>
                , boost::mpl::vector_c<int,2>
                , nt2::memory::no_padding, allocator<T>
                >
  block_type;

  NT2_TEST((is_same<typename block_type::bases_type,boost::mpl::vector_c<int,1> >::value));
  NT2_TEST((is_same<typename block_type::sizes_type,boost::mpl::vector_c<int,5> >::value));
  NT2_TEST((is_same<typename block_type::stored_bases_type,boost::mpl::vector_c<int,1> >::value));
  NT2_TEST((is_same<typename block_type::stored_sizes_type,boost::mpl::vector_c<int,5> >::value));

  block_type b;

  NT2_TEST_EQUAL( b.template size<1>()          ,  5      );
  NT2_TEST_EQUAL( b.template lower<1>()         ,  1      );
  NT2_TEST_EQUAL( b.template upper<1>()         ,  5      );
  NT2_TEST_NOT_EQUAL( b.template data<1>().origin() , (T*)(0) );
  NT2_TEST_EQUAL( b.template data<1>().begin()  , b.template data<1>().origin() - 1 );
  NT2_TEST_EQUAL( b.template data<1>().end()  , b.template data<1>().origin() + 4 );
}
