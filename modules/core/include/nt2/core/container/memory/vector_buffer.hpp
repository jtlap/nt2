//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_VECTOR_BUFFER_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_VECTOR_BUFFER_HPP_INCLUDED

#include <vector>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/swap.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>
#include <nt2/core/container/meta/dereference.hpp>
#include <nt2/core/container/memory/adapted/vector_buffer.hpp>

#include <iostream>

namespace nt2 {  namespace memory
{

  template<  class Type, class Allocator=std::allocator<Type>
          >
  class vector_buffer
    : private std::vector<Type, Allocator>
  {
    public:


    typedef std::vector<Type,Allocator>            parent_data;
    typedef typename parent_data::allocator_type   allocator_type;

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


    vector_buffer( Allocator const& a = Allocator() ) : parent_data(a) {}

    template<typename Sizes, typename Bases>
    vector_buffer( Sizes            const& sz
                  , Bases           const& bs
                  , allocator_type  const& alloc = allocator_type()
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Sizes>
                              >::type* = 0
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Bases>
                              >::type* = 0
                  )
    : parent_data(boost::fusion::at_c<0>(sz))
    {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , SIZE_MISMATCH_IN_VECTOR_BUFFER_CONSTRUCTOR
      , (Sizes)
      );

      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , BASE_MISMATCH_IN_VECTOR_BUFFER_CONSTRUCTOR
      , (Bases)
      );

      rebase(bs);
    }


    template<typename Sizes, typename Bases>
    vector_buffer( vector_buffer    const& src
                  , Sizes           const& sz
                  , Bases           const& bs
                  , allocator_type  const& alloc = allocator_type()
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Sizes>
                              >::type* = 0
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Bases>
                              >::type* = 0
                  )
    : parent_data(boost::fusion::at_c<0>(sz))
    {
      // BOOST_MPL_ASSERT_MSG
      // ( (boost::mpl::size<Sizes>::value == 1)
      // , SIZE_MISMATCH_IN_VECTOR_BUFFER_CONSTRUCTOR
      // , (Sizes)
      // );

      // BOOST_MPL_ASSERT_MSG
      // ( (boost::mpl::size<Bases>::value == 1)
      // , BASE_MISMATCH_IN_VECTOR_BUFFER_CONSTRUCTOR
      // , (Bases)
      // );

      this->copy(src, boost::fusion::at_c<0>(sz), boost::fusion::at_c<0>(bs));
    }


    vector_buffer( vector_buffer const& src )
      : parent_data(src.size())
    {
      //      bss_ = src.bss_;
      this->copy( src, src.size(),src.bss_);
    }



    ~vector_buffer() {  }

    ////////////////////////////////////////////////////////////////////////////
    // Assignment operator - SG version
    ////////////////////////////////////////////////////////////////////////////
    vector_buffer& operator=(vector_buffer const& src)
    {

      // we want to have a Strong Garantee and yet be performant
      // so we check if we need some resizing
      if(src.size() > this->size())
      {
        // If we do, use the SG copy+swap method
        std::cout << "We need resizing" << std::endl;
        vector_buffer that(src);
        swap(that);
      }
      else
      {
        // // If not we just need to resize/rebase and copy which is SG here
        //restructure
        parent_data::resize(src.size());
        bss_ = src.bss_;

        std::copy(src.begin(),src.end(),begin());
      }
           return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Iterator related methods
    ////////////////////////////////////////////////////////////////////////////
    using parent_data::begin;
    using parent_data::end;

    ////////////////////////////////////////////////////////////////////////////
    // Forward size related methods
    ////////////////////////////////////////////////////////////////////////////
    using parent_data::size;

    ////////////////////////////////////////////////////////////////////////////
    // RandomAccessContainer Interface
    ////////////////////////////////////////////////////////////////////////////

    reference
    operator[](difference_type const& i)
    {
      // BOOST_ASSERT_MSG( (i - bss_ >= parent_data::size)
      //                 , "Position is below buffer bounds"
      //                 );
                      
      // BOOST_ASSERT_MSG( (i - bss_ <= 0)
      //                 , "Position is out of buffer bounds"
      //                 );

      return parent_data::operator[](i - bss_);
    }

    const_reference
    operator[](difference_type const& i) const
    {
      // BOOST_ASSERT_MSG( (i - bss_ >= parent_data::size)
      //                 , "Position is below buffer bounds"
      //                 );
                      
      // BOOST_ASSERT_MSG( (i - bss_ <= 0)
      //                 , "Position is out of buffer bounds"
      //                 );

      return parent_data::operator[](i - bss_);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Swapping
    ////////////////////////////////////////////////////////////////////////////
    void swap( vector_buffer& src )
    {
      //      bss_ = src.bss_;
      boost::swap(bss_, src.bss_);
      parent_data::swap(src.begin());
    }

    ////////////////////////////////////////////////////////////////////////////
    // resize/rebase/restructure buffer
    ////////////////////////////////////////////////////////////////////////////
    //    using parent_data::rebase;
    //    using parent_data::resize;

    template<class Bases>
    typename boost::enable_if< boost::fusion::traits::is_sequence<Bases> >::type
    rebase(Bases b) { 
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , SIZE_MISMATCH_IN_VECTOR_BUFFER_REBASE
      , (Bases)
      );

      bss_ = boost::fusion::at_c<0>(b); 
    }


    template<class Sizes>
    typename boost::enable_if< boost::fusion::traits::is_sequence<Sizes> >::type
    resize(Sizes s) { 
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , BASE_MISMATCH_IN_VECTOR_BUFFER_RESIZE
      , (Sizes)
      );
      parent_data::resize(boost::fusion::at_c<0>(s)); 
    }


    template<class Bases, class Sizes>
    typename boost::enable_if_c < boost::fusion::traits::is_sequence<Sizes>::value
                                  &&
                                  boost::fusion::traits::is_sequence<Bases>::value
                                >::type
    restructure( Sizes const& sz, Bases const& bs )
    {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , BASE_MISMATCH_IN_VECTOR_BUFFER_RESTRUCTURE
      , (Bases)
      );

      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , SIZE_MISMATCH_IN_VECTOR_BUFFER_RESTRUCTURE
      , (Sizes)
      );

      resize(sz);
      rebase(bs);
    }

    protected:
    ////////////////////////////////////////////////////////////////////////////
    // Allocator access
    ////////////////////////////////////////////////////////////////////////////
    //    using parent_data::allocator;
    typename parent_data::difference_type bss_;


    void copy( vector_buffer const& src, size_type const& s, difference_type const& b )
    {
      //restructure(s,b);
      parent_data::resize(s);
      bss_ = b;
      std::copy(src.begin(),src.end(),begin());
    }
 
  };

  //============================================================================
  /**!
   * Swap the contents of two buffer of same type and allocator settings
   **/
  //============================================================================
  template<class T, class A>
  void swap( vector_buffer<T,A>& a, vector_buffer<T,A>& b )
  {
    a.swap(b);
  }


} } 



#endif
