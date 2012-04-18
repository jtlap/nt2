//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_SUMP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_SUMP_HPP_INCLUDED

#include <nt2/core/functions/sump.hpp>
#include <nt2/include/functions/pow_abs.hpp>

//TODO include complex cases
namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sump_, tag::cpu_, (A0)
                            , (scalar_< floating_<A0> >)
                              (scalar_< arithmetic_<A0>)
                            )
  {
    typedef typename  meta::as_floating<A0>::type  f_type;
    typedef typename  meta::as_real<f_type> result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& a, A0 const& p) const
    {
      return pow_abs(a, p);
    }
  };
} }

#endif
