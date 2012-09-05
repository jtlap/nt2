/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_TOTO_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_TOTO_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {         
     struct toto_ : ext::unspecified_<toto_> { typedef ext::unspecified_<toto_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::toto_, toto, 2)  
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr>
  struct size_of<tag::toto_, Domain, 2, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 1>::value_type child0;
    typedef typename child0::extent_type                               result_type; 

    result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<1>(e).extent();
    }
  };

 template <class Domain, class Expr, int N>
 struct value_type < tag::toto_, Domain,N,Expr> {
   typedef typename boost::proto::result_of::child_c<Expr&, 1>::value_type  child0;
   typedef typename nt2::meta::scalar_of<child0>::type                    elt_type;
   typedef typename nt2::meta::strip<elt_type>::type                          type;
 }; 
} } }
#endif

// /////////////////////////////////////////////////////////////////////////////
// End of toto.hpp
// /////////////////////////////////////////////////////////////////////////////
