//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_BOOLEAN_FUNCTIONS_COMPLEX_GENERIC_IF_ZERO_ELSE_ONE_HPP_INCLUDED
#define NT2_TOOLBOX_BOOLEAN_FUNCTIONS_COMPLEX_GENERIC_IF_ZERO_ELSE_ONE_HPP_INCLUDED

#include <nt2/toolbox/boolean/functions/if_zero_else_one.hpp>
<<<<<<< HEAD
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/sdk/simd/logical.hpp>
=======
#include <nt2/include/functions/is_nez.hpp>
>>>>>>> master

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::if_zero_else_one_, tag::cpu_, (A0)
<<<<<<< HEAD
                             , (generic_< complex_<floating_<A0> > >)
=======
                            ,  (generic_< complex_<floating_<A0> > >)
>>>>>>> master
                            )
  {
    typedef A0 result_type;
    result_type  operator()(A0 const& a0) const
    {
<<<<<<< HEAD
      return if_zero_else_one(is_nez(a0));
=======
      return result_type(nt2::if_zero_else_one(nt2::is_nez(a0)));
>>>>>>> master
    }
  };
} }

#endif
