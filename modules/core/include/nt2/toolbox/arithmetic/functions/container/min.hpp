//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_CONTAINER_MIN_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_CONTAINER_MIN_HPP_INCLUDED

#include <nt2/toolbox/arithmetic/functions/min.hpp>
#include <nt2/include/functions/minimum.hpp>

namespace nt2
{
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::min_, min     , 3)
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::min_, tag::cpu_
                            , (A0)
                            , (generic_< unspecified_<A0> >)
                            )
  {
    typedef typename meta::call< nt2::tag::minimum_(A0 const&)>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0) const
    {
      return nt2::minimum(a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::min_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (generic_< unspecified_<A0> >)
                              (target_< unspecified_<A1> >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef typename meta::call< nt2::tag::minimum_(A0 const&, A2 const&)>::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 const&, A2 const& a2) const
    {
      return nt2::minimum(a0,a2);
    }
  };
} }

#endif
