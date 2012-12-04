//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_POLYNOM_FUNCTIONS_RATFRACDER_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOM_FUNCTIONS_RATFRACDER_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/boxed_size.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

/**
 * @brief Perform polynomial/or rational fraction derivative
 *
 *   ratfracder(p) returns the derivative of the polynomial whose
 *   coefficients are the elements of vector p.
 *
 *   ratfracder(a,b) returns the derivative of rational fraction. a/b.
 *
 *   [n,d] = ratfracder(a, b) returns the derivative of the
 *   polynomial ratio a/b, represented as n/d.
 *
 **/
namespace nt2 { namespace tag
  {
    struct ratfracder_ : ext::tieable_<ratfracder_> { typedef ext::tieable_<ratfracder_> parent; };
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::ratfracder_, ratfracder, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::ratfracder_, ratfracder, 2)
}

 namespace nt2 { namespace ext
{
  template<class Domain, class Expr>
  struct  size_of<tag::ratfracder_,Domain,1,Expr>
  {
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      _2D sizee;
      sizee[0] = 1;
      size_t na = nt2::numel(boost::proto::value(boost::proto::child_c<0>(e)));
      sizee[1] = na ? na-1u :0; ;
      return sizee;
    }
  };
  template<class Domain, class Expr>
  struct  size_of<tag::ratfracder_,Domain,2,Expr>
  {
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      _2D sizee;
      sizee[0] = 1;
      size_t na = nt2::numel(boost::proto::value(boost::proto::child_c<0>(e)));
      size_t nb = nt2::numel(boost::proto::value(boost::proto::child_c<1>(e)));
      sizee[1] = std::max(std::max(na+nb ? na+nb-1u : 0u,na),nb);
      sizee[1] = sizee[1] ? sizee[1]-1u : 0;
      return sizee;
    }
  };

  template<class Domain, int N, class Expr>
  struct  value_type<tag::ratfracder_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }
#endif
