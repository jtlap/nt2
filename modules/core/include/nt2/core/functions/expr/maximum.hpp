//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_MAXIMUM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_MAXIMUM_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/toolbox/reduction/functions/maximum.hpp>
#include <nt2/toolbox/arithmetic/functions/max.hpp>

namespace nt2 {
  struct empty_t {};
  const meta::as_<empty_t> empty_ = {};
 
  namespace ext
  {
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::maximum_, tag::cpu_,
                                (A0)(A2),
                                (ast_<A0>)
                                ( unspecified_< meta::as_<nt2::empty_t> const >)
                                (scalar_<integer_<A2> > )
                                )
    {
      typedef typename meta::call<tag::maximum_(A0 const&,A2 const&)>::type
        result_type;
      
      BOOST_FORCEINLINE result_type operator()(A0 const& a0, nt2::empty_t const&, A2 const& a2) const
      {
        return nt2::maximum(a0, a2);
      }
    };
  }  
}

#endif
