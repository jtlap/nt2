//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_EXTENT_EXTENT_HPP_INCLUDED
#define NT2_CORE_CONTAINER_EXTENT_EXTENT_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>

namespace nt2 { namespace container
{
  template<typename Sizes>
  struct  extent
        : expression< typename boost::proto::terminal<Sizes>::type
                    , Sizes&
                    >
  {
    typedef std::ptrdiff_t        value_type;
    typedef std::ptrdiff_t&       reference;
    typedef std::ptrdiff_t const& const_reference;

    typedef expression< typename boost::proto::terminal<Sizes>::type
                      , Sizes&
                      >           parent;

    extent() {}

    reference operator()(std::size_t i)
    {
      return boost::proto::value(*this)[i-1];
    }

    const_reference operator()(std::size_t i) const
    {
      return boost::proto::value(*this)[i-1];
    }

    std::size_t size() const { return boost::proto::value(*this).size(); }

    /*
       // Construction from arbitrary expression is same as assignment
      template<class Xpr>
      BOOST_DISPATCH_FORCE_INLINE extent(Xpr const& xpr) { *this = xpr; }

      // Assignment operators force evaluation
      BOOST_DISPATCH_FORCE_INLINE extent& operator=(extent const& xpr)
      {
        nt2::evaluate( nt2::assign(*this, xpr) );
        return *this;
      }

      template<class Xpr>
      BOOST_DISPATCH_FORCE_INLINE extent& operator=(Xpr const& xpr)
      {
        nt2::evaluate( nt2::assign(*this, xpr) );
        return *this;
      }
    };
    */

  };
} }


namespace boost { namespace dispatch { namespace meta
{
  template<typename Sizes>
  struct  semantic_of< nt2::container::extent<Sizes> >
        : semantic_of< typename nt2::container::extent<Sizes>::parent >
  {};

} } }

#endif
