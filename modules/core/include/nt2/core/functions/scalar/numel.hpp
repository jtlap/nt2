//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_NUMEL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_NUMEL_HPP_INCLUDED

#include <nt2/core/functions/numel.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/fusion/include/fold.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::numel_, tag::cpu_
                            , (A0), (scalar_< unspecified_<A0> >)
                            )
  {
    typedef boost::mpl::size_t<1> result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0&) const { return result_type(); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::numel_, tag::cpu_
                            , (A0)
                            , (fusion_sequence_<A0>)
                            )
  {
    struct mul_
    {
      template<class Sig> struct result;
      template<class This,class A, class B>
      struct result<This(A,B)>
      {
        typedef typename boost::common_type<A,B>::type  base;
        typedef typename meta::strip<base>::type        type;
      };

      template<class A, class B>
      BOOST_FORCEINLINE typename result<mul_(A const&,B const&)>::type
      operator()(const A& a, const B& b) const
      {
        typedef typename result<mul_(A,B)>::type type;
        return type(a)*type(b);
      }
    };

    typedef typename  boost::fusion::result_of::
                      fold<A0,boost::mpl::size_t<1>,mul_>::type   result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0) const
    {
      return boost::fusion::fold( a0
                                , boost::mpl::size_t<1>()
                                , mul_()
                                );
    }
  };
} }

#endif
