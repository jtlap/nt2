//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_ROR_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_ROR_HPP_INCLUDED
//#include <nt2/sdk/meta/as_bits.hpp>
#include <nt2/include/functions/shli.hpp>
#include <nt2/include/functions/shri.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::ror_, tag::cpu_, (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return b_or(shri(a0, a1), shli(a0, (sizeof(A0)*CHAR_BIT-a1)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::ror_, tag::cpu_, (A0)(A1)
                            , (scalar_< real_<A0> >)(scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_integer<A0, unsigned>::type itype;
      const itype ia0 = bitwise_cast<itype, A0>(a0);
      return bitwise_cast<A0,itype>(
				    shri(ia0,a1) | shli(ia0, (sizeof(A0)*CHAR_BIT-a1))
				    ); 
    }
  };
} }

#endif
