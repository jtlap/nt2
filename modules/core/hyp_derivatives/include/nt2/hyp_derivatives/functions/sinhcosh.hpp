//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_SINHCOSH_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_SINHCOSH_HPP_INCLUDED
#include <nt2/hyperbolic/include/functions/sinhcosh.hpp>
#include <nt2/include/functions/simd/sinhcosh.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of sinhcosh at x
    by sincosh<N>(x)
    @see @funcref{sincosh}
  **/
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinhcosh_, sincosh,(A0 const&)(A1 const&)(A2&)(A3&),4)
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinhcosh_, sincosh,(A0 const&)(A1 const&)(A2&),3)
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinhcosh_, sincosh,(A0 const&)(A1 const&),2)


  template < long N, class T0,  class T1,  class T2 > BOOST_FORCEINLINE
  void sinhcosh(const T0 & x, T1 & a1, T2& a2)
  {
    a1 = nt2::sinhcosh(boost::mpl::long_<N>(), x, a2);
  }
  template < long N, class T0,  class T1> BOOST_FORCEINLINE
  T1 sinhcosh(const T0 & x, T1& a2)
  {
    T1 a1;
    nt2::sinhcosh(boost::mpl::long_<N>(), x, a1, a2);
    return a1;
  }
  template < long N, class T> BOOST_FORCEINLINE std::pair<T, T>  sinhcosh(const T & x)
  {
    typedef std::pair<T, T>       result_type;
    T a1, a2;
    nt2::sinhcosh(boost::mpl::long_<N>(), x, a1, a2);
    return result_type(a1, a2);
  }
}

#endif

