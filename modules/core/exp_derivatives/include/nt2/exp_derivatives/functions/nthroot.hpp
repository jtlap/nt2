//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_NTHROOT_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_NTHROOT_HPP_INCLUDED
#include <nt2/exponential/include/functions/nthroot.hpp>
#include <nt2/include/functions/simd/nthroot.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of nthroot at x
    by nthroot<N>(x, n)
    @see @funcref{nthroot}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::nthroot_, nthroot, 3)


  template < long N, class T, class NN> BOOST_FORCEINLINE T nthroot(const T & x, const NN & n)
  {
    return nthroot(boost::mpl::long_<N>(), x, n);
  }

}

#endif

