//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DIAG_OF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DIAG_OF_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the diag_of function
**/

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/size.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the diag_of functor
    **/
    struct diag_of_ : ext::elementwise_<diag_of_>
    {
      typedef ext::elementwise_<diag_of_> parent;
    };

    /*!
      @brief Tag for the offset_diag_of functor
    **/
    struct offset_diag_of_ : ext::elementwise_<offset_diag_of_>
    {
      typedef ext::elementwise_<offset_diag_of_>  parent;
    };
   }

  /*!
    @brief Diagonal extraction

    Retrieves the diagonal of an expression. Contrary to diagonal, this
    is an extarction of data and not a simple masking operation.

    @param a0 Expression to process
    @return The diagonal of a0
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::diag_of_       , diag_of, 1)

  /*!
    @brief Diagonal extraction with offset

    Retrieves the kth sub or super-diagonal of an expression. Contrary to band,
    this is an extarction of data and not a simple masking operation.

    @param a0 Expression to process
    @param a1 Diagonal offset
    @return The diagonal of a0
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::offset_diag_of_, diag_of, 2)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::diag_of_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::diag_of_,Domain,N,Expr>
  {
    typedef nt2::_1D result_type;
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type c0_t;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      c0_t a0 = boost::proto::child_c<0>(e);
      return result_type(std::min(nt2::size(a0,1),nt2::size(a0,2)));
    }
  };

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::offset_diag_of_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};

  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::offset_diag_of_,Domain,N,Expr>
  {
    typedef nt2::_1D result_type;
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type c0_t;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      c0_t a0 = boost::proto::child_c<0>(e);
      std::ptrdiff_t w  = nt2::width(a0);
      std::ptrdiff_t h  = nt2::height(a0);
      std::ptrdiff_t m  = boost::proto::child_c<3>(e);

      if(m < -h || m > w) return result_type(0);

      if(h <= w)
      {
        if(m <= 0)        return result_type(h+m);
        else if(m <= w-h) return result_type(h);
      }
      else
      {
        if(m <= w-h)    return result_type(h+m);
        else if(m <= 0) return result_type(w);
      }

      return result_type(w-m);
    }
  };
} }

#endif
