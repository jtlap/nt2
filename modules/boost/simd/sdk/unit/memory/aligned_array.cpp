//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::memory::aligned_array"

#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/mpl/int.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

using boost::mpl::int_;

NT2_TEST_CASE_TPL( aligned_array_alignment
                 , (int_<1>)(int_<2>)(int_<4>)(int_<8>)
                   (int_<16>)(int_<32>)(int_<64>)
                 )
{


}
