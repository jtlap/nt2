//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_EXPR_REDUCE_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_EXPR_REDUCE_HPP_INCLUDED
#include <nt2/toolbox/polynom/functions/reduce.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/numel.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::reduce_, tag::cpu_
                              , (A0)
                              , ((ast_<A0, nt2::container::domain>))
                            )
  {

    typedef typename A0::value_type value_type;
    typedef typename nt2::meta::call<nt2::tag::colon_(size_t, size_t)>::type                     T1;
    typedef typename nt2::meta::call<nt2::tag::function_(const A0&, size_t, T1)>::type  result_type;
    NT2_FUNCTOR_CALL(1)
    {
      size_t na0 =  numel(a0); 
      size_t idx = na0+1;
      for(size_t i=1; i <= na0 ; i++)
      {
        if (a0(i)) {idx = i; break;}
      }
      return a0(One<size_t>(), _(idx,na0)); 
    }
  };
} }


#endif
