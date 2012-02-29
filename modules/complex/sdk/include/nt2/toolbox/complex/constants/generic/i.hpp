//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_COMPLEX_CONSTANTS_GENERIC_I_HPP_INCLUDED
#define NT2_TOOLBOX_COMPLEX_CONSTANTS_GENERIC_I_HPP_INCLUDED

#include <nt2/toolbox/complex/constants/i.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
#include <nt2/sdk/complex/meta/as_imaginary.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::I, tag::cpu_, (A0)
                             , ((target_< generic_< imaginary_< arithmetic_<A0> > > >))
                             )
  {
    typedef typename A0::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      typedef typename meta::as_real<result_type>::type real_t;
      return bitwise_cast<result_type>(One<real_t>());
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::I, tag::cpu_, (A0)
                             , ((target_< generic_< dry_< arithmetic_<A0> > > >))
                             )
  {
    typedef typename meta::as_imaginary<typename A0::type>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return I<result_type>();
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::I, tag::cpu_, (A0)
                             , ((target_< scalar_< arithmetic_<A0> > >))
                             )
  {
    typedef typename meta::as_imaginary<typename A0::type>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return I<result_type>(); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::I, tag::cpu_, (A0)(X)
                             , ((target_< simd_< arithmetic_<A0>, X> >))
                             )
  {
    typedef typename meta::as_imaginary<typename A0::type>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return I<result_type>(); 
    }
  };


  
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::I, tag::cpu_, (A0)
                             , ((target_< generic_< complex_< arithmetic_<A0> > > >))
                             )
  {
    typedef typename meta::as_real<typename A0::type>::type real_t;
    typedef typename meta::as_imaginary<real_t>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const&) const
    {
      return I<result_type>(); 
    }
  };
} }

#endif
