//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_BUFFER_ADAPTOR_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_BUFFER_ADAPTOR_HPP_INCLUDED

#include <vector>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <nt2/core/container/meta/dereference.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>
#include <nt2/core/container/memory/buffer_adaptor.hpp>

//==============================================================================
// Fill out the Buffer concepts for std::vector
//==============================================================================
namespace nt2 { namespace meta
{
  template< class Type >
  struct  dimensions_of< memory::buffer_adaptor<Type> >
        : boost::mpl::size_t<1>
  {};


} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================

  template<  class Type>
  struct value_of< nt2::memory::buffer_adaptor<Type> > : value_of<Type>
  {};

  // ============================================================================
  // model_of specialization
  // ============================================================================

  template<  class Type >
  struct model_of< nt2::memory::buffer_adaptor<Type> > 
  {};


} } }



#endif
