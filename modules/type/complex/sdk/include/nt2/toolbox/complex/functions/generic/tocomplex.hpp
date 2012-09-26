//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_COMPLEX_FUNCTIONS_GENERIC_TOCOMPLEX_HPP_INCLUDED
#define NT2_TOOLBOX_COMPLEX_FUNCTIONS_GENERIC_TOCOMPLEX_HPP_INCLUDED
#include <nt2/toolbox/complex/functions/tocomplex.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tocomplex_, tag::cpu_, (A0)
                            , (generic_< arithmetic_<A0> >)
                            )
  {
    typedef typename meta::as_complex<A0>::type  result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return result_type(a0);
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tocomplex_, tag::cpu_, (A0)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      typedef typename meta::as_real<A0>::type rtype;
      return result_type(Zero<rtype>(), nt2::imag(a0));
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tocomplex_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_complex<A0>::type const &result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0;
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tocomplex_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::as_complex<rtype>::type const &result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return result_type(nt2::real(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tocomplex_, tag::cpu_, (A0)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< arithmetic_<A0> >)              
                            )
  {
    typedef typename meta::as_complex<A0>::type const &result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      return result_type(a0, a1);
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tocomplex_, tag::cpu_, (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< imaginary_<A1> >)              
                            )
  {
    typedef typename meta::as_complex<A0>::type const &result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return result_type(a0, nt2::imag(a1));
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tocomplex_, tag::cpu_, (A0)(A1)
                            , (generic_< imaginary_<A0> >)
                              (generic_< arithmetic_<A1> >)              
                            )
  {
    typedef typename meta::as_complex<A0>::type const &result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return result_type(a1, nt2::imag(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tocomplex_, tag::cpu_, (A0)(A1)
                            , (generic_< imaginary_<A0> >)
                              (generic_< dry_<A1> >)              
                            )
  {
    typedef typename meta::as_complex<A0>::type const &result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return result_type(nt2::real(a1), nt2::imag(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tocomplex_, tag::cpu_, (A0)(A1)
                            , (generic_< dry_<A0> >)
                              (generic_< imaginary_<A1> >)              
                            )
  {
    typedef typename meta::as_complex<A0>::type const &result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return result_type(nt2::real(a0), nt2::imag(a1));
    }
  };
  
} }

#endif
