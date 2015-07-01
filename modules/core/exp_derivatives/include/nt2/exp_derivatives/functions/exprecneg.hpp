//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_EXPRECNEG_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_EXPRECNEG_HPP_INCLUDED
#include <nt2/exponential/include/functions/exprecneg.hpp>
#include <nt2/include/functions/simd/exprecneg.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of exprecneg at x
    by exprecneg<N>(x)
    @see @funcref{exprecneg}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::exprecneg_, exprecneg, 2)


  template < long N, class T> BOOST_FORCEINLINE T exprecneg(const T & x)
  {
    return exprecneg(boost::mpl::long_<N>(), x);
  }

}

#endif

