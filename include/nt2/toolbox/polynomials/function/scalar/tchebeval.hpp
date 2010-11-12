//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SCALAR_TCHEBEVAL_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SCALAR_TCHEBEVAL_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/toolbox/polynomials/category.hpp>

//#include <boost/array.hpp>
// #include <nt2/sdk/meta/irrelevant.hpp>
// namespace nt2 { namespace details
// {
//   template<class T,std::size_t N> 
//   struct category_of_impl<boost::array<T,N>,false>
//   {
//     typedef tag::irrelevant type;
//   };
// } }
// namespace nt2 { namespace meta {
//   template<class Info, class A0,class A1>
//   struct  categorize<functors::tchebeval_,Info,A0,A1>
//   {
//     typedef typename meta::category_of<A0>::type::tag type;
//   };  
// } }
namespace nt2 { namespace functors
{
  template<class Info>
  struct validate<tchebeval_,tag::scalar_(tag::arithmetic_),Info>
  {
    typedef boost::mpl::true_ result_type;
  };

  /////////////////////////////////////////////////////////////////////////////
  // Compute tchebeval(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<tchebeval_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      A0,
      (2, (real_, arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,  real_)
    {
      typename A1::const_iterator p = a1.begin();
      A0 b0 = *p++;
      A0 b1 =  Zero<A0>();
      A0 b2; 
      while (p != a1.end())
	{ 
	  b2 = -b1;
	  b1 = b0;
	  b0 = fma(a0, b1, b2)  + *p++;
	}
      return average(b0, b2); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type; 
      return tchebeval(type(a0), a1); 
    }

  };
} }


      
#endif
