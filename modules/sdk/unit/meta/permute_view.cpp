/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::permute_view"

#include <boost/array.hpp>
#include <boost/fusion/adapted/array.hpp>

#include <nt2/sdk/meta/permute_view.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

struct some_permutation
{
  template<class Size, class Index>
  struct apply : boost::mpl::size_t<Size::value - 1 - Index::value>
  {};
};

////////////////////////////////////////////////////////////////////////////////
// Test permute view
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(permute_view)
{
  using boost::array;
  using boost::is_same;
  using nt2::meta::permute_view;

  typedef boost::array<std::size_t,4> Seq;
  Seq sizes = {{5,2,4,3}};

  permute_view<Seq,some_permutation> permuted(sizes);

  NT2_TEST_EQUAL( boost::fusion::at_c<0>(sizes), boost::fusion::at_c<3>(permuted));
  NT2_TEST_EQUAL( boost::fusion::at_c<1>(sizes), boost::fusion::at_c<2>(permuted));
  NT2_TEST_EQUAL( boost::fusion::at_c<2>(sizes), boost::fusion::at_c<1>(permuted));
  NT2_TEST_EQUAL( boost::fusion::at_c<3>(sizes), boost::fusion::at_c<0>(permuted));

}

