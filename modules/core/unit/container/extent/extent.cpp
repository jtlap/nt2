/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::extent"

#include <boost/type_traits/is_same.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/core/container/extent/extent.hpp>
#include <nt2/core/settings/size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(boost::proto::tag::function, tag::cpu_
                            , (A0)(S0)
                            , ((container_< unspecified_<A0>, S0 >))
                            )
  {
    typedef A0& result_type;
    result_type operator()(A0& a0) const { return a0; }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Pass some allocator_ as an option and check everythign go out properly
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( default_constructor )
{
  using boost::is_same;
  using nt2::_2D;
  using nt2::container::extent;

  extent<_2D> e;
}
