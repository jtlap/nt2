//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_ISEXPANDABLE_TO_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_ISEXPANDABLE_TO_HPP_INCLUDED

#include <nt2/core/functions/isexpandable_to.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/size.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isexpandable_to_, tag::cpu_
                              , (A0)(A1)
                              , (ast_<A0>)
                              (unspecified_<A1>)
                              )
  {
    typedef bool result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0, const A1& siz) const
    {
      typedef typename meta::call<tag::extent_(A0 const&)>::type ext1_t;
      ext1_t ex1 = nt2::extent(a0);
      if (isempty(a0) && nt2::numel(siz) == 0) return true; 
      size_t sz =  nt2::min(ex1.size(), siz.size());
      for(size_t i=0; i < sz; ++i)
      {
        if ((ex1.data()[i]!= siz.data()[i]) && (ex1.data()[i]!= 1)) return false;
      }

      for(size_t i=sz; i < ex1.size(); ++i)
      {
        if (ex1[i]!= 1) return false;
      }
      return true;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isexpandable_to_, tag::cpu_
                              , (A0)(A1)
                              , (scalar_<fundamental_<A0> >)
                              (ast_<A1>)
                              )
  {
    typedef bool result_type;
    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0&, const A1& a1) const
    {
      return nt2::numel(a1);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isexpandable_to_, tag::cpu_
                              , (A0)(A1)
                              , (scalar_<fundamental_<A0> >)
                              (fusion_sequence_<A1>)
                              )
  {
    typedef bool result_type;
    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0&, const A1& a1) const
    {
      return nt2::numel(a1) != 0;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isexpandable_to_, tag::cpu_
                            , (A0)(A1)
                            , (ast_<A0>)
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef bool result_type;
    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0&a0, const A1& a1) const
    {
      return (nt2::size(a0, 1) == size_t(a1)) || (nt2::size(a0, 1) == 1u); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isexpandable_to_, tag::cpu_
                            , (A0)(A1)
                            , (fusion_sequence_<A0>)
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef bool result_type;
    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0&a0, const A1& a1) const
    {
      return (nt2::size(a0, 1) == size_t(a1)) || (nt2::size(a0, 1) == 1u); 
    }
  };
  

} }

#endif
