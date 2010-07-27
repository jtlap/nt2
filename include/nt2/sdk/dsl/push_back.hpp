/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_PUSH_BACK_HPP_INCLUDED
#define NT2_SDK_DSL_PUSH_BACK_HPP_INCLUDED

#include <boost/proto/transform.hpp>
#include <boost/fusion/include/push_back.hpp>

namespace nt2 { namespace meta
{
  struct push_back : boost::proto::callable
  {
    template<class Sig> struct result;

    template<class This, class Seq, class Elem>
    struct result<This(Seq, Elem)>
      : boost::fusion::result_of::push_back<
            typename boost::remove_reference<Seq>::type const
          , typename boost::remove_reference<Elem>::type
        >
    {};

    template<class Seq, class Elem>
    typename result<push_back(Seq, Elem)>::type
    operator()(Seq const& s, Elem const& e) const
    {
      return boost::fusion::push_back(s,e);
    }
  };
} }

#endif
