//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_MNORM_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_MNORM_HPP_INCLUDED
#include <nt2/linalg/functions/mnorm.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/ismatrix.hpp>
#include <nt2/include/functions/isvector.hpp>
#include <nt2/include/functions/svd.hpp>
#include <nt2/include/functions/globalnorm2.hpp>
#include <nt2/include/functions/mnorm1.hpp>
#include <nt2/include/functions/mnorminf.hpp>
#include <nt2/include/functions/mnormfro.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/functions/table/details/is_definitely_vector.hpp>
#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/static_assert.hpp>
#include <nt2/sdk/meta/is_target.hpp>
#include <boost/utility/enable_if.hpp>

namespace nt2
{
  namespace tag
  {
    struct Fro     : tag::Mone   {};
  }
  nt2::meta::as_<tag::Fro>     const Fro = {};
}

namespace nt2 {  namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mnorm_, tag::cpu_
                            , (A0)
                            , (scalar_<unspecified_<A0> >)
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return nt2::abs(a0);
    }

  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mnorm_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> >)
                              (unspecified_<A1>)
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return nt2::abs(a0);
    }

  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mnorm_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      BOOST_ASSERT_MSG(nt2::ismatrix(a0), "a0 is not a matrix");
      typedef typename details::is_vector<typename A0::extent_type>::type choice_t;
      return eval(a0, choice_t());
    }

    BOOST_FORCEINLINE result_type
    eval(A0 const& a0, boost::mpl::true_ const &) const
    {
      return globalnorm2(a0);
    }

    BOOST_FORCEINLINE result_type
    eval(A0 const& a0, boost::mpl::false_ const &) const
    {
      return svd(a0)(1);
    }

    BOOST_FORCEINLINE result_type
    eval(A0 const& a0, nt2::meta::indeterminate_ const &) const
    {
      if (isvector(a0))
      {
        return globalnorm2(a0);
      }
      else
      {
        return svd(a0)(1);
      }
    }


  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mnorm_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<arithmetic_<A1> >)
                            )
  {
    typedef typename A0::value_type                   type_t;
    typedef typename meta::as_real<type_t>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const & a1) const
    {
      BOOST_ASSERT_MSG(nt2::ismatrix(a0), "a0 is not a matrix");
      result_type choice = result_type(a1);
      if (choice == Two<result_type>())
      {
        return nt2::mnorm(a0);
      }
      else if (choice == One<result_type>())
      {
        return nt2::mnorm1(a0);
      }
      else if (choice == Inf<result_type>())
      {
        return nt2::mnorminf(a0);
      }
      else if (is_ltz(choice))
      {
        return nt2::mnormfro(a0);
      }
      else
      {
        BOOST_ASSERT_MSG(false, "mnorm is not defined for this parameters setting");
        return Nan<result_type>();
      }
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mnorm_, tag::cpu_,
                                     (A0)(A1),
                                     ((ast_<A0, nt2::container::domain>))
                                     (unspecified_<A1>)
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
      return nt2::mnorminf(a0);
    }
    BOOST_FORCEINLINE result_type eval(A0 const &a0
                                      , nt2::meta::as_<tag::One> const&) const
    {
      return nt2::mnorm1(a0);
    }
    BOOST_FORCEINLINE result_type eval(A0 const &a0
                                      , nt2::meta::as_<tag::Two> const&) const
    {
      return mnorm(a0);
    }
    BOOST_FORCEINLINE result_type eval(A0 const &a0
                                      , nt2::meta::as_<tag::Fro> const&) const
    {
      return mnormfro(a0);
    }
    template < class T >
    BOOST_FORCEINLINE result_type eval(A0 const &a0
                                      , nt2::meta::as_<T> const&) const
    {
      BOOST_ASSERT_MSG(false, "mnorm is not defined for this parameters setting");
    }
  };

} }

#endif
