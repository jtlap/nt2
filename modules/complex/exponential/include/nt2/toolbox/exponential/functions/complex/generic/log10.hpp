//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_LOG10_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_LOG10_HPP_INCLUDED
#include <nt2/include/functions/log10.hpp>
#include <nt2/include/functions/arg.hpp>
#include <nt2/include/functions/abs.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log10_, tag::cpu_
                            , (A0)
                            , (generic_< complex_<floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    { 
      typedef typename meta::as_real<A0>::type             rtype;
      return result_type(nt2::log10(nt2::abs(a0)),
                         nt2::arg(a0)/Log_10<rtype>()); 
    }
  };
  
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log10_, tag::cpu_
//                             , (A0)
//                             , (generic_< imaginary_<floating_<A0> > >)
//                             )
//   {
//     typedef typename meta::as_real<A0>::type             rtype; 
//     typedef typename meta::as_complex<rtype>::type result_type;
//     NT2_FUNCTOR_CALL(1)
//     {
//       return result_type(arg(a0)/Log_10<A0>()); 
//     }
//   };

//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log10_, tag::cpu_
//                             , (A0)
//                             , (generic_< dry_<floating_<A0> > >)
//                             )
//   {
//     typedef typename meta::as_real<A0>::type             rtype; 
//     typedef typename meta::as_complex<rtype>::type result_type;
//     NT2_FUNCTOR_CALL(1)
//     {
//       return result_type(nt2::log10(nt2::abs(real(a0))), nt2::arg(real(a0))/Log_10<A0>()); 
//     }
//   };      
} }


#endif
