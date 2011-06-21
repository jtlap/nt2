//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_SIMD_PACK_SPLAT_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_SPLAT_HPP_INCLUDED

#include <nt2/include/functions/splat.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::splat_ , tag::cpu_
                            , (A0)(A1)(T)(C)(Sema)
                            , (scalar_< fundamental_<A0> >)
                              ((target_< expr_< A1
                                              , domain_< simd::domain<T,C> >
                                              , tag::terminal_
                                              , Sema
                                              >
                                       >
                              ))
                            )
  {
   typedef typename strip<A1>::type::type result_type;

   NT2_FUNCTOR_CALL(2)
   {
     result_type that;
     that.fill(a0);
     return that;
   }
  };
} }

#endif
