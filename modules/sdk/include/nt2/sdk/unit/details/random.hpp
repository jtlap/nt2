/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_UNIT_DETAILS_RANDOM_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_RANDOM_HPP_INCLUDED
#include <nt2/sdk/constant/eps_related.hpp>
#include <nt2/sdk/unit/details/ulpdist.hpp>
namespace nt2
{
  namespace details
  {
    
    template < class T> T nt2_random(T a0, T a1,  double_ )
    {
      if (a0 == a1) return a0; 
      return (a1-a0)*((double)rand()/RAND_MAX)+a0; //TO DO
    }
    
    template < class T > T nt2_random(T a0, T a1,  float_ )
    {
      if (a0 == a1) return a0; 
      return T((a1-a0)*((double)rand()/RAND_MAX)+a0); //TO DO
    }
    
    
    template < class T > T nt2_random(T a0, T a1,  other_ )
    {
      if (a0 == a1) return a0; 
      if (a1 < a0) { T c = a0;  a0 = a1;  a1 = a0; }
      return T((a1-a0)*((double)rand()/RAND_MAX)+a0); //TO DO
    }
    
   
    template < class T1, class T2> T1  random(T1 a0, T2 a1)
    {
      typedef typename std::tr1::result_of<meta::arithmetic(T1, T2)>::type type; 
      return nt2_random(type(a0), type(a1), typename details::classif<T1>::type()); 
    }
  }
  
}
#endif

// /////////////////////////////////////////////////////////////////////////////
// End of random.hpp
// /////////////////////////////////////////////////////////////////////////////
