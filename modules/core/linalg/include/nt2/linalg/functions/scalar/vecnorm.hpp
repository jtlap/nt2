//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_VECNORM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_VECNORM_HPP_INCLUDED

#include <nt2/linalg/functions/vecnorm.hpp>
#include <nt2/include/functions/scalar/vecnorm.hpp>
#include <nt2/include/functions/scalar/is_nan.hpp>
#include <nt2/include/functions/scalar/is_finite.hpp>
#include <nt2/include/functions/scalar/is_gtz.hpp>
#include <nt2/include/functions/globalmin.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/globalasum1.hpp>
#include <nt2/include/functions/globalnorm2.hpp>
#include <nt2/include/functions/globalnormp.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/core/container/dsl.hpp>
#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::vecnorm_, tag::cpu_,
                                     (A0),
                                     ((ast_<A0, nt2::container::domain>))
                                     )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const &a0) const
      {
        return globalnorm2(a0);
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::vecnorm_, tag::cpu_,
                                     (A0)(A1),
                                     ((ast_<A0, nt2::container::domain>))
                                     (scalar_<arithmetic_<A1> > )
                                     )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const &a0, A1 const& a1) const
      {
        BOOST_ASSERT_MSG((a1 > 0)|| (a1 == Minf<A1>()), "p must be positive or -inf");
        result_type choice = result_type(a1);
        if (is_nan(choice)) return Nan<result_type>();
        if (choice == Two<result_type>())
        {
          return nt2::vecnorm(a0);
        }
        else if (choice == One<result_type>())
        {
          return nt2::globalasum1(a0);
        }
        else if (nt2::is_finite(choice))
        {
          return nt2::globalnormp(a0, choice);
        }
        else if (is_gtz(choice))
        {
          return nt2::globalmax(nt2::abs(a0));
        }
        else
        {
          return nt2::globalmin(nt2::abs(a0));
        }
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::vecnorm_, tag::cpu_,
                                     (A0)(A1),
                                     ((ast_<A0, nt2::container::domain>))
                                     (target_<unspecified_<A1> >)
                                     )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const &a0, A1 const&) const
    {
      return eval(a0, A1());
    }

  private:
    BOOST_FORCEINLINE result_type eval(A0 const &a0
                                      , nt2::meta::as_<tag::Inf> const&) const
    {
      return nt2::globalmax(nt2::abs(a0));
    }
    BOOST_FORCEINLINE result_type eval(A0 const &a0
                                      , nt2::meta::as_<tag::Minf> const&) const
    {
      return nt2::globalmin(nt2::abs(a0));
    }
    BOOST_FORCEINLINE result_type eval(A0 const &a0
                                      , nt2::meta::as_<tag::One> const&) const
    {
      return nt2::globalasum1(nt2::abs(a0));
    }
    BOOST_FORCEINLINE result_type eval(A0 const &a0
                                      , nt2::meta::as_<tag::Two> const&) const
    {
      return vecnorm(a0);
    }
  };




  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::vecnorm_, tag::cpu_,
                                     (A0)(A1),
                                     (scalar_<arithmetic_<A0> > )
                                     (scalar_<arithmetic_<A1> > )
                                     )
  {
    typedef typename meta::as_real<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const &a0, A1 const& ) const
      {
        return result_type(nt2::abs(a0));
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::vecnorm_, tag::cpu_,
                                     (A0),
                                     (scalar_<arithmetic_<A0> > )
                                     )
  {
    typedef typename meta::as_real<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const &a0) const
      {
        return result_type(nt2::abs(a0));
      }
  };

} }

#endif
