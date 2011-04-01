/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_UNIT_DETAILS_TESTS_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_TESTS_HPP_INCLUDED
//#include <nt2/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/details/ulpdist.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <iostream>

namespace nt2 { namespace details
{
  template<class T, class U, class V>					
  inline bool test_ulp_eq( char const* x1
			   , char const* x2		
			   , char const* x3				
			   , int line
			   , char const * fn			
			   , T const & t
			   , U const & u			
			   , V const & v				
			   )						
  {									
    test_count()++;							
    volatile T tt(t);							
    volatile U uu(u);							
    volatile V vv(v);
    typedef typename nt2::meta::upgrade<T>::type TT;
    typedef typename nt2::meta::upgrade<U>::type UU;
    typedef typename boost::common_type<TT, UU>::type R;
    if( nt2::details::ulpdist(tt, uu ) <= (R)vv)
      {									
	std::cout << " * Test `"					
		  << "details::ulpdist(" << x1 << ", " <<  x2 << ") <= " << x3	
		  << "` **passed**."					
		  << " (" << line << ")"				
		  << std::endl;
	return true; 
      }									
    else								
      {									
	std::cout << " * Test `"					
		  << "details::ulpdist(" << x1 << ", " <<  x2 << ") <= " << x3	
		  << "` **failed** in function "			
		  << fn << " (" << line << ")"				
		  << "details::ulpdist(" << TT(tt) << ", " <<  UU(uu) << ") == "		
		  <<  nt2::details::ulpdist(tt, uu )				
		  << std::endl;						
	++error_count();
	return false; 
      }									
  }									

  template<class T, class U, class V>					
  inline bool test_ulp_tuple_eq( char const* x1
			   , char const* x2		
			   , char const* x3				
			   , int line
			   , char const * fn			
			   , T const & t
			   , U const & u			
			   , V const & v				
			   )						
  {									
    test_count()++;							
    volatile T tt(t);							
    volatile U uu(u);							
    volatile V vv(v);
    typedef typename nt2::meta::upgrade<T>::type TT;
    typedef typename nt2::meta::upgrade<U>::type UU;
    bool r =   nt2::details::ulpdist(boost::fusion::at_c<0>(u), boost::fusion::at_c<0>(t)) <= v;
    r &= nt2::details::ulpdist(boost::fusion::at_c<1>(u), boost::fusion::at_c<1>(t)) <= v; 
    if(r)					
      {									
	std::cout << " * Test `"					
		  << "details::ulpdist(" << x1 << ", " <<  x2 << ") <= " << x3	
		  << "` **passed**."					
		  << " (" << line << ")"				
		  << std::endl;
	return true; 
      }									
    else								
      {									
// 	std::cout << " * Test `"					
// 		  << "details::ulpdist(" << x1 << ", " <<  x2 << ") <= " << x3	
// 		  << "` **failed** in function "			
// 		  << fn << " (" << line << ")"				
// 		  << "details::ulpdist(" << TT(t) << ", " <<  UU(u) << ") == "		
// 		  <<  nt2::details::ulpdist(tt, uu )				
// 		  << std::endl;						
	++error_count();
	return false; 
      }									
  }

} }
#endif

