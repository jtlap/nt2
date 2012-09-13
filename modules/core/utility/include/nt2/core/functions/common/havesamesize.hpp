//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_HAVESAMESIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_HAVESAMESIZE_HPP_INCLUDED

#include <nt2/core/functions/havesamesize.hpp>
#include <nt2/include/functions/extent.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::havesamesize_, tag::cpu_
                            , (A0)(A1)
                            , (unspecified_<A0>)
                              (unspecified_<A1>)
                            )
  {
    typedef bool result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0, const A1& a1) const
    {
      return nt2::extent(a0) == nt2::extent(a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::havesamesize_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<fundamental_<A0> >)
                              (scalar_<fundamental_<A1> >)
                            )
  {
    typedef bool result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& , const A1& ) const
    {
      return true;
    }
  };
} }

#endif
