//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_SDK_SIMD_PACK_META_RETARGET_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_META_RETARGET_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <boost/proto/proto.hpp>
#include <boost/dispatch/dsl/terminal_of.hpp>

namespace boost { namespace simd { namespace meta
{
  struct retarget : boost::proto::callable
  {
    template<class Sig> struct result;

    template<class This, class Expr>
    struct result<This(Expr)>
    {
      typedef boost::dispatch::meta::terminal_of<Expr> base_type;
      typedef typename boost::mpl::apply<base_type,void>::type pack_type;
      typedef boost::dispatch::meta::as_< typename pack_type::data_type::parent > type;
    };

    template<class Expr> inline
    typename result<retarget(Expr&)>::type
    operator()(Expr& ) const
    {
      return typename result<retarget(Expr&)>::type();
    }
  };
} } }

#endif
