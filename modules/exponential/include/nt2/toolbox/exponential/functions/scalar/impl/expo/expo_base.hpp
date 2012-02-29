//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPO_EXPO_BASE_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPO_EXPO_BASE_HPP_INCLUDED
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/is_nan.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      template < class A0,
         class Tag,
         class Style , 
         class Speed_Tag = fast_tag,
         class base_A0 = typename meta::scalar_of<A0>::type> 
      struct exponential{}; 


      template < class A0, class Tag,  class Speed_Tag> 
      struct exponential< A0, Tag, tag::not_simd_type, Speed_Tag >
      {
    typedef exp_reduction<A0,Tag>                        reduc_t;
    typedef exp_finalization<A0,Tag,Speed_Tag>        finalize_t; 
    // compute exp(ax) where a is 1, 2 or ten depending on Tag
    static inline A0 expa(const A0& a0)
    {
       if (reduc_t::isgemaxlog(a0)) return Inf<A0>();
       if (reduc_t::isleminlog(a0)) return Zero<A0>();
       if (is_nan(a0)) return a0; 
      A0 hi, lo, x; 
      A0 k = reduc_t::reduce(a0, hi, lo, x);
      A0 c = reduc_t::approx(x);
          return finalize_t::finalize(a0, x, c, k, hi, lo); 
    }
      };     
    }
  }
}


#endif
