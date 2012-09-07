//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_GAMMAINC_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SCALAR_GAMMAINC_HPP_INCLUDED

#include <nt2/toolbox/euler/functions/gammainc.hpp>
#include <nt2/toolbox/boost_math/functions/gamma_p.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/scalar/is_ngtz.hpp>
#include <nt2/include/constants/nan.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gammainc_, tag::cpu_
                              , (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< arithmetic_<A1> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0, A1>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::gammainc(nt2::tofloat(a0), nt2::tofloat(a1));
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gammainc_, tag::cpu_
                              , (A0)(A1)
                            , (scalar_< floating_<A0> >)
                              (scalar_< floating_<A1> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      if(is_ngtz(a1)||is_ngtz(a0)) return Nan<result_type>(); 
      return boost_math::gamma_p(a0, a1); 
    }
  };
} }
       
#endif
