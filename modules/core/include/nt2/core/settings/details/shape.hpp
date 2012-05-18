//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_DETAILS_SHAPE_HPP_INCLUDED
#define NT2_CORE_SETTINGS_DETAILS_SHAPE_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/buffer.hpp>
#include <boost/fusion/include/size.hpp>
#include <nt2/include/functions/sub2ind.hpp>
#include <nt2/core/functions/scalar/numel.hpp>

namespace nt2
{
  //============================================================================
  // rectangular_ shape
  //============================================================================
  struct rectangular_
  {
    //==========================================================================
    // rectangular_ just use the buffer we asked for
    //==========================================================================
    template<class T, class S> struct apply
    {
      typedef typename meta::option<S,tag::buffer_>::type   buffer_t;
      typedef typename buffer_t::template apply<T,S>::type  type;
    };

    //==========================================================================
    // a rectangular [D0 ... D1] container has Prod(Di) element
    //==========================================================================
    template<class S> static BOOST_FORCEINLINE
    std::size_t nnz(S const& sz) { return nt2::numel(sz); }

    //==========================================================================
    // a rectangular container access its element without any special case
    //==========================================================================
    template<class P, class S> static
    BOOST_FORCEINLINE std::size_t linearize(P const& p,S const& s)
    {
      typedef typename boost::mpl::
              apply < typename P::storage_type
                    , boost::mpl::size_t<S::static_size>
                    , boost::mpl::size_t<0U>
                    >::type                     dim_t;

      return  nt2::sub2ind(s,p)
            - boost::mpl::at_c<typename P::index_type,dim_t::value>::type::value;
    }
  };
}

#endif
