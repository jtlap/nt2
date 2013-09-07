//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/swar/include/functions/sort.hpp>
#include <nt2/include/functions/load.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/meta/cardinal_as.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

#include <algorithm>

template<typename T>
struct  not_that_small
      : boost::mpl::bool_ < boost::simd::meta::
                            cardinal_as<T, BOOST_SIMD_DEFAULT_EXTENSION>::value
                          <= 8
                          >
{};

NT2_TEST_CASE_TPL_MPL ( sort
                      , NT2_TEST_SEQ_MPL_FILTER ( NT2_SIMD_TYPES
                                                , not_that_small<boost::mpl::_>
                                                )
                      )
{
  using nt2::sort;
  using nt2::tag::sort_;
  using nt2::load;
  using boost::simd::native;

  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             vT;

  T data[vT::static_size];

  for(int i = 0; i<vT::static_size;++i) data[i] = i;

  vT ordered = load<vT>(&data[0]);

  do
  {
    vT current = load<vT>(&data[0]);
    vT r = nt2::sort(current);
    NT2_TEST_EQUAL(r,ordered);

  } while ( std::next_permutation(data,data+vT::static_size) );
}
