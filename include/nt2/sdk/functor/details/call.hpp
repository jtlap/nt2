/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_CALL_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_CALL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// User-overloadable call meta-function
// Documentation:http://nt2.lri.fr/extension/custom_function.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/unknown.hpp>
#include <nt2/sdk/functor/hierarchy.hpp>
#include <nt2/sdk/error/static_assert.hpp>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // Flag call instanciation as callable
  //////////////////////////////////////////////////////////////////////////////
  struct callable { typedef void callable_type; };

  //////////////////////////////////////////////////////////////////////////////
  // Call to non-categorizable types ends up in error
  //////////////////////////////////////////////////////////////////////////////
  template<class Function,class Hierarchy,class I>
  struct call<Function,tag::unknown,Hierarchy,I> : callable
  {
    typedef int result_type;
    /**
     * If you get an error here, you tried to call a nt2 function on values
     * which types is not supported by nt2. Check that you included the proper
     * toolbox or use the correct type in your function  call.
     **/
    NT2_STATIC_ASSERT ( (boost::is_same<Function,void>::value)
                      , NT2_UNSUPPORTED_TYPE
                      , (Hierarchy)
                      );
  };

  template<class Function,class Category,class I>
  struct call<Function,Category,functors::empty_,I> : callable
  {
    typedef int result_type;
    /**
     * If you get an error here, you tried to call a nt2 function
     * which is not implemented on the given hierarchy types.
     * Check that a proper call<> overload is available and, if it
     * exists, if this specialziation inherits from callable
     **/
    NT2_STATIC_ASSERT ( (boost::is_same<Function,void>::value)
                      , NT2_UNSUPPORTED_FUNCTOR
                      , (Category)
                      );
  };
} }

#endif
