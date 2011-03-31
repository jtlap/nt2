//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_IMPL_TRIGO_FAST_TRIG_BASE_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_IMPL_TRIGO_FAST_TRIG_BASE_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/simd/tags.hpp>

namespace nt2
{


//   NT2_EXCEPTION_INFO(max_range,double);
//   struct fast_trig_range_exception : public nt2::exception
//   {
//     virtual void display(std::ostream& os) const throw()
//     {
//       double mr = *boost::get_error_info<max_range>(*this)
//       os << "Using a fast trigonometric function outside the range ["
// 	 << -mr <<",  " << mr << "]";
//     }
//   };

  namespace details
  {
    namespace internal
    {
      template < class A0, class unit_tag> struct trig_ranges
      {
	//	static inline A0    max_range() {return Zero<A0>(); }
      }; 
      template < class A0>  struct trig_ranges<A0, radian_tag>
      {
	static inline A0    max_range() {return Pio_4<A0>(); }
	static inline A0    scale()     {return One<A0>(); }
      }; 
      template < class A0>  struct trig_ranges<A0, pi_tag>
      {
	static inline A0    max_range() {return Quarter<A0>(); }
	static inline A0    scale()     {return Pi<A0>(); }
      }; 
      template < class A0>  struct trig_ranges<A0, degree_tag>
      {
	static inline A0    max_range() {return Fortyfive<A0>(); }
	static inline A0    scale()     {return Pio_180<A0>(); }
      }; 



      // This class expose the public static members:
      // cosa     x -> cos(a*x)
      // sina     x -> sin(a*x)
      // tana     x -> tan(a*x)
      // cota     x -> cot(a*x)
      // sincosa  x -> cos(a*x) and sin(a*x)
      // "a" is not a run time parameter !
      // It stands as a remainder that according the Tag it can be considered
      // as a scale factor for the input of values:
      //   1           radian_tag,
      //   pi          pi_tag
      //   pi/180      degree_tag,
      // but the scaling is internal to the algorithm to provide better accuracy
      // and better performance.

      // The range is [-pi/4,  pi/4] for radian_tag
      // The range is [ -1/4,   1/4] for pi_tag
      // The range is [  -45,    45] for degree_tag
      // Outside these ranges the functions return Nan(s)

      // In this file stands the scalar  version 
      // Some definitions are useless but provide facilities of comparaison with
      // the SIMD implementation
      //

      template < class A0,
		 class unit_tag
      > 
      struct trig_base<A0,unit_tag,fast_tag,tag::not_simd_type>
      {
	// for all functions the algorithm is:
	// * evaluations
	// * return evaluation or Nan if range is not respected
	//
	// note that the range is VERY SMALL
	

	typedef trig_evaluation<A0,trig_tag,tag::not_simd_type> eval_t;
	
	static inline A0 cosa(const A0& a0)
	{
	  A0 x =  scale(a0); 
	  if(not_in_range(a0)) return Nan<A0>(); else return eval_t::cos_eval(sqr(x), x, Zero<A0>());
	}

	
	static inline A0 sina(const A0& a0)
	{
	  A0 x =  scale(a0); 
	  if(not_in_range(a0)) return Nan<A0>(); else return eval_t::sin_eval(sqr(x), x, Zero<A0>());
	}

	static inline A0 tana(const A0& a0)
	{
	  A0 x =  scale(a0); 
	  if(not_in_range(a0)) return Nan<A0>(); else return eval_t::base_tan_eval(x);
	}	  
	static inline A0 cota(const  A0& a0)
	{
	  A0 x =  scale(a0); 
	  if(not_in_range(a0)||!(a0)) return Nan<A0>(); else return rec(eval_t::base_tan_eval(x));
	}


	static inline void sincosa(const A0& a0, A0& s, A0& c)
	{
	  if(not_in_range(a0)){c = s = Nan<A0>(); return; }
	  A0 x =  scale(a0);
	  A0 z =  sqr(x); 
	  c = eval_t::cos_eval(z, x, Zero<A0>());
	  s = eval_t::sin_eval(z, x, Zero<A0>());  
	}
      private:
	typedef typename meta::logical<A0>::type                                                          logic; 
        static inline logic not_in_range(const A0& a0){return nt2::abs(a0) > trig_ranges<A0,unit_tag>::max_range(); }
        static inline A0    scale       (const A0& a0){return a0*trig_ranges<A0,unit_tag>::scale();            }
      }; 	
    }
  }
}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of fast_trig_base.hpp
// /////////////////////////////////////////////////////////////////////////////
