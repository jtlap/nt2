//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_SINECOSINE_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_SINECOSINE_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/sinecosine.hpp>
#include <nt2/include/functions/simd/sinecosine.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of sinecosine at x
    by sinecosine<N>(x)
    @see @funcref{sinecosine}
  **/
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinecosine_<A0>, sinecosine,(A1 const&)(A2 const&)(A3&)(A4&),5)
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinecosine_<A0>, sinecosine,(A1 const&)(A2 const&)(A3&),4)
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinecosine_<A0>, sinecosine,(A1 const&)(A2 const&),3)

  template <class mode, long N, class T> BOOST_FORCEINLINE void sinecosine(const T & x, T & a1, T& a2)
  {
    sinecosine<mode>(boost::mpl::long_<N>(), x, a1, a2);
  }
  template <class mode, long N, class T> BOOST_FORCEINLINE T sinecosine(const T & x, T& a2)
  {
    T a1;
    sinecosine<mode>(boost::mpl::long_<N>(), x, a1, a2);
    return a1;
  }
  template <class mode, long N, class T> BOOST_FORCEINLINE std::pair<T, T>  sinecosine(const T & x)
  {
    typedef std::pair<T, T>       result_type;
    T a1, a2;
    sinecosine<mode>(boost::mpl::long_<N>(), x, a1, a2);
    return result_type(a1, a2);
  }
}

#endif

