//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SCALAR_SPLAT_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SCALAR_SPLAT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// splat for scalar types
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::splat_ , tag::cpu_ , (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              (target_< scalar_< fundamental_<A1> > >)
                            )
  {
    typedef typename strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      ignore_unused(a1); 
      result_type that = static_cast<result_type>(a0);
      return that;
    }
  };
} }

#endif
