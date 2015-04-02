//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_CSORT_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_CSORT_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2
{
  namespace tag
  {
    struct csort_ :  ext::tieable_<csort_>
    {
      typedef ext::tieable_<csort_>  parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
        BOOST_AUTO_DECLTYPE_BODY( dispatching_csort_( ext::adl_helper(),
                                                      static_cast<Args&&>(args)... ) )
     };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::csort_, Site>
    dispatching_csort_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::csort_, Site>();
    }
    template<class... Args>
    struct impl_csort_;
  }

  /**
   * @brief Perform sort using libc++ std::sort from algorithm
   *
   * tie(sa{, index}) = csort(a{, dim }{, comp}})
   *
   * @param a is the table expression to be sorted
   * @param dim is the dimension along with the table is sorted
   * @param comp is a comparaison function in the same format than std::sort
   *
   * the functor returns the sorted input and optionaly
   * the indices of the elements in the original input
   *
   * for sorting a vector use rather globalcsort
   **/

  NT2_FUNCTION_IMPLEMENTATION(tag::csort_, csort, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::csort_, csort, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::csort_, csort, 3)

}

namespace nt2 {
  namespace ext {
    template<class Domain, int N, class Expr>
    struct  size_of<tag::csort_,Domain,N,Expr>
      : meta::size_as<Expr,0>
    {};

} }

#endif
