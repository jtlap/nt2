//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::meta::padded_size"

#include <vector>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/sdk/memory/cache_padding.hpp>
#include <nt2/core/utility/of_size/pad.hpp>
#include <nt2/core/utility/of_size/of_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Check pad with no_padding
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( pad_with_no_padding )
{
  using nt2::pad;
  using nt2::of_size_;
  using boost::fusion::at_c;
  using nt2::memory::no_padding;

  NT2_TEST_EQUAL( at_c<0>( pad<double>(of_size_<6,1,2,3>(), no_padding()) ), 6u );
  NT2_TEST_EQUAL( at_c<1>( pad<double>(of_size_<6,1,2,3>(), no_padding()) ), 1u );
  NT2_TEST_EQUAL( at_c<2>( pad<double>(of_size_<6,1,2,3>(), no_padding()) ), 2u );
  NT2_TEST_EQUAL( at_c<3>( pad<double>(of_size_<6,1,2,3>(), no_padding()) ), 3u );

  NT2_TEST_EQUAL( at_c<0>( pad<float>(of_size_<6,1,2,3>(), no_padding()) ), 6u );
  NT2_TEST_EQUAL( at_c<1>( pad<float>(of_size_<6,1,2,3>(), no_padding()) ), 1u );
  NT2_TEST_EQUAL( at_c<2>( pad<float>(of_size_<6,1,2,3>(), no_padding()) ), 2u );
  NT2_TEST_EQUAL( at_c<3>( pad<float>(of_size_<6,1,2,3>(), no_padding()) ), 3u );

  NT2_TEST_EQUAL( at_c<0>( pad<short>(of_size_<6,1,2,3>(), no_padding()) ), 6u );
  NT2_TEST_EQUAL( at_c<1>( pad<short>(of_size_<6,1,2,3>(), no_padding()) ), 1u );
  NT2_TEST_EQUAL( at_c<2>( pad<short>(of_size_<6,1,2,3>(), no_padding()) ), 2u );
  NT2_TEST_EQUAL( at_c<3>( pad<short>(of_size_<6,1,2,3>(), no_padding()) ), 3u );

  NT2_TEST_EQUAL( at_c<0>( pad<char>(of_size_<6,1,2,3>(), no_padding()) ), 6u );
  NT2_TEST_EQUAL( at_c<1>( pad<char>(of_size_<6,1,2,3>(), no_padding()) ), 1u );
  NT2_TEST_EQUAL( at_c<2>( pad<char>(of_size_<6,1,2,3>(), no_padding()) ), 2u );
  NT2_TEST_EQUAL( at_c<3>( pad<char>(of_size_<6,1,2,3>(), no_padding()) ), 3u );
}

////////////////////////////////////////////////////////////////////////////////
// Check pad with cache_padding
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( pad_with_cache_padding )
{
  using nt2::pad;
  using nt2::of_size_;
  using boost::fusion::at_c;
  using nt2::memory::cache_padding;
  using boost::simd::memory::align_on;

  std::size_t cls = nt2::config::shared_cache_line_size();
  std::size_t dsz = align_on (6*sizeof(double), cls) / sizeof(double);
  std::size_t fsz = align_on (6*sizeof(float) , cls) / sizeof(float);
  std::size_t ssz = align_on (6*sizeof(short) , cls) / sizeof(short);
  std::size_t csz = align_on (6*sizeof(char)  , cls) / sizeof(char);

  NT2_TEST_EQUAL( at_c<0>( pad<double>(of_size_<6,1,2,3>(), cache_padding()) ), dsz );
  NT2_TEST_EQUAL( at_c<1>( pad<double>(of_size_<6,1,2,3>(), cache_padding()) ), 1u );
  NT2_TEST_EQUAL( at_c<2>( pad<double>(of_size_<6,1,2,3>(), cache_padding()) ), 2u );
  NT2_TEST_EQUAL( at_c<3>( pad<double>(of_size_<6,1,2,3>(), cache_padding()) ), 3u );

  NT2_TEST_EQUAL( at_c<0>( pad<float>(of_size_<6,1,2,3>(), cache_padding()) ), fsz );
  NT2_TEST_EQUAL( at_c<1>( pad<float>(of_size_<6,1,2,3>(), cache_padding()) ), 1u );
  NT2_TEST_EQUAL( at_c<2>( pad<float>(of_size_<6,1,2,3>(), cache_padding()) ), 2u );
  NT2_TEST_EQUAL( at_c<3>( pad<float>(of_size_<6,1,2,3>(), cache_padding()) ), 3u );

  NT2_TEST_EQUAL( at_c<0>( pad<short>(of_size_<6,1,2,3>(), cache_padding()) ), ssz );
  NT2_TEST_EQUAL( at_c<1>( pad<short>(of_size_<6,1,2,3>(), cache_padding()) ), 1u );
  NT2_TEST_EQUAL( at_c<2>( pad<short>(of_size_<6,1,2,3>(), cache_padding()) ), 2u );
  NT2_TEST_EQUAL( at_c<3>( pad<short>(of_size_<6,1,2,3>(), cache_padding()) ), 3u );

  NT2_TEST_EQUAL( at_c<0>( pad<char>(of_size_<6,1,2,3>(), cache_padding()) ), csz );
  NT2_TEST_EQUAL( at_c<1>( pad<char>(of_size_<6,1,2,3>(), cache_padding()) ), 1u );
  NT2_TEST_EQUAL( at_c<2>( pad<char>(of_size_<6,1,2,3>(), cache_padding()) ), 2u );
  NT2_TEST_EQUAL( at_c<3>( pad<char>(of_size_<6,1,2,3>(), cache_padding()) ), 3u );
}

