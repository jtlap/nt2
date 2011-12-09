//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_POINTER_BUFFER_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_POINTER_BUFFER_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/size.hpp>
#include <boost/swap.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <nt2/sdk/meta/remove_pointers.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/simd/sdk/memory/details/category.hpp>
#include <nt2/core/container/memory/adapted/pointer_buffer.hpp>


namespace nt2 { namespace memory
{

  template<class Type>
  class pointer_buffer
  {
    public:
    //==========================================================================
    // Inheritance type definition
    //==========================================================================
    typedef typename std::allocator<Type>     allocator_type;


    //============================================================================
    // Buffer type interface
    //============================================================================
    typedef Type                              value_type;                  
    typedef Type*                             pointer;
    typedef const Type*                       const_pointer;
    typedef Type*                             iterator;
    typedef const Type*                       const_iterator;
    typedef Type&                             reference;
    typedef const Type&                       const_reference;
    typedef std::size_t                       size_type;
    typedef std::ptrdiff_t                    difference_type;
    typedef std::ptrdiff_t                    index_type;


    //==========================================================================
    /**!
     *
     *
     **/
    //==========================================================================
    pointer_buffer( allocator_type const& a =allocator_type() ) 
    {
      bss_ = 0;
      begin_ = 0;
      end_ = 0;
    }

    //==========================================================================
    /**!
     *
     *
     **/
    //==========================================================================

    template<typename Sizes, typename Bases>
    pointer_buffer( Sizes           const& sz
                  , Bases           const& bs
                  , allocator_type  const& alloc = allocator_type()
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Sizes>
                              >::type* = 0
                  , typename  boost::enable_if<
                              boost::fusion::traits::is_sequence<Bases>
                              >::type* = 0
                  )
   {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , SIZE_MISMATCH_IN_BUFFER_CONSTRUCTOR
      , (Sizes)
      );

      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , BASE_MISMATCH_IN_BUFFER_CONSTRUCTOR
      , (Bases)
      );

      resize(sz);
      rebase(bs);
      begin_ = 0;

    }

    //==========================================================================
    /**!
     *
     *
     **/
    //==========================================================================
    template<typename Sizes, typename Bases>
    pointer_buffer( Type*           const& src
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
    {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , SIZE_MISMATCH_IN_BUFFER_CONSTRUCTOR
      , (Sizes)
      );

      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , BASE_MISMATCH_IN_BUFFER_CONSTRUCTOR
      , (Bases)
      );

      begin_ = src;
      resize(sz);
      rebase(bs);

    }

    pointer_buffer( pointer_buffer const& src )
    {
      begin_ = src.begin_;
      end_ = src.end_;
      bss_ = src.bss_;

    }


    //==========================================================================
    // Basic destructor 
    //==========================================================================

    ~pointer_buffer() {}

    //==========================================================================
    /**!
     * Assign a buffer to the current buffer 
     *
     * \param src buffer to assign
     * \return The now updated buffer
     **/
    //==========================================================================
    pointer_buffer& operator=(pointer_buffer const& src)
    {

      begin_ = src.begin_;
      bss_ = src.bss_;
      end_ = src.end_;

      return *this;
    }



    ////////////////////////////////////////////////////////////////////////////
    // Iterator related methods
    ////////////////////////////////////////////////////////////////////////////
    iterator
    begin()
    {
      return begin_;
    }

    const_iterator
    begin() const
    {
      return begin_;
    }


    iterator
    end()
    {
      return end_;
    }

    const_iterator
    end() const
    {
      return end_;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Forward size related methods
    ////////////////////////////////////////////////////////////////////////////
    size_type
    size() const
    {
      return end_ - begin_;
    }
    ////////////////////////////////////////////////////////////////////////////
    // RandomAccessContainer Interface
    ////////////////////////////////////////////////////////////////////////////

    reference
    operator[](difference_type const& i)
    {
      // BOOST_ASSERT_MSG( (i >= lower())
      //                 , "Position is below buffer bounds"
      //                 );
                      
      // BOOST_ASSERT_MSG( (i <= upper())
      //                 , "Position is out of buffer bounds"
      //                 );
      return begin_[i - bss_];
    }

    const_reference
    operator[](difference_type const& i) const
    {
      // BOOST_ASSERT_MSG( (i >= lower())
      //                 , "Position is below buffer bounds"
      //                 );
                      
      // BOOST_ASSERT_MSG( (i <= upper())
      //                 , "Position is out of buffer bounds"
      //                 );
      return begin_[i - bss_];
    }

    ////////////////////////////////////////////////////////////////////////////
    // Swapping
    ////////////////////////////////////////////////////////////////////////////
    void swap( pointer_buffer& src )
    {
      boost::swap(src.bss_,bss_);
      boost::swap(src.begin_,begin_);
      boost::swap(src.end_,end_);
    }

    ////////////////////////////////////////////////////////////////////////////
    // resize/rebase/restructure buffer
    ////////////////////////////////////////////////////////////////////////////
    //    using parent_data::rebase;

    template<class Bases>
    typename boost::enable_if< boost::fusion::traits::is_sequence<Bases> >::type
    rebase(Bases const & b) { 

      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , BASE_MISMATCH_IN_POINTER_BUFFER_REBASE
      , (Bases)
      );

      // if(begin_){
      //   begin_ += bss_;
      // }

      bss_ = boost::fusion::at_c<0>(b); 

      // if(begin_){
      //   begin_ -= bss_;
      // }
    }

    template<class Sizes>
    typename boost::enable_if< boost::fusion::traits::is_sequence<Sizes> >::type
    resize(Sizes const& s) {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , SIZE_MISMATCH_IN_POINTER_BUFFER_RESIZE
      , (Sizes)
      );



      end_ = begin_+ boost::fusion::at_c<0>(s);
    }

   

    template<class Bases,class Sizes>
    typename boost::enable_if_c < boost::fusion::traits::is_sequence<Sizes>::value
                                  &&
                                  boost::fusion::traits::is_sequence<Bases>::value
                                >::type
    restructure( Sizes const& s, Bases const& b)
    {
      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Bases>::value == 1)
      , BASE_MISMATCH_IN_POINTER_BUFFER_RESTRUCTURE
      , (Bases)
      );

      BOOST_MPL_ASSERT_MSG
      ( (boost::mpl::size<Sizes>::value == 1)
      , SIZE_MISMATCH_IN_POINTER_BUFFER_RESTRUCTURE
      , (Sizes)
      );

      resize(s);
      rebase(b);
    }

    protected:
    ////////////////////////////////////////////////////////////////////////////
    // Allocator access
    ////////////////////////////////////////////////////////////////////////////
    difference_type bss_;
    Type *begin_, *end_;


  };

  //============================================================================
  /**!
   * Swap the contents of two buffer of same type and allocator settings
   **/
  //============================================================================
  template<class T>
  void swap( pointer_buffer<T>& a, pointer_buffer<T>& b )
  {
    a.swap(b);
  }


} }
  


#endif
