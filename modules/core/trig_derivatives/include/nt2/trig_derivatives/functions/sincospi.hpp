//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_SINCOSPI_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_SINCOSPI_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/sincospi.hpp>
#include <nt2/include/functions/simd/sincospi.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of sincospi at x
    by sincospi<N>(x)
    @see @funcref{sincospi}
  **/
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sincospi_, sincospi,(A0 const&)(A1 const&)(A2&)(A3&),4)
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sincospi_, sincospi,(A0 const&)(A1 const&)(A2&),3)
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sincospi_, sincospi,(A0 const&)(A1 const&),2)


  template < long N, class T> BOOST_FORCEINLINE void sincospi(const T & x, T & a1, T& a2)
  {
    sincospi(boost::mpl::long_<N>(), x, a1, a2);
  }
  template < long N, class T> BOOST_FORCEINLINE T sincospi(const T & x, T& a2)
  {
    T a1;
    sincospi(boost::mpl::long_<N>(), x, a1, a2);
    return a1;
  }
  template < long N, class T> BOOST_FORCEINLINE std::pair<T, T>  sincospi(const T & x)
  {
    typedef std::pair<T, T>       result_type;
    T a1, a2;
    sincospi(boost::mpl::long_<N>(), x, a1, a2);
    return result_type(a1, a2);
  }
}

#endif

