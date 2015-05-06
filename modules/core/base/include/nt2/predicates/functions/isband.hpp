//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_ISBAND_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_ISBAND_HPP_INCLUDED

/*!
  @file
  @brief Defines the isband function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct isband_ : ext::abstract_<isband_>
    {
      typedef ext::abstract_<isband_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY(
        dispatching_isband_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::isband_, Site>
    dispatching_isband_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::isband_, Site>();
    }
    template<class... Args>
    struct impl_isband_;
  }

  /*!
    @brief Test for band status with bounds

    isband(a0, lower,  upper)

    Returns @c true iff a0 is a band matrix between lower and upper, which
    means every elements outside this band a0 are 0.

    @param  a0 The expression to test
    @param  lower  lower band value
    @param  upper  upper band value
    @return a boolean value indicating the  status of a0

    @see @funcref{bandidth}, @funcref{band}
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isband_, isband, 3)
}

#endif
