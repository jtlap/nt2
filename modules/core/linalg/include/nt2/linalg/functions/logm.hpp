//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LOGM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LOGM_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>
#include <nt2/core/container/dsl/value_type.hpp>

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag logm_ of functor logm
     *        in namespace nt2::tag for toolbox algebra
    **/
    struct logm_ :   ext::tieable_<logm_>
    {
      typedef ext::tieable_<logm_>  parent;
    };
  }
  /**
   * @brief compute natural principla logarithm of a matricial expression
   *
   * logm(a0) must not be confused with log(a0) that computes on an
   * elementwise basis the logarithms of the elements of matrix a0.
   *
   * a0  can be a any square matricial expression whose
   * eigenvalues have strictly positive real parts
   *
   * @param  a0  Matrix expression or scalar
   *
   * @return a matrix containing logm(a1)
   **/


  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logm_, logm, 1)

}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::logm_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::value_type  c0_t;
    typedef typename c0_t::extent_type                               result_type;
    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      BOOST_ASSERT_MSG(issquare(boost::proto::child_c<0>(e)),
                       "logm needs a square matrix expression");

      return nt2::extent(boost::proto::child_c<0>(e));
    }
  };

  template<class Domain, int N, class Expr>
  struct  value_type<tag::logm_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }
#endif

