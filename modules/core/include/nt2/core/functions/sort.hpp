//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SORT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SORT_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/generator.hpp>
#include <nt2/sdk/meta/tieable_hierarchy.hpp>

/*!
 * \ingroup core
 * \defgroup core sort
 *
 * \par Description
 * sorting sort(a0, n))
 * by default n is the first non-singleton dimension of a0
 *
 *
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sort.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::sort_(A0)>::type
 *     sort(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of sort
 *
 * \return always a scalar value
 *
 * \par Notes
 * \par
 * This is a reduction operation. As such it has not real interest outside
 * SIMD mode.
 * \par
 * Such an operation always has a scalar result which translate a property
 * of the whole SIMD vector.
 * \par
 * If usable and used in scalar mode, it reduces to the operation as acting
 * on a one element vector.
 *
**/


namespace nt2
{
  namespace tag
  {
    struct sort_ :  ext::tieable_<sort_>
    {
      typedef ext::tieable_<sort_>  parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sort_       , sort, 1)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sort_       , sort, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sort_       , sort, 3)

}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, int N, class Expr>
  struct  size_of<tag::sort_,Domain,N,Expr>
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
  struct  size_of<tag::sort_,Domain,1,Expr>
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
  struct  generator<tag::sort_,Domain,N,Expr>
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
