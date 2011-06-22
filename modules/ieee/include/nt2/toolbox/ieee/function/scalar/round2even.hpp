//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_ROUND2EVEN_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_ROUND2EVEN_HPP_INCLUDED

#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/include/constants/properties.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::round2even_, tag::cpu_ , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1) { return a0; }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::round2even_, tag::cpu_ , (A0)
                            , (scalar_< real_<A0> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      const result_type v = nt2::abs(a0);
      const result_type t2n = Two2nmb<result_type>();
      volatile result_type d0 = (v+t2n);
      volatile result_type d = (d0-t2n);
      d = (v < t2n)?d:v;
      return a0 < 0? -d : d;
    }
  };
} }

#endif
