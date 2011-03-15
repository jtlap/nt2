/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_SPLAT_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_SPLAT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Splat over terminal of simd domain using the pack::fill method
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::splat_
                      , tag::cpu_
                      , (A0)(A1)(T)(C)(Sema)
                      , (fundamental_<A0>)
                        ((target_< expr_< A1
                                        , domain_< simd::domain<T,C> >
                                        , tag::terminal_
                                        , Sema
                                        >
                                 >
                        ))
                      );

namespace nt2 { namespace ext
{
  template<class T, class C, class Sema, class Dummy>
  struct  call< tag::splat_ ( tag::fundamental_
                            , tag::target_<tag::expr_ < simd::domain<T,C>
                                                      , tag::terminal_
                                                      , Sema
                                                      >
                                          >
                            )
             , tag::cpu_
             , Dummy
             >
       : callable
  {
   template<class Sig> struct result;

   template<class This,class A0, class Target>
   struct result<This(A0,Target)> : meta::strip<Target>::type {};

   NT2_FUNCTOR_CALL(2)
   {
     typename NT2_RETURN_TYPE(2)::type that;
     that.fill(a0);
     return that;
   }
  };
} }

#endif
