//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_BITWISE_NOTOR_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_BITWISE_NOTOR_HPP_INCLUDED

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION_IF( tag::bitwise_notor_, tag::cpu_, (A0)(A1), 
				 (boost::mpl::bool_<sizeof(A0) == sizeof(A1)>), 				 
                                 ( tag::bitwise_notor_
				  ( scalar_<fundamental_<A0> >, 
				    scalar_<fundamental_<A1> >
				    )
				  ), 
                               (scalar_< fundamental_<A0> >)
                               (scalar_< fundamental_<A1> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_integer<A0, unsigned>::type bts;
      return bitwise_cast<A0>(b_or(b_not(bitwise_cast<bts>(a0)),
					 bitwise_cast<bts>(a1)
					 )
				   ); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::bitwise_notor_, tag::cpu_, (A0)(A1)
                            , (scalar_< bool_<A0> >)
                              (scalar_< bool_<A1> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2) { return a1 || !a0; }

  };
} }

#endif
