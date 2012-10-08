//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_ARECATCOMPATIBLE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_ARECATCOMPATIBLE_HPP_INCLUDED

#include <nt2/core/functions/arecatcompatible.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/isrow.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/isvectoralong.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::arecatcompatible_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_<A0>)
                              (ast_<A1>)
                              (scalar_<integer_<A2> >)
                              )
  {
    typedef bool result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0, const A1& a1, const A2& dim) const
    {
      typedef typename meta::call<tag::extent_(A0 const&)>::type ext1_t;
      ext1_t ex1 = nt2::extent(a0);

      typedef typename meta::call<tag::extent_(A1 const&)>::type ext2_t;
      ext2_t ex2 = nt2::extent(a1);

      if (isempty(a0) || isempty(a1)) return true;

      size_t sz =  nt2::min(ex1.size(), ex2.size());
      size_t d = dim-1;

      for(size_t i=0; i < sz; ++i)
      {
        if ((i != d) && (ex1.data()[i]!= ex2.data()[i])) return false;
      }

      for(size_t i=sz; i < ex1.size(); ++i)
      {
        if (ex1[i]!= 1) return false;
      }

      for(size_t i=sz; i < ex2.size(); ++i)
      {
        if (ex2[i]!= 1) return false;
      }
      return true;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::arecatcompatible_, tag::cpu_
                              , (A0)(A1)(A2)
                            , (scalar_<fundamental_<A0> >)
                              (scalar_<fundamental_<A1> >)
                              (scalar_<integer_<A2> >)
                              )
  {
    typedef bool result_type;
    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0&, const A1&, const A2&) const
    {
      return true;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::arecatcompatible_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (ast_<A0>)
                              (scalar_<fundamental_<A1> >)
                              (scalar_<integer_<A2> >)
                            )
  {
    typedef bool result_type;
    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0&a0, const A1&, const A2& dim) const
    {
      return isvectoralong(a0, dim);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::arecatcompatible_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<fundamental_<A0> >)(ast_<A1>)
                              (scalar_<integer_<A2> >)
                            )
  {
    typedef bool result_type;
    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0&, const A1&a1, const A2& dim) const
    {
      return isvectoralong(a1, dim);
    }
  };
} }

#endif
