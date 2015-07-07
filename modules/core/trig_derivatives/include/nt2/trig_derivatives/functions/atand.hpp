//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_ATAND_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_ATAND_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/atand.hpp>
#include <nt2/include/functions/simd/atand.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of atand at x
    by atand<N>(x)
    @see @funcref{atand}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::atand_, atand, 2)


  template < long N, class T> BOOST_FORCEINLINE T atand(const T & x)
  {
    return atand(boost::mpl::long_<N>(), x);
  }

}

#endif

