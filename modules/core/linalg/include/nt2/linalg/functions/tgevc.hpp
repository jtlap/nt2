//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_TGEVC_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_TGEVC_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements tgevc function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Defines trf function tag
    struct tgevc_ : ext::abstract_<tgevc_>
    {
      /// INTERNAL ONLY
      typedef ext::abstract_<tgevc_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_tgevc_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::tgevc_, Site> dispatching_tgevc_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::tgevc_, Site>();
    }
    template<class... Args>
    struct impl_tgevc_;
  }

  /*!
    @brief

    @param
    @param

    @return
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL (tag::tgevc_, tgevc
                                  , (const A0&)(const A1&)(A2&)(A3&)(A4&)(A5&)
                                  , 6
                                  );
}

#endif
