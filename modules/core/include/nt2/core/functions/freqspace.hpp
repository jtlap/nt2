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
#include <nt2/sdk/meta/generative_hierarchy.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

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
  {
    // The size is contained in the first child
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term;
    typedef typename meta::strip<seq_term>::type::extent_type        result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<0>(e).extent();
    }
  };

  template<class Domain, class Expr>
  struct  size_of<tag::freqspace_,Domain,1,Expr>
  {
    // The size is contained in the first child
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term;
    typedef typename meta::strip<seq_term>::type::extent_type        result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<0>(e).extent();
    }
  };

  template<class Domain, int N, class Expr>
  struct  generator<tag::freqspace_,Domain,N,Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&,0>::type seq_term;
    typedef typename boost::dispatch::meta::semantic_of<seq_term>::type sema_t;

    // Rebuild proper expression type with semantic
    typedef expression< typename boost::remove_const<Expr>::type
                      , sema_t
                      >                                     result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      return result_type(e);
    }
  };
} } }

#endif

