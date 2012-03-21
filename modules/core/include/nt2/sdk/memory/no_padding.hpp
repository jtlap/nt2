//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_NO_PADDING_HPP_INCLUDED
#define NT2_SDK_MEMORY_NO_PADDING_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <boost/dispatch/meta/as_ref.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  /*!
   * no_padding is a padding strategy that align nothing.
   */
  //============================================================================
  struct no_padding
  {
    typedef boost::mpl::false_ padding_status;

    template<class Target> struct apply
    {
      struct type
      {
        template<class Sig> struct result;
        template<class This, class V, class N>
        struct result<This(V,N)> : boost::dispatch::meta::as_ref<V> {};

        template<class V,class N>
        typename result<no_padding(V const&, N const&)>::type
        operator()(V const& v, N const&) const
        {
          return v;
        }
      };
    };
  };
} }

#endif
