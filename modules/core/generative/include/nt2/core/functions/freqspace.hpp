//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FREQSPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FREQSPACE_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the freqspace function
**/

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/boxed_size.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the freqspace functor
    **/
    struct freqspace_ : ext::tieable_<freqspace_>
    {
      typedef ext::tieable_<freqspace_> parent;
    };
  }

  /*!
    @brief Frequency spacing for frequency responses.

    f =  freqspace(n, whole_, as<T>())
    f =  freqspace(n, as<T>())

    f = freqspace(n, as<T>()) returns the 1-d frequency vector f assuming n
                              equally spaced points around the unit circle.
                              f = _(0, 2/n, 1).
   f = freqspace(n, whole_, as<T>()) returns all n equally spaced points.
                                 In this case, f = _(0, 2/n, 2*(n-1)/n).
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace_, freqspace, 3)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace_, freqspace, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::freqspace_, freqspace, 1)
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::freqspace_,Domain,N,Expr>
        : meta::boxed_size<Expr,0>
  {};

  template<class Domain, int N, class Expr>
  struct  value_type<tag::freqspace_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,2>::value_type  c_t;
    typedef typename boost::proto::result_of::value<c_t>::value_type        t_t;
    typedef typename t_t::type                                              type;
  };
} }

#endif
