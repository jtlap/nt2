/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_POLYNOMIALS_FUNCTIONS_CONV_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOMIALS_FUNCTIONS_CONV_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/include/functions/numel.hpp>

namespace nt2 {  namespace tag
  {
    struct conv_ :  ext::unspecified_<conv_>
    {
      typedef ext::unspecified_<conv_>  parent;
    };
  }
  
  /**
   * @brief Perform characteristic conv computation 
   *
   * convolves vectors a and b.  the resulting vector is
   * numel max(cons(numel(a)+numel(b)-1,numel(a),numel(b))). if a and b are
   * vectors of polynomial coefficients, convolving them is almost
   * equivalent to multiplying the two polynomials.
   *
   * c = conv(a, b, shape) returns a subsection of the convolution with size
   * specified by shape:
   *   'f'  - (default) returns the 'full' convolution,
   *   's'  - returns the central part of the convolution
   *             that is the 'same' size as a.
   *   'v' - returns only those ('valid') parts of the convolution 
   *             that are computed without the zero-padded edges. 
   *             numel(c) is max(numel(a)-max(0,numel(b)-1),0). 
   **/
  NT2_FUNCTION_IMPLEMENTATION(tag::conv_, conv, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::conv_, conv, 3)
    
}

namespace nt2 { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::conv_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type A0;
    typedef _2D                                             result_type;
    BOOST_FORCEINLINE result_type operator ()(Expr& e) const
    {
      result_type sizee;
      sizee[0] = 1;
      size_t na = nt2::numel(boost::proto::child_c<0>(e));
      size_t nb = nt2::numel(boost::proto::child_c<1>(e));
      sizee[1] = std::max(std::max(na+nb ? na+nb-1u : 0u,na),nb);
      return sizee; 
    }       
  };

  template<class Domain, int N, class Expr>
  struct  value_type<tag::conv_,Domain,N,Expr>
        : meta::value_as<Expr,0>
  {};
} }


#endif
