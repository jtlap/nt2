//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_CORE_FUNCTIONS_EXPR_LENGTH_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_LENGTH_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/length.hpp>
#include <nt2/include/functions/max.hpp>
#include <boost/fusion/include/fold.hpp>
#include <nt2/core/container/category.hpp>
#include <nt2/include/functions/extent.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::length_, tag::cpu_
                            , (A0)(T)
                            , ((expr_ < unspecified_<A0>
                                      , nt2::container::domain, T
                                      >
                              ))
                            )
  {
    typedef typename meta::strip<typename A0::extent_type>::type  base;
    typedef typename boost::fusion::result_of::
    fold< base
        , boost::mpl::size_t<1>
        , nt2::functor<tag::max_>
        >::type                                                   result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0) const
    {
      return boost::fusion::fold( a0.extent()
                                , boost::mpl::size_t<1>()
                                , functor<tag::max_>() 
                                );
    }
  };
} }

#endif
