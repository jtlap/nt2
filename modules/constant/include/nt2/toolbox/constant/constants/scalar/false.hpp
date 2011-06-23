//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//============================================================================== 
#ifndef NT2_TOOLBOX_CONSTANT_CONSTANTS_SCALAR_FALSE_HPP_INCLUDED
#define NT2_TOOLBOX_CONSTANT_CONSTANTS_SCALAR_FALSE_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>
#include <nt2/include/functions/splat.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::false_ ,tag::cpu_, (A0)
                            , (target_< scalar_<fundamental_<A0> > >)
                            )
  {
    typedef typename A0::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      return splat<result_type>(false);
    }
  };
} }

#endif
