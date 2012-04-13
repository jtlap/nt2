.. _buffer:

buffer
======

.. index::
    single: buffer

Description
^^^^^^^^^^^

``buffer`` is a one dimensional memory block which can manage a relative indexation. 
This means that you can specify the `base` (starting index) of the memory block. If your `base` is -3 and your buffer size is 5, the resulting range of index is the following : [-3,2].

.. seealso::

  :ref:`allocator`


Template Parameters
^^^^^^^^^^^^^^^^^^^

  +-----------+------------------------------+------------------------------------+
  | Parameter | Requirement                  | Description                        |
  +===========+==============================+====================================+
  | Type      | None                         | Element type                       |
  +-----------+------------------------------+------------------------------------+
  | Allocator | Allocator Concept            | User allocator                     |
  |           |                              | Default one is :ref:`allocator`    |
  +-----------+------------------------------+------------------------------------+

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/memory/buffer.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace memory
  {
    ////////////////////////////////////////////////////////////////////////////
    // For more delails on buffer_data, see /nt2/sdk/memory/details/buffer_base.hpp
    ////////////////////////////////////////////////////////////////////////////
    template<class Type,class Allocator = nt2::memory::allocator<Type> >
    class buffer
        : private details::buffer_data< typename Allocator
                                        ::template rebind<Type>::other::pointer
                                    >
        , private Allocator::template rebind<Type>::other
    {
      public:

      typedef typename Allocator::template rebind<Type>::other         parent_allocator;
      typedef details::buffer_data<typename parent_allocator::pointer> parent_data;

      ////////////////////////////////////////////////////////////////////////////
      // Forwarded types
      ////////////////////////////////////////////////////////////////////////////
      typedef typename parent_allocator::value_type       value_type;
      typedef typename parent_allocator::pointer          pointer;
      typedef typename parent_allocator::const_pointer    const_pointer;
      typedef typename parent_allocator::reference        reference;
      typedef typename parent_allocator::const_reference  const_reference;
      typedef typename parent_allocator::size_type        size_type;
      typedef typename parent_allocator::difference_type  difference_type;
      typedef typename parent_allocator::difference_type  index_type;

      ////////////////////////////////////////////////////////////////////////////
      // Constructor & destructor
      ////////////////////////////////////////////////////////////////////////////
      buffer( Allocator const& a = Allocator() );

      template<class Base, class Size>
      buffer( Base const& b
            , Size const& s
            , Allocator const& a = Allocator()
            );

      ~buffer();

      buffer& operator=(buffer const& src);

      ////////////////////////////////////////////////////////////////////////////
      // Iterator related methods
      ////////////////////////////////////////////////////////////////////////////
      using parent_data::begin;
      using parent_data::end;

      ////////////////////////////////////////////////////////////////////////////
      // Forward size related methods
      ////////////////////////////////////////////////////////////////////////////
      using parent_data::lower;
      using parent_data::upper;
      using parent_data::size;

      ////////////////////////////////////////////////////////////////////////////
      // RandomAccessContainer Interface
      ////////////////////////////////////////////////////////////////////////////
      typename parent_allocator::reference
      operator[](typename parent_allocator::difference_type const& i);

      typename parent_allocator::const_reference
      operator[](typename parent_allocator::difference_type const& i) const;

      ////////////////////////////////////////////////////////////////////////////
      // Swapping
      ////////////////////////////////////////////////////////////////////////////
      void swap( buffer& src );

      ////////////////////////////////////////////////////////////////////////////
      // resize/rebase buffer
      ////////////////////////////////////////////////////////////////////////////
      using parent_data::rebase;

      template<class Size>
      void resize(Size s);

      template<class Base,class Size>
      void restructure( Base const& b, Size const& s );
 
      protected:
      ////////////////////////////////////////////////////////////////////////////
      // Allocator access
      ////////////////////////////////////////////////////////////////////////////
      parent_allocator& allocator();

      parent_allocator const& allocator() const;
  };

    //////////////////////////////////////////////////////////////////////////////
    // ADL swap
    //////////////////////////////////////////////////////////////////////////////
    template<class T, class Allocator>
    void swap( buffer<T,Allocator>& a, buffer<T,Allocator>& b );

} }


Operators
^^^^^^^^^

operator[](Args const&... )
---------------------------
.. index::
    single: buffer; operator[](Args const&... )

**Synopsis:**

.. code-block:: cpp

  typename parent_allocator::reference
  operator[](typename parent_allocator::difference_type const& i);

  typename parent_allocator::const_reference
  operator[](typename parent_allocator::difference_type const& i) const;

**Description:** Random Access Iterator interface for accessing data in the buffer.

Example
^^^^^^^^

The compilation of the following code sample:

.. literalinclude:: ../../../../../modules/sdk/examples/memory/buffer.cpp
   :language: cpp

leads to the following compiler output when compiled with g++ on a Linux machine:

.. code-block:: bash

  Buffer 1 size  = 5
  Buffer 2 size  = 5

