//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_WILKINSON_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_WILKINSON_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/boxed_size.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

/*!
 * \ingroup algebra
 * \defgroup algebra_wilkinson wilkinson
 *
 * \par Description
 *   wilkinson(n) is the inverse of the n by n matrix with elements
 *   1/(i+j-1), which is a famous example of a badly conditioned
 *   matrix.  the result is exact for  n  less than about 15.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/wilkinson.hpp>
 * \endcode
 *
 *
 * \param n order of the matrix output
 *
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag wilkinson_ of functor wilkinson
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct wilkinson_ : ext::unspecified_<wilkinson_>
    {
      typedef ext::unspecified_<wilkinson_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_wilkinson_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::wilkinson_, Site> dispatching_wilkinson_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::wilkinson_, Site>();
    }
    template<class... Args>
    struct impl_wilkinson_;
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::wilkinson_, wilkinson, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::wilkinson_, wilkinson, 2)

  template<typename T, typename A0>
  typename  boost::dispatch
          ::meta::call<tag::wilkinson_( A0 const&, meta::as_<T> const&)>::type
  wilkinson(A0 const& n)
  {
    return nt2::wilkinson(n, meta::as_<T>());
  }
}

namespace nt2 { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::wilkinson_, Domain, N, Expr>
        : meta::boxed_size<Expr,1>
  {};

  template <class Domain, class Expr,  int N>
  struct value_type < tag::wilkinson_, Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type c0_t;
    typedef typename boost::proto::result_of::value<c0_t>::value_type       v_t;
    typedef typename v_t::type                                             type;
  };
} }

#endif
