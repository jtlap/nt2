//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_MODELS_FUNCTION_SIMD_COMMON_MODEL_FOUR_BRANCHES_HPP_INCLUDED
#define NT2_TOOLBOX_MODELS_FUNCTION_SIMD_COMMON_MODEL_FOUR_BRANCHES_HPP_INCLUDED
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/nbtrue.hpp>
#include <nt2/include/functions/bitwise_ornot.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/functions/ceil.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<model_four_branches_,tag::simd_<tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::is_real_convertible<A0>{}; 
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute model_four_branches(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<model_four_branches_,
              tag::simd_<tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (2, (real_,arithmetic_))
    )
    NT2_FUNCTOR_CALL_EVAL_IF(1,       real_)
    {
      //	  std::cout << "      : a0 " << a0 << std::endl; 
      // test1/2/3 are supposed less and less restrictive 
      A0 r =  Nan<A0>(); 
      A0 test1 = is_le(a0, One<A0>()); // any test
      int32_t nb = 0; 
      if ((nb = nbtrue(test1)) > 0)
	{
 	  A0 y1 = case_1<A0>(a0);  // computation result if test1
	  r = b_ornot(y1, test1);
//       	  std::cout << "case_1 : r  " << r << std::endl; 
// 	  std::cout << "nb          " << nb<< std::endl;  
	  if (nb >= meta::cardinal_of<A0>::value) return r; // we are done	  
	}
      A0 test2 = is_le(a0, Two<A0>()); // any test
      A0 test = b_andnot(test2, test1); 
      int32_t nb1 = 0; 
      if ((nb1 = nbtrue(test)) > 0)
	{
	  A0 y2 = case_2<A0>(a0);  // computation result if test2 & ~test1
	  A0 r2 = b_ornot(y2, test);
	  r &= r2; 
//       	  std::cout << "case_2 : r " << r << std::endl; 
// 	  std::cout << "nb          " << nb<< std::endl;  
// 	  std::cout << "nb1         " << nb1<< std::endl;  
	  if ((nb += nb1)>= meta::cardinal_of<A0>::value) return r; // we are done	  
	}
      A0 test3 = is_le(a0, Three<A0>()); // any test
      test = b_andnot(test3, test2); 
      if ((nb1 = nbtrue(test)) > 0)
	{
	  A0 y3 = case_3<A0>(a0);  // computation result if test3 & ~test2
	  A0 r3 = b_ornot(y3, test);
	  r &= r3; 
//       	  std::cout << "case_3 : r  " << r << std::endl;
// 	  std::cout << "nb          " << nb<< std::endl;  
// 	  std::cout << "nb1         " << nb1<< std::endl;  
	  if ((nb += nb1)>= meta::cardinal_of<A0>::value) return r; // we are done	  
	}
      A0 y4 =  case_4<A0>(a0); // computation result in remaining cases
      r = sel(test3, r, y4);
//       std::cout << "case_4 : r  " << r << std::endl;
//       if(any(is_nez(r-ceil(a0))))
// 	{
// 	  std::cout << "a0       " << a0 << std::endl;
// 	  std::cout << "ceil(a0) " << ceil(a0) << std::endl;
// 	  std::cout << "r        " << r  << std::endl;
// 	  exit(1); 
// 	}
      return r|isnan(a0); // we are done
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,       arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      return model_four_branches(tofloat(a0));
    }
  private :
    template < class A0> static inline A0 case_1(const A0& )
    {
      return  One<A0>();
    }
    template < class A0> static inline A0 case_2(const A0& )
    {
      return  Two<A0>();
    }
    template < class A0> static inline A0 case_3(const A0& )
    {
      return  Three<A0>();
    }
    template < class A0> static inline A0 case_4(const A0& )
    {
      return  Four<A0>();
    }
  };
} }

      
#endif
