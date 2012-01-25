//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_SINCOS_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_SINCOS_HPP_INCLUDED
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/sinhcosh.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::sincos_, tag::cpu_,
                             (A0),
                             (generic_ < complex_<floating_ < A0> > > )
                             (generic_ < complex_<floating_ < A0> > > )
                             (generic_ < complex_<floating_ < A0> > > )
                             )
  {
    typedef int result_type;    
    inline int operator()(A0 const& a0,A0 & a1,A0 & a2) const
    {
      typedef typename meta::as_real<A0>::type rtype; 
      rtype c, s, ch, sh;
      sincos(real(a0), s, c);
      sinhcosh(imag(a0), sh, ch);
      a1 =  A0(s*ch, c*sh);     
      a2 =  A0(c*ch, -s*sh);
      return 0; 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::sincos_, tag::cpu_,
                             (A0)(A1),
                             (generic_ < imaginary_<floating_ < A0> > > )
                             (generic_ < dry_<floating_ < A1> > > )
                             (generic_ < imaginary_<floating_ < A0> > > )
                             )
  {
    typedef int result_type;    
    inline int operator()(A0 const& a0,A1 & a1,A0 & a2) const
    {
      typedef typename meta::as_real<A0>::type rtype; 
      rtype ch, sh;
      sinhcosh(imag(a0), sh, ch);
      a1 =  A1(ch);
      a2 =  A0(-sh);     
      return 0; 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::sincos_, tag::cpu_,
                             (A0),
                             (generic_ < dry_<floating_ < A0> > > )
                             (generic_ < dry_<floating_ < A0> > > )
                             (generic_ < dry_<floating_ < A0> > > )
                             )
  {
    typedef int result_type;    
    inline int operator()(A0 const& a0,A0 & a1,A0 & a2) const
    {
      typedef typename meta::as_real<A0>::type rtype; 
      rtype c, s;
      sincos(real(a0), s, c);
      a1 =  A0(c);
      a2 =  A0(s);     
      return 0; 
    }
  };

  
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::sincos_, tag::cpu_,
                             (A0),
                             (generic_ < complex_<floating_ < A0> > > )
                             (generic_ < complex_<floating_ < A0> > > )
                             )
  {
    typedef A0 result_type;    
    inline A0 operator()(A0 const& a0,A0 & a2) const
    {
      result_type a1;
      sincos(a0, a1, a2);
      return a1; 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::sincos_, tag::cpu_,
                             (A0),
                             (generic_ < complex_<floating_<A0> > > )
                             )
  {
    typedef boost::fusion::tuple<A0, A0>           result_type;
    NT2_FUNCTOR_CALL(1)
      {
        result_type res;
        sincos(a0, boost::fusion::at_c<0>(res), boost::fusion::at_c<1>(res));
        return res;
      }
  };
} }


#endif
