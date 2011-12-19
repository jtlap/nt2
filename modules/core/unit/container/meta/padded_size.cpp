/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::padded_size"

#include <vector>
#include <boost/type_traits/is_same.hpp>
#include <nt2/core/utility/of_size/of_size.hpp>
#include <nt2/core/container/meta/padded_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Check reference_
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( no_padding )
{
  using nt2::of_size_;
  using boost::mpl::int_;
  using nt2::meta::padded_size;

  NT2_TEST_EQUAL( (padded_size< of_size_<2,3,4>, int_<1>, int_<1> >::value)
                , 2*3*4
                );

  NT2_TEST_EQUAL( (padded_size< of_size_<5,4,2>, int_<32>, int_<1> >::value)
                , 64
                );
}
