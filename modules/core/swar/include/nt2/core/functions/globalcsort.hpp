//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_GLOBALCSORT_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_GLOBALCSORT_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    struct globalcsort_ :  ext::tieable_<globalcsort_>
    {
      typedef ext::tieable_<globalcsort_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
        BOOST_AUTO_DECLTYPE_BODY( dispatching_globalcsort_( ext::adl_helper(),
                                                      static_cast<Args&&>(args)... ) )
     };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::globalcsort_, Site>
    dispatching_globalcsort_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::globalcsort_, Site>();
    }
    template<class... Args>
    struct impl_globalcsort_;
  }

  /**
   * @brief Perform sort using libc++ std::sort from algorithm
   *
   * tie(sa{, index}) = globalcsort(a{, comp}})
   *
   * @param a is the table expression to be globally sorted
   * @param comp is a comparaison function in the same format than std::sort
   *
   * the functor returns the sorted input in its original dimensionnalities
   * and optionaly the indices of the elements in the original input
   *
   * for sorting an array along a dimension use rather csort
   **/

  NT2_FUNCTION_IMPLEMENTATION(tag::globalcsort_, globalcsort, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::globalcsort_, globalcsort, 2)
}

namespace nt2 {
  namespace ext {
    template<class Domain, int N, class Expr>
    struct  size_of<tag::globalcsort_,Domain,N,Expr>
      : meta::size_as<Expr,0>
    {};

} }

#endif
