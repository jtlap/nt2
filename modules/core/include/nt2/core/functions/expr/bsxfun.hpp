//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_BSXFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_BSXFUN_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/bsxfun.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/sum.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::bsxfun_, tag::cpu_,
                              (A0)(A1)(A2),
                               (unspecified_<A0>)
                               (ast_<A1>)
                               (ast_<A2)
                               )
  {
    typedef typename meta::call<tag::repmat(A1 const&, of_size_max) >::type T1;
    typedef typename meta::call<tag::repmat(A2 const&, of_size_max) >::type T2;
    typedef typename meta::call<A0(T1 const&, T2 const & )>::type) >::type
      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      const of_size_max s1 = size(a1);
      const of_size_max s2 = size(a2);
      of_size_max s ;
      for(int i = 1; i <= numel(s))
        {
          s(i) = 1; 
          if (s1(i) == 1) s(i) = s(2);
          if (s2(i) == 1) s(i) = s(1);
        }
      return a0(repmat(a1,s1), repmat(a2,s2));
    }
  };

} }

#endif
