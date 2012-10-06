//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_COMPLEX_CONSTANTS_GENERIC_CNAN_HPP_INCLUDED
#define NT2_TOOLBOX_COMPLEX_CONSTANTS_GENERIC_CNAN_HPP_INCLUDED

#include <nt2/toolbox/complex/constants/cnan.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::Cnan, tag::cpu_, (A0)
                             , ((target_< generic_< complex_< arithmetic_<A0> > > >))
                             )
  {
    typedef typename meta::as_real<typename A0::type>::type r_type;
    typedef typename meta::as_complex<r_type>::type result_type;      
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const&) const
    {
      return result_type(Nan<r_type>(),Nan<r_type>());
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::Cnan, tag::cpu_, (A0)
                             , ((target_< generic_< imaginary_< arithmetic_<A0> > > >))
                             )
  {
    typedef typename meta::as_real<typename A0::type>::type r_type;
    typedef typename meta::as_complex<r_type>::type result_type;      
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const&) const
    {
      return Cnan<result_type>();
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::Cnan, tag::cpu_, (A0)
                             , ((target_< generic_< dry_< arithmetic_<A0> > > >))
                             )
  {
    typedef typename meta::as_real<typename A0::type>::type r_type;
    typedef typename meta::as_complex<r_type>::type result_type;      
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const&) const
    {
      return  Cnan<result_type>();
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::Cnan, tag::cpu_, (A0)
                             , ((target_< scalar_< arithmetic_<A0> > >))
                             )
  {
    typedef typename meta::as_real<typename A0::type>::type r_type;
    typedef typename meta::as_complex<r_type>::type result_type;      
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const&) const
    {
      return Cnan<result_type>();
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::Cnan, tag::cpu_, (A0)(X)
                             , ((target_< simd_< arithmetic_<A0>, X> >))
                             )
  {
    typedef typename meta::as_real<typename A0::type>::type r_type;
    typedef typename meta::as_complex<r_type>::type result_type;      
    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const&) const
    {
      return Cnan<result_type>();
    }
  };  
} }

#endif
