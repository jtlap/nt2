.. _string:

string
======

.. index::
    single: string (sys)
    single: sys; string

Description
^^^^^^^^^^^
Encapsulate a null-terminated C string in a RAII enabled lightweight class. The
purpose of ``sys::string`` is to provide a ``std::string`` replacement that can
be used on a large selection of architecture, including systems unable to afford
linking with ``libstd++``.

Header File
^^^^^^^^^^^

.. code-block:: cpp

  #include <nt2/sdk/sys/string.hpp>

Synopsis
^^^^^^^^

.. code-block:: cpp

  namespace nt2 { namespace sys
  {
    class string
    {
      public:
      string();
      string(std::size_t n);
      string(string const& src);
      string(char const* format, ...);

      ~string();

      string& operator=( string src );
      string& operator=( char const* src );
      void swap( string& src );

      char const* c_str() const;
      char*       c_str();
    };

    void swap( string& a, string& b );

    bool operator==( string const& a, string const& b );
    bool operator==( char const*   a, string const& b );
    bool operator==( string const& a, char const* b   );

    bool operator!=( string const& a, string const& b );
    bool operator!=( char const*   a, string const& b );
    bool operator!=( string const& a, char const* b   );
  } }

Constructors
^^^^^^^^^^^^

string()
--------

.. index::
    single: string (sys); string()

**Synopsis:**

.. code-block:: cpp

    string();

**Description:** Constructs an empty ``string``. After construction,
the string size is equals to 0.

string(string const&)
---------------------

.. index::
    single: string (sys); string(string const&)

**Synopsis:**

.. code-block:: cpp

    string(string const& src);

**Description:** ``string`` copy constructor.

string(std::size_t)
-------------------

.. index::
    single: string (sys); string(std::size_t)

**Synopsis:**

.. code-block:: cpp

    string(std::size_t n);

**Description:** Constructs a ``string`` by preallocating ``n`` characters.
After construction, the string size is equals to ``n`` but the string itself
is empty.

string(char const*, ...)
------------------------

.. index::
    single: string (sys); string(char const*, ...)

**Synopsis:**

.. code-block:: cpp

    string(char const* format, ...)

**Description:** Constructs a ``string`` from a ``printf``-like format string
and an undetermined list of :term:`POD` arguments. After construction, the string
contains the formated string.

Member Functions
^^^^^^^^^^^^^^^^

operator=
---------

.. index::
    single: string (sys); operator=

**Synopsis:**

.. code-block:: cpp

    string& operator=( string );

**Description:** Assign a string to another one. For exception safety purpose,
the potential copy is made via the copy-by-swap idiom.

swap( string& )
---------------

.. index::
    single: string (sys); swap

**Synopsis:**

.. code-block:: cpp

    void swap( string& )

**Description:** Swap the contents of the current string with another one. This
method is exception-safe.

c_str()
-------

.. index::
    single: string (sys); c_str()

**Synopsis:**

.. code-block:: cpp

      char const* c_str() const;

**Description:** Return the null-terminated C string held by the current string.

Functions
^^^^^^^^^

operator==
-----------

.. index::
    single: string (sys); operator==

**Synopsis:**

.. code-block:: cpp

    bool operator==( string const& a, string const& b );
    bool operator==( char const*   a, string const& b );
    bool operator==( string const& a, char const* b   );

**Description:** Returns ``true`` if the two string are equals.

operator!=
-----------

.. index::
    single: string (sys); operator!=

**Synopsis:**

.. code-block:: cpp

    bool operator!=( string const& a, string const& b );
    bool operator!=( char const*   a, string const& b );
    bool operator!=( string const& a, char const* b   );

**Description:** Returns ``true`` if the two string are different.

swap( string&, string& )
------------------------

.. index::
    single: string (sys); swap

**Synopsis:**

.. code-block:: cpp

    void swap( string& a, string& b)

**Description:** Swap the contents of two strings references. Provided as a generic
programming facility.

Example
^^^^^^^

.. literalinclude:: ../../../../examples/sdk/sys/string.cpp
   :language: cpp
