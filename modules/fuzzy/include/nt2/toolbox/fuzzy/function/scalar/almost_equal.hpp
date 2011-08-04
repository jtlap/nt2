//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_ALMOST_EQUAL_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_ALMOST_EQUAL_HPP_INCLUDED
#include <nt2/include/constants/real.hpp>

#include <nt2/include/functions/dist.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/successor.hpp>
#include <nt2/include/functions/predecessor.hpp>
#include <nt2/include/functions/abs.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::almost_equal_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A1> >)(scalar_< integer_<A2> >)
                            )
  {

    typedef bool result_type;

    NT2_FUNCTOR_CALL(3)
    {
      return dist(a0, a1) <= nt2::abs(a2);
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::almost_equal_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< real_<A0> >)(scalar_< real_<A1> >)(scalar_< integer_<A2> >)
                            )
  {

    typedef bool result_type;

    NT2_FUNCTOR_CALL(3)
    {
      if (a0 == a1) return true;
      if (is_inf(a0) || is_inf(a1)) return (a0 == a1);
      if (is_nan(a0) || is_nan(a1)) return false;
      // see http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
      // by Bruce Dawson
      // Do not choose a2 negative or too large
      // assert(aa2 > 0 && aa2 < bitinteger(Nan<select_type>()) );
      A2 aa2 =  nt2::abs(a2); 
      return  (a0 <= successor(a1, aa2)) && (a0 >= predecessor(a1, aa2));
    }
  };
} }


#endif
