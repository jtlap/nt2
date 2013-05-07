//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_ISREAL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_ISREAL_HPP_INCLUDED

#include <nt2/core/functions/isreal.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/is_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isreal_, tag::cpu_
                            , (A0)(S0)(T)(M)
                            , ((expr_< table_< fundamental_<A0>, S0 >
                                     , T
                                     , M
                                     >
                               ))
                            )
  {
    typedef bool result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0) const
    {
      return true;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isreal_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef bool result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0) const
    {
      return nt2::is_real(a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::isreal_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef bool result_type;

    BOOST_DISPATCH_FORCE_INLINE
    result_type operator()(const A0& a0) const
    {
      return nt2::globalall(nt2::is_real(a0));
    }

  };

} }

#endif
