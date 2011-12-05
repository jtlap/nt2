//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_VECTOR_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_VECTOR_HPP_INCLUDED

#include <vector>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <nt2/core/settings/sharing.hpp>
#include <nt2/core/container/meta/dereference.hpp>
#include <nt2/core/container/memory/buffer_adaptor.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================
  template<typename T, typename A>
  struct value_of< std::vector<T,A> > : value_of<T>
  {};


  //============================================================================
  // model_of specialization
  //============================================================================
  template<typename T, typename A>
  struct model_of< std::vector<T,A> >
  {
    struct type
    {
      template<class X> struct apply
      {
        // This recursive build is required to properly handle vector of vector
        // cases and other similar recursive structure
        typedef typename  boost::mpl::
                          apply<typename model_of<T>::type,X>::type base;
        typedef typename A::template rebind<base>::other            alloc;
        typedef std::vector<base,alloc>                             type;
      };
    };
  };
} } }

// namespace nt2 { namespace details
// {
//   template<std::size_t Dims> struct build
//   {
//     template<typename T, typename A, typename Sizes>
//     static inline void apply( std::vector<T,A>& v, Sizes const& s)
//     {
//       v.resize(boost::fusion::at_c<Dims-1>(s));
//       inner_apply(v,s,boost::mpl::size_t<Dims>());
//     }

//     template<typename T, typename A, typename Sizes, typename N> static inline
//     void inner_apply( std::vector<T,A>& v, Sizes const& s, N)
//     {
//       for(std::size_t i=0;i<boost::fusion::at_c<Dims-1>(s);++i)
//         build<Dims-1>::apply(v[i],s);
//     }

//     template<typename T, typename A, typename Sizes> static inline
//     void inner_apply( std::vector<T,A>&, Sizes const&, boost::mpl::size_t<1> const&)
//     {}
//   };
// } }

// namespace nt2 { namespace memory
// {

//   //============================================================================
//   // std::vector resize - Part of Buffer Concept
//   //============================================================================

//   template< typename T, typename A
//             , typename Sizes, typename Bases, typename Padding
//             >
//   inline void resize( std::vector<T,A>& v
//                       , Sizes const& s
//                       )
//   {
//     v.resize(boost::fusion::at_c<0>(s));
//   }


//   //============================================================================
//   // std::vector rebase - Part of Buffer Concept
//   //============================================================================

//     template< typename T, typename A
//             , typename Sizes, typename Bases, typename Padding
//             >
//   inline void rebase( std::vector<T,A>& 
//                       , Sizes const& , Bases const&, Padding const&
//                       )
//   {
//     //TODO : embedded std::vector into buffer to have mechanism with base and size
//   }


//   //============================================================================
//   // std::vector restructure - Part of Buffer Concept
//   //============================================================================

//   template< typename T, typename A
//             , typename Sizes, typename Bases, typename Padding
//             >
//   inline void restructure( std::vector<T,A>& v
//                            , Sizes const& s, Bases const&, Padding const&
//                            )
//   {
//     //resize
//     //rebase
//   }

// } }

namespace nt2 {  namespace memory
{


  template<  class Type, class Allocator,
             class Sizes ,
             class Bases ,
             class Padding ,
          >
  class buffer_adaptor<std::vector<Type, Allocator>,Sizes, Bases, Padding, owned_>
    : private std::vector<Type, Allocator>
  {
    public:

    // typedef typename Allocator::template rebind<Type>::other  parent_allocator;
    typedef std::vector<Type>            parent_data;


    ////////////////////////////////////////////////////////////////////////////
    // Forwarded types
    ////////////////////////////////////////////////////////////////////////////
    typedef typename parent_data::value_type       value_type;
    typedef typename parent_data::pointer          pointer;
    typedef typename parent_data::const_pointer    const_pointer;
    typedef typename parent_data::pointer          iterator;
    typedef typename parent_data::const_pointer    const_iterator;
    typedef typename parent_data::reference        reference;
    typedef typename parent_data::const_reference  const_reference;
    typedef typename parent_data::size_type        size_type;
    typedef typename parent_data::difference_type  difference_type;
    typedef typename parent_data::difference_type  index_type;

    ////////////////////////////////////////////////////////////////////////////
    // Constructor & destructor
    ////////////////////////////////////////////////////////////////////////////

    buffer_adaptor() {}

    template<class Base, class Size>
    buffer_adaptor( Base const& b
                    , Size const& s
                    )
    {
      bss_ = b;

    }


    ~buffer_adaptor() {  }

    ////////////////////////////////////////////////////////////////////////////
    // Assignment operator - SG version
    ////////////////////////////////////////////////////////////////////////////
    buffer_adaptor& operator=(buffer_adaptor const& src)
    {
      // we want to have a Strong Garantee and yet be performant
      // so we check if we need some resizing
      if(src.size() > this->size())
      {
        // If we do, use the SG copy+swap method
        buffer_adaptor that(src);
        swap(that);
      }
      else
      {
        // If not we just need to resize/rebase and copy which is SG here
        restructure(src.lower(),src.size());
        std::copy(src.begin(),src.end(),begin());
      }
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Iterator related methods
    ////////////////////////////////////////////////////////////////////////////
    using parent_data::begin;
    using parent_data::end;
    // using parent_data::first;
    // using parent_data::last;

    ////////////////////////////////////////////////////////////////////////////
    // Forward size related methods
    ////////////////////////////////////////////////////////////////////////////
    // using parent_data::lower;
    // using parent_data::upper;
    // using parent_data::size;

    ////////////////////////////////////////////////////////////////////////////
    // RandomAccessContainer Interface
    ////////////////////////////////////////////////////////////////////////////

    typename parent_data::reference
    operator[](typename parent_data::difference_type const& i)
    {
      return parent_data::begin_[i - boost::fusion::at_c<0>(bss_)];
    }

    typename parent_data::const_reference
    operator[](typename parent_data::difference_type const& i) const
    {
      return parent_data::begin_[i - boost::fusion::at_c<0>(bss_)];
    }

    ////////////////////////////////////////////////////////////////////////////
    // Swapping
    ////////////////////////////////////////////////////////////////////////////
    void swap( buffer_adaptor& src )
    {
    //   parent_data::swap(src);
    //   boost::swap(allocator(),src.allocator());
    }

    ////////////////////////////////////////////////////////////////////////////
    // resize/rebase/restructure buffer
    ////////////////////////////////////////////////////////////////////////////
    //    using parent_data::rebase;

    // template<class Size>
    // void resize(Size s) { parent_data::resize(s); }

    // template<class Base,class Size>
    // void restructure( Base const& b, Size const& s )
    // {
    //   resize(s);
    //   rebase(b);
    // }

    protected:
    ////////////////////////////////////////////////////////////////////////////
    // Allocator access
    ////////////////////////////////////////////////////////////////////////////
    //    using parent_data::allocator;
    Sizes szs_;
    Bases bss_;
  };
} } 

#endif
