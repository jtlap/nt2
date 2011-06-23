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
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_power_of_2_, tag::cpu_
                            , (A0), (scalar_< integer_<A0> >)
                            )
  {
    typedef bool result_type;
    NT2_FUNCTOR_CALL(1) { return (!(a0 & (a0 - 1)) && a0); }
  };
} }

//==============================================================================
// is_power_of_2 on mpl integral
//==============================================================================
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_power_of_2_, tag::cpu_
                            , (A0), (mpl_integral_<A0>)
                            )
  {
    typedef bool result_type;
    NT2_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      return meta::is_power_of_2<A0>::value;
    }
  };
} }

#endif
