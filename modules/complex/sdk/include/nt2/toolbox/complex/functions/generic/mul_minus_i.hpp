//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_COMPLEX_FUNCTIONS_GENERIC_MUL_MINUS_I_HPP_INCLUDED
#define NT2_TOOLBOX_COMPLEX_FUNCTIONS_GENERIC_MUL_MINUS_I_HPP_INCLUDED

#include <nt2/toolbox/complex/functions/mul_minus_i.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/constants/unary_minus.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mul_minus_i_, tag::cpu_, (A0)
                            , (generic_< complex_ < arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return result_type(nt2::imag(a0), -nt2::real(a0));
    }
  }; 
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mul_minus_i_, tag::cpu_, (A0)
                            , (generic_< arithmetic_<A0> >)
                            )
  {
    typedef typename meta::as_imaginary<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return result_type(-a0);
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mul_minus_i_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > > )
                            )
  {
    typedef typename meta::as_imaginary<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return result_type(-nt2::real(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mul_minus_i_, tag::cpu_, (A0)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_dry<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return result_type(nt2::imag(a0));
    }
  };
  
} }

#endif
