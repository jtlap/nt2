//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_SDK_MEMORY_DETAILS_STORE_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_STORE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// store for scalar types
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/mpl.hpp>
#include <nt2/sdk/memory/details/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over store_
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::store_, tag::cpu_, (A0)(A1)(A2)
                            , (scalar_< fundamental_<A0> >)
                              (iterator_< scalar_< fundamental_<A1> > >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef typename strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
      A1 that = a1;
      std::advance(that,a2);
      return *that = a0;
    }
  };
} }

#endif
