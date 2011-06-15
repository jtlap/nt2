//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_DETAILS_IS_POWER_OF_2_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_IS_POWER_OF_2_HPP_INCLUDED

#include <nt2/sdk/meta/mpl.hpp>
#include <nt2/sdk/memory/details/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

//==============================================================================
// is_power_of_2 on integers
//==============================================================================
NT2_REGISTER_DISPATCH ( tag::is_power_of_2_, tag::cpu_
                      , (A0), (scalar_< integer_<A0> >)
                      )

namespace nt2 { namespace ext
{
  template<class A0, class Dummy>
  struct  call< tag::is_power_of_2_(meta::scalar_< meta::integer_<A0> >)
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    typedef bool result_type;
    result_type operator()(A0 const& a0) const
    {
      return (!(a0 & (a0 - 1)) && a0);
    }
  };

} }

//==============================================================================
// is_power_of_2 on mpl integral
//==============================================================================
NT2_REGISTER_DISPATCH ( tag::is_power_of_2_, tag::cpu_
                      , (A0), (mpl_integral_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class A0, class Dummy>
  struct  call< tag::is_power_of_2_(meta::mpl_integral_<A0>)
              , tag::cpu_, Dummy
              >
        : callable
  {
    typedef bool result_type;
    result_type operator()(A0 const&) const
    {
      return meta::is_power_of_2<A0>::value;
    }
  };
} }

#endif
