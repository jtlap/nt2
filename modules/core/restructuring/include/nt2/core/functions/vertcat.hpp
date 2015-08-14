//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_VERTCAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_VERTCAT_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
   /*!
     @brief vertcat generic tag

     Represents the vertcat function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct  vertcat_ : ext::abstract_<vertcat_>
    {
      typedef ext::abstract_<vertcat_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_vertcat_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::vertcat_, Site> dispatching_vertcat_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::vertcat_, Site>();
   }
   template<class... Args>
   struct impl_vertcat_;
  }
  /*!
    Vertical concatenation

    @par Semantic:

    For every  table expressions:

    @code
    auto r = vertcat(a0, a1, ... an);
    @endcode

    is similar to:

    @code
    auto r = cat(2, a0, a1, ... an);
    @endcode

    @see @funcref{horzcat}, @funcref{cat}

    @par alias: @c catv
    @param a0
    @param a1
    ...
    @param an

    @return an expression which eventually will evaluate to the result
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::vertcat_, vertcat, 2)
  /// INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::vertcat_, vertcat, 1)
  /// INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::vertcat_, catv, 1)
  /// INTERNAL ONLY
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::vertcat_, catv, 2)

  template <class T, class... Args >
  auto horzcat(const T & f, const Args&... args)
    -> decltype(cat(1, f, cat(1, args...)))
  {
    return cat(1, f, cat(1, args...));
  }


  template <class T, class... Args > auto catv(const T & f, const Args&... args)
    -> nt2::table <typename T::value_type>
  {
    return vertcat(f, args...);
  }

}

#endif
