//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBALASUMP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBALASUMP_HPP_INCLUDED

/*!
  @file
  @brief Define and implements the globalasump function
**/

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/asump.hpp>
#include <nt2/include/functions/global.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the globalasump functor
    **/
    struct globalasump_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief Asump of all the elements of an expression

    @param a0 Expression to asump
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::globalasump_, globalasump, 2)
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::globalasump_, tag::cpu_
                              , (A0)(A1)
                              , (unspecified_<A0>)
                              (scalar_<arithmetic_<A1> > ) 
                            )
  {
    typedef typename meta::call<tag::global_( nt2::functor<tag::asump_>
                                            , const A0&
                                            , const A1&  
                                            )>::type                result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
       return global(nt2::functor<tag::asump_>(), a0, a1);
    }
  };
} }

#endif
