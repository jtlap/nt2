//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_DIVCEIL_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_DIVCEIL_HPP_INCLUDED

#include <nt2/include/functions/ceil.hpp>
#include <nt2/include/functions/iceil.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/functions/rdivide.hpp>

#ifdef BOOST_MSVC
  #pragma warning(push)
  #pragma warning(disable: 4723) // potential divide by 0
#endif

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::divceil_, tag::cpu_, (A0)(A1)
                            , (scalar_< signed_<A0> >)
                              (scalar_< signed_<A1> >)
                            )
  {
    typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      if(a1)
        return iceil(double(a0)/double(a1)); 
      else
      {
        return (a0) ? ((a0>0) ? Valmax<result_type>() : Valmin<result_type>()) : Zero<result_type>();
      }
    }
  }; 
  
  NT2_FUNCTOR_IMPLEMENTATION( tag::divceil_, tag::cpu_, (A0)(A1)
                            , (scalar_< unsigned_<A0> >)
                              (scalar_< unsigned_<A1> >)
                            )
  {
    typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      if(a1)
        return rdivide(a0+(a1-One<result_type>()), a1); 
      else
      {
        return (a0) ? Valmax<result_type>() : Zero<result_type>();
      }
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( tag::divceil_, tag::cpu_, (A0)(A1)
                            , (scalar_< real_<A0> >)
                              (scalar_< real_<A1> >)
                            )
  {
    typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type result_type;
    NT2_FUNCTOR_CALL(2) { return ceil(a0/a1); }
  };
} }

#ifdef BOOST_MSVC
  #pragma warning(pop)
#endif

#endif
