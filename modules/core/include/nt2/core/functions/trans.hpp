//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TRANS_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TRANS_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::trans function
 */

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct trans_ : ext::elementwise_<trans_>
    {
      typedef ext::elementwise_<trans_> parent;
    };
  }

  //============================================================================
  /*!
   * transpose a matrix
   *
   * \param xpr 2D table (must verify is_matrix(a))
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::trans_, trans, 1)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class X>
  struct  size_of<nt2::tag::trans_,Domain,1,X>
  {
    typedef _2D result_type;

    BOOST_FORCEINLINE result_type operator()(X& e) const
    {
      //BOOST_ASSERT(ndims(boost::proto::child_c<0>(e)) <= 2);
      return _2D( boost::proto::child_c<0>(e).extent()[1]
                , boost::proto::child_c<0>(e).extent()[0]
                );
    }
  };

  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::trans_,Domain,N,Expr>
  {
    typedef typename meta::scalar_of< typename  boost::proto::result_of::
                                                child_c<Expr&,0>::type
                                    >::type                             base_t;
    typedef typename meta::strip<base_t>::type                          type;
  };
} } }
#endif
