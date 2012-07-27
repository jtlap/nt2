//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FREQSPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FREQSPACE_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/core/container/dsl/details/generate_as.hpp>

/*!
 * \ingroup core
 * \defgroup core_freqspace freqspace
 *
 * \par Description
 * Frequency spacing for frequency response. 1D case
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/freqspace.hpp>
 * \endcode
 *
 *   f =  freqspace(n, whole_, as<T>())
 *   f =  freqspace(n, as<T>())
 *
 *   f = freqspace(n, as<T>()) returns the 1-d frequency vector f assuming n
 *                              equally spaced points around the unit circle.
 *                              f = _(0, 2/n, 1).
 *   f = freqspace(n, whole_, as<T>()) returns all n equally spaced points.
 *                                 In this case, f = _(0, 2/n, 2*(n-1)/n).
 *
 * T can be any floating type
**/

namespace nt2
{
  namespace tag
  {
    struct freqspace_ : ext::tieable_<freqspace_>
    {
      typedef ext::tieable_<freqspace_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace_, freqspace, 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace_, freqspace, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace_, freqspace, 1)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::freqspace_,Domain,N,Expr>
        : boxed_size_of<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  generator<tag::freqspace_,Domain,N,Expr>
        : generate_as_target< Expr
                            , memory::container
                              < boost::mpl::_
                              , typename boxed_size_of<Expr,0>::result_type
                              >
                            , 2
                            >
  {};
} } }

#endif
