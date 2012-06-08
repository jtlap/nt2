//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_CDIFF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_CDIFF_HPP_INCLUDED

#include <nt2/core/functions/cdiff.hpp>
#include <nt2/core/functions/common/cdiff.hpp>
#include <nt2/table.hpp>
#include <nt2/core/functions/of_size.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cdiff_, tag::cpu_,
                              (A0),
                              (scalar_<fundamental_<A0> >)
                            )
  {
    typedef table<A0, of_size_<0, 0> > result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& ) const
    {
      result_type t; 
      return t; 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cdiff_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<A0>)(scalar_<integer_<A1> >)
                            )
  {
    typedef table<A0, of_size_<0, 0> > result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& ,
                                             A1 const& ) const
    {
      result_type t; 
      return t; 
    }
  };
  
} } 

#endif
