//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_HGEQZ_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_HGEQZ_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements hgeqz function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines trf function tag
    struct hgeqz_ : ext::abstract_<hgeqz_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<hgeqz_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_hgeqz_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::hgeqz_, Site> dispatching_hgeqz_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::hgeqz_, Site>();
    }
    template<class... Args>
    struct impl_hgeqz_;
  }

  /*!
    @brief

    @param
    @param

    @return
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::hgeqz_, hgeqz
                                  , (const A0&)(const A1&)(const A2&)(const A3&)(const A4&)(A5&)(A6&)(A7&)(A8&)(A9&)(A10&)
                                  , 11
                                  );
}

#endif
