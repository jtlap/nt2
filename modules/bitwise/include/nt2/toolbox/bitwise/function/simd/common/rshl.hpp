//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_RSHL_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_RSHL_HPP_INCLUDED

#include <nt2/include/functions/shli.hpp>
#include <nt2/include/functions/shri.hpp>  
#include <nt2/include/functions/is_gtz.hpp>  

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION_IF ( tag::rshl_, tag::cpu_, (A0)(A1)(X)
                                , (boost::mpl::equal_to < cardinal_of<A0>
                                                        , cardinal_of<A1>
                                                        >
                                  )
                                , (tag::rshl_ ( simd_<arithmetic_<A0>,X>
                                              , simd_<integer_<A1>,X>
                                              )
                                  )
                                , ((simd_<arithmetic_<A0>,X>))
                                  ((simd_<integer_<A1>,X>))
                                )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2) { return map(functor<tag::rshl_>(), a0, a1); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::rshl_, tag::cpu_, (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))((scalar_ < integer_<A1> >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      if(is_gtz(a1)) return shli(a0, a1);  else return shri(a0, -a1);
    }
  };
} }

#endif
