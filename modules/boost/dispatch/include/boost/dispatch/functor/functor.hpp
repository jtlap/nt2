//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_FUNCTOR_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_FUNCTOR_HPP_INCLUDED

/*!
 * \file
 * \brief Implements Boost.Dispatch main functor handler
 */

/*!
 * \defgroup functors Functor system
 * \ingroup sdk
 * This module gathers macros, classes and functions to define, implement
 * and specialize polymorphic functors.
 */

#include <boost/config.hpp>
#include <boost/type_traits/common_type.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/meta/as_ref.hpp>
#include <boost/dispatch/functor/forward.hpp>
#include <boost/dispatch/functor/details/call.hpp>
#include <boost/dispatch/functor/details/dispatch.hpp>
#include <boost/dispatch/functor/meta/make_functor.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace dispatch
{
  //============================================================================
  /*!
   * \ingroup functors
   * \ref functor is a generic, concept-dispatched polymorphic function object.
   * Every function in Boost.Dispatch are defined in term of implementing a call strategy
   * for \ref functor. The main rationale is to centralize and homogenize the way
   * functions with multiple possible implementation with respect to types,
   * architectures and compilation phases are handled.
   *
   * \tparam Tag Function tag to dispatch to.
   * \tparam EvalContext Tag defining how to perform said function call with
   * respect to architecture or phase settings.
   *
   * \par Models:
   * \dco
   *
   * \see call
   * \see hierarchy
   * \see make_functor
   */
  //============================================================================
  template<class Tag, class EvalContext> struct functor
  {
    typedef Tag         tag_type;
    typedef EvalContext context_type;

    template<class Sig> struct result;

    template<class This, class... Args>
    struct result<This(Args...)>
      : meta::
        result_of< typename meta::
                   dispatch_call< Tag(typename meta::as_ref<Args>::type...)
                                , EvalContext
                                >::type(typename meta::as_ref<Args>::type...)
                 >
    {};

    //==========================================================================
    /*!
     * Polymorphic variadic function call operator. This catch-all operators
     * dispatches its arguments to the proper type and architecture based
     * implementation using the hierarchy_of system.
     *
     * \param args Arguments of function \c Tag implementation
     * \return The result of the calculation of function \c Tag
     */
    //==========================================================================
    template<class... Args> BOOST_FORCEINLINE
    typename result<functor(typename meta::as_ref<Args>::type...)>::type
    operator()( Args&& ...args ) const
    {
      return typename meta::
             dispatch_call< Tag(typename meta::as_ref<Args>::type...)
                          , EvalContext
                          >::type()
             ( static_cast<typename meta::as_ref<Args>::type>(args)... );
    }

  };
} }

#endif
