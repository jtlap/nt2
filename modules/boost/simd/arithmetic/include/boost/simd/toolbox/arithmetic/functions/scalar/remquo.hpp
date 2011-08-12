//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_REMQUO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SCALAR_REMQUO_HPP_INCLUDED
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/simd/include/functions/remainder.hpp>
#include <boost/simd/include/functions/idivround.hpp>

// namespace boost { namespace simd { namespace details
// {
//   template <class T,class Dummy> struct remquo;
  
//   template <class Dummy> struct remquo<double,Dummy>{
//     typedef double                                          rem; 
//     typedef typename dispatch::meta::as_integer<double,signed>::type  quo;
//     typedef boost::fusion::tuple<rem,quo>                 rtype;
    
//     static inline rtype eval(const double& a0, const double& a1)
//     {
//       rtype res;
//       int rt; 
//       boost::fusion::at_c<0>(res) = ::remquo(a0, a1, &rt);
//       boost::fusion::at_c<1>(res) = rt;
//       return res; 
//     }
//   }; 
    
//   template <class Dummy> struct remquo<float,Dummy>{
//     typedef float                                           rem; 
//     typedef typename dispatch::meta::as_integer<float,signed>::type  quo;
//     typedef boost::fusion::tuple<rem,quo>                 rtype;
    
//     static inline rtype eval(const float& a0, const float& a1)
//     {
//       rtype res;
//       int rt; 
//       boost::fusion::at_c<0>(res) = ::remquof(a0, a1, &rt);
//       boost::fusion::at_c<1>(res) = rt;
//       return res; 
//     }
//   }; 
// } } }

/////////////////////////////////////////////////////////////////////////////
// Implementation when A0 and A1 types are fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::remquo_, tag::cpu_,
			     (A0)(A1),
			     (scalar_ < real_<A0> > )
			     (scalar_ < real_<A1> > )
			     )
  {
    typedef typename boost::dispatch::meta::result_of<boost::dispatch::meta::floating(A0,A1)>::type ftype;
    typedef typename dispatch::meta::as_integer<ftype,signed>::type           quo;
    typedef boost::fusion::tuple<ftype,quo>                 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      result_type res;
      boost::simd::remquo(a0, a1, boost::fusion::at_c<0>(res), boost::fusion::at_c<1>(res));
      return res; 
    }
    
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::remquo_, tag::cpu_,
			     (A0)(A1)(A2)(A3),
			     (scalar_ < arithmetic_<A0> > )
			     (scalar_ < arithmetic_<A1> > )
			     (scalar_ < real_<A2> > )
			     (scalar_ < arithmetic_<A3> > )
			     )
  {
    typedef boost::simd::int32_t result_type;
    inline result_type operator()(A0 const& a0,const A1 & a1,A2 & a2,A3 & a3) const
    {
      a2 = boost::simd::remainder(A2(a0), A2(a1));
      a3 = boost::simd::idivround(A2(a0), A2(a1));
      return 0;
    }
  };
} } }

#endif
