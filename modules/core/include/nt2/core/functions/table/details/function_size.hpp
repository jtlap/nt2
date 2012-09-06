//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_DETAILS_FUNCTION_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_DETAILS_FUNCTION_SIZE_HPP_INCLUDED

#include <nt2/core/functions/function.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <nt2/core/functions/table/details/make_size.hpp>

namespace nt2 { namespace container { namespace ext
{
  //============================================================================
  // Size of a function call node is depends of the indexers
  //============================================================================
  template<class Expr, class Domain, int N>
  struct size_of<tag::function_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of
                          ::child_c<Expr&, 0>::type           referee;
    typedef typename meta::strip<referee>::type::indexes_type indexes_type;

    typedef typename boost::proto::result_of
                          ::child_c<Expr&, 1>::type           indices;

    typedef typename boost::proto::result_of
                          ::child_c<Expr&, 2>::type           reldims;

    typedef typename boost::proto::result_of
                          ::value<reldims>::type              dims;

    typedef details::make_size< meta::strip<dims>::type::static_size
                              , Domain
                              , referee
                              , dims
                              , indexes_type, indices
                              >                                   impl;
    typedef typename impl::result_type                            result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type operator()(Expr& e) const
    {
      return impl() ( boost::proto::child_c<0>(e)
                    , boost::proto::value(boost::proto::child_c<2>(e))
                    , boost::proto::child_c<0>(e).indexes()
                    , boost::proto::child_c<1>(e)
                    );
    }
  };

  //==========================================================================
  // Size_of nullary function call case - handle expr()
  //==========================================================================
  template<class Expr, class Domain>
  struct size_of<tag::function_, Domain, 1, Expr> : size_as<Expr,0> {};
} } }

#endif
