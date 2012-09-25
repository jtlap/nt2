//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALANY_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALANY_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the globalany function
**/

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/functions/global.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the globalany_ functor
    **/
    struct globalany_ : tag::formal_
    {
      typedef tag::formal_ parent;
    };
  }

  /*!
    @brief Checks that any elements of an expression is non-zero

    @param a0 Expression to check
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalany_       , globalany, 1)
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalany_, tag::cpu_
                            , (A0)
                            , (unspecified_<A0>)
                            )
  {
    typedef typename meta::call < tag::global_( nt2::functor<nt2::tag::any_>
                                              , const A0&
                                              )
                                >::type                             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return global(nt2::functor<nt2::tag::any_>(), a0);
    }
  };
} }

#endif
