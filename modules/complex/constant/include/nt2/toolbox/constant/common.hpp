//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_CONSTANT_COMMON_HPP_INCLUDED
#define NT2_TOOLBOX_CONSTANT_COMMON_HPP_INCLUDED

#include <boost/simd/sdk/constant/common.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( Tag, tag::cpu_, (Tag)(A0)
                                   , ((target_< generic_< complex_< arithmetic_<A0> > > >))
                                   )
  {
    typedef typename A0::type                               result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const&) const
    {
      typedef typename meta::as_real<result_type>::type real_t;
           
      return result_type( boost::dispatch::functor<Tag>()(boost::dispatch::meta::as_<real_t>())
                        , Zero<real_t>()
                        );
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( Tag, tag::cpu_, (Tag)(A0)
                                   , ((target_< generic_< imaginary_< arithmetic_<A0> > > >))
                                   )
  {
    typedef typename A0::type                               result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const&) const
    {
      typedef typename meta::as_real<result_type>::type real_t;
      return result_type(boost::dispatch::functor<Tag>()(boost::dispatch::meta::as_<real_t>()));
    }
  };
  
} }

#endif
