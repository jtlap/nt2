/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONCEPT_ALLOCATOR_HPP_INCLUDED
#define NT2_SDK_CONCEPT_ALLOCATOR_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// NT2 Allocator concept
//* TODO: Documentation: http://nt2.lri.fr/sdk/concept/allocator.hpp
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/error/concepts.hpp>
#include <nt2/sdk/concepts/same_type.hpp>

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // Allocator concept
  //////////////////////////////////////////////////////////////////////////////
  template<class X> struct  Allocator
        : boost::CopyConstructible<X>
        , boost::DefaultConstructible<X>
        , boost::EqualityComparable<X>
  {
    typedef typename X::value_type      value_type;
    typedef typename X::pointer         pointer;
    typedef typename X::const_pointer   const_pointer;
    typedef typename X::reference       reference;
    typedef typename X::const_reference const_reference;
    typedef typename X::size_type       size_type;

    typedef typename X::template rebind<value_type>::other other;
    BOOST_CONCEPT_ASSERT((SameType<X,other>));

    BOOST_CONCEPT_USAGE(Allocator)
    {
      p   = x.allocate(s);
      s   = x.max_size();
      p   = x.address((value_type&)(v));
      cp  = x.address((value_type const&)(v));
      x.construct(p,v);
      x.destroy(p);
      x.deallocate(p,s);
    }

    private:
    X                 x;
    size_type         s;
    pointer           p;
    const_pointer     cp;
    value_type        v;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Allocator archetype
  //////////////////////////////////////////////////////////////////////////////
  template <class T> class allocator_archetype
  {
    public:
    typedef T           value_type;
    typedef T*          pointer;
    typedef T const*    const_pointer;
    typedef T&          reference;
    typedef T const&    const_reference;
    typedef std::size_t size_type;

    template<class U> struct rebind { typedef allocator_archetype<U> other; };

    pointer   allocate(size_type)           { return 0; }
    size_type max_size()                    { return 0; }
    pointer       address(reference)        { return 0; }
    const_pointer address(const_reference)  { return 0; }
    void construct(pointer,const_reference) {}
    void destroy(pointer)                   {}
    void deallocate(pointer,size_type)      {}

    bool operator==(allocator_archetype const&) { return true; }
    bool operator!=(allocator_archetype const&) { return false; }
  };
}

#endif
