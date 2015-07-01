//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_EXPRECNEGC_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_EXPRECNEGC_HPP_INCLUDED
#include <nt2/exponential/include/functions/exprecnegc.hpp>
#include <nt2/include/functions/simd/exprecnegc.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of exprecnegc at x
    by exprecnegc<N>(x)
    @see @funcref{exprecnegc}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::exprecnegc_, exprecnegc, 2)


  template < long N, class T> BOOST_FORCEINLINE T exprecnegc(const T & x)
  {
    return exprecnegc(boost::mpl::long_<N>(), x);
  }

}

#endif

