//==============================================================================
//         Copyright 2015          J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_BINEAREST_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_BINEAREST_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/include/functions/dec.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/inc.hpp>
#include <nt2/include/functions/pow2.hpp>
#include <nt2/include/functions/width.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief binearest generic tag

     Represents the binearest function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct binearest_ : ext::unspecified_<binearest_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<binearest_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_binearest_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
   template<class Site>
   BOOST_FORCEINLINE generic_dispatcher<tag::binearest_, Site> dispatching_binearest_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
   {
     return generic_dispatcher<tag::binearest_, Site>();
   }
   template<class... Args>
   struct impl_binearest_;
  }
  /*!
    one dimensional binearest interpolation
    \par

    @par Semantic:

    For every parameters expressions

    @code
    auto r = binearest (x, y, z, xi, yi)
    auto r = binearest (z, xi, yi)
    auto r = binearest (z{, n])
    auto r = binearest (z, xi, yi, extrapval)
    auto r = binearest (x, y, z, xi, yi, extrapval)
    @endcode

     Two-dimensional interpolation return the nearest neighbor.
     x, y and z describe a surface
     if x and y are vectors their length must correspond
     to the size of z.  x and y must be monotonic.  if they are matrices
     they must have the 'meshgrid' format.

     binearest (x, y, z, xi, yi, ...)
     returns a matrix corresponding to the points described by the
     matrices xi, yi.

     binearest (z, xi, yi)
     assumes x = 1:height(z) and y = 1:width(z)

     binearest (z, n)
     interleaves the matrix z n-times.  if n is omitted a value of
     n = 1 is assumed.

     search the xi and yi, locations i  in x and y and return  z(i, j)
     choosing the ones that realize the smallest distance of (xi, yi) to (x, y)
     if x is  in the interval [x(1), x(end_)]
     and y is  in the interval [y(1), y(end_)]
     else depending on extrap value:

      - nan if extrap is missing or false
      - extrapolation if extrap is true.
      - value of extrap if the type of extrap is a scalar of
        the z element type

    @param x
    @param y
    @param z
    @param xi
    @param yi
    @param extrap

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::binearest_, binearest, 6)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::binearest_, binearest, 5)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::binearest_, binearest, 4)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::binearest_, binearest, 3)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::binearest_, binearest, 2)
  /// @overload
  NT2_FUNCTION_IMPLEMENTATION(tag::binearest_, binearest, 1)
  /// @overload

}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct  size_of<tag::binearest_, Domain, 1, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee;
      size_t h = height((boost::proto::child_c<0>(e)));
      size_t w = width ((boost::proto::child_c<0>(e)));
      sizee[0] = 2*h-1;
      sizee[1] = 2*w-1;
      return sizee;
    }
  };
  /// INTERNAL ONLY
  template<class Domain, class Expr>
  struct  size_of<tag::binearest_, Domain, 2, Expr>
  {
    typedef _2D                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee;
      size_t h = dec(height((boost::proto::child_c<0>(e))));
      size_t w = dec(width ((boost::proto::child_c<0>(e))));
      size_t p =  pow2(boost::proto::child_c<1>(e));
      sizee[0] = inc(h*p);
      sizee[1] = inc(w*p);
      return sizee;
    }
  };
  /// INTERNAL ONLY
  template<class Domain, class Expr,  int N>
  struct  size_of<tag::binearest_, Domain, N, Expr>
  {
    typedef _2D                               result_type;
    typedef boost::mpl::long_ < N <= 4 ? 1 : 3>         I;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type sizee;
      size_t hxi = height((boost::proto::child_c<I::value>(e)));
      size_t wxi = width ((boost::proto::child_c<I::value>(e)));
      size_t hyi = height((boost::proto::child_c<I::value+1>(e)));
      size_t wyi = width ((boost::proto::child_c<I::value+1>(e)));
      if( boost::proto::child_c<I::value>(e).extent() ==
          boost::proto::child_c<I::value+1>(e).extent())
      {
        sizee = boost::proto::child_c<1>(e).extent();
      }
      else if((hxi == 1u && wyi == 1u) || (wxi == 1u && hyi == 1u))
      {
        sizee =  of_size(length(boost::proto::child_c<I::value+1>(e)),
                         length(boost::proto::child_c<I::value>(e)));
      }
      else
      {
        BOOST_ASSERT_MSG(false, "inputs sizes do not match");
      }
      return sizee;
    }
  };
} }
#endif
