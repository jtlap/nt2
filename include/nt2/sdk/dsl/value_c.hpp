/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_VALUE_C_HPP_INCLUDED
#define NT2_SDK_DSL_VALUE_C_HPP_INCLUDED

#include <boost/proto/transform.hpp>

namespace nt2 { namespace meta
{
  template<std::size_t N>
  struct value_c
  {
    template<class Sig> struct result;

    template<class This,class X>
    struct  result<This(X)>
    {
      typedef typename boost::result_of<boost::proto::_child_c<N>(X)>::type base;
      typedef typename boost::result_of<boost::proto::_value(base)>::type   type;
    };

    template<class X> inline typename result<value_c(X)>::type
    operator()( X& x ) const
    {
      return  boost::proto::value(boost::proto::child_c<0>(x));
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Register value_c<N> as a proto callable transform
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace proto
{
  template<std::size_t N>
  struct is_callable<nt2::meta::value_c<N> > : mpl::true_ {};
} }

#endif
