//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_ISEQUALN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_ISEQUALN_HPP_INCLUDED

#include <nt2/core/functions/isequaln.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/havesamesize.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/is_equal_with_equal_nans.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isequaln_, tag::cpu_
                            , (A0)(A1)
                            , (unspecified_<A0>)
                              (unspecified_<A1>)
                            )
  {
    typedef bool result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0, const A1& a1) const
    {
      if (isempty(a0)&&isempty(a1)) return true;
      if (!havesamesize(a0, a1)) return false;
      return nt2::all(is_equal_with_equal_nans(a0,a1)(_))(1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isequaln_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<fundamental_<A0> >)
                              (scalar_<fundamental_<A1> >)
                            )
  {
    typedef bool result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0, const A1& a1) const
    {
      return is_equal_with_equal_nans(a0,a1);
    }
  };
} }

#endif
