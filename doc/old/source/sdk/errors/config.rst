.. _error_config:

Error Reporting Configuration
=============================

Description
-----------
The error handling in |nt2| is fully customizable by the user. The main intent is
to allow easy debugging sessions by being able to force various behavior on different
type of runtime error and to be able to strip down error handling to the bare minimum
for release mode.

Disabling Reports
-----------------

.. _nt2_disable_error:

NT2_DISABLE_ERROR
^^^^^^^^^^^^^^^^^
.. index::
  single: NT2_DISABLE_ERROR

If defined, :ref:`nt2_throw` performs a no-op instead of throwing an exception.
Note that, if exceptions are disabled via a compiler options like `-fno-exceptions`,
the reporting is automatically disabled unless a custom behavior is defined.

.. _nt2_disable_asserts:

NT2_DISABLE_ASSERTS
^^^^^^^^^^^^^^^^^^^
.. index::
  single: NT2_DISABLE_ASSERTS

If defined, runtime assertion are suppressed, forcing :ref:`nt2_assert` to
perform a no-op instead. This options takes precedence over
:ref:`nt2_asserts_as_exceptions`

Reports Customization
---------------------

.. _nt2_asserts_as_exceptions:

NT2_ASSERTS_AS_EXCEPTIONS
^^^^^^^^^^^^^^^^^^^^^^^^^
.. index::
  single: NT2_ASSERTS_AS_EXCEPTIONS

If defined, runtime assertion throw a :ref:`assertion_failure` instead of
a runtime assertion.

.. _nt2_custom_error:

NT2_CUSTOM_ERROR
^^^^^^^^^^^^^^^^

.. index::
  single: NT2_CUSTOM_ERROR

If ``NT2_CUSTOM_ERROR`` is defined and exceptions are disabled, a special
exception handling function can be specified. The user-defined function that
must be implemented in this case must follow the following prototype:

.. code-block:: cpp

  namespace nt2 { namespace ext
  {
    void throw_exception(std::exception const& e);
  } }

By default, if exceptions are disabled and no handler is defined, a link time
error will be raised.
