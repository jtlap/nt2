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

.. index::
  single: NT2_DISABLE_WARNING
  single: NT2_DISABLE_ERROR
  single: NT2_DISABLE_FAILURE

Each reporting macro can be completely disabled by the one of the following
macros.

* ``NT2_DISABLE_WARNING``
* ``NT2_DISABLE_ERROR``
* ``NT2_DISABLE_FAILURE``

Note that, for :ref:`errors`, if exceptions are disabled via a compiler options like
`-fno-exceptions`, the reporting is automatically disabled unless a custom behavior
for :ref:`errors` is defined.

Reports Custom Handlers
-----------------------

.. index::
  single: NT2_CUSTOM_WARNING
  single: NT2_CUSTOM_ERROR
  single: NT2_CUSTOM_FAILURE

Each reporting macro can be forwarded to an external, user-defined function if
one of these symbol is defined.

* ``NT2_CUSTOM_WARNING``
* ``NT2_CUSTOM_ERROR``
* ``NT2_CUSTOM_FAILURE``

The user-defined function that must be implemented in those case are:

* :ref:`_nt2_ext_emit_warning`
* :ref:`_nt2_ext_emit_error`
* :ref:`_nt2_ext_emit_failure`

Reports Exit Codes
------------------

.. index::
  single: NT2_WARNING_EXIT_CODE
  single: NT2_ERROR_EXIT_CODE
  single: NT2_FAILURE_EXIT_CODE

By default, or when an :ref:`warnings` or :ref:`errors` report is upgraded as a
:ref:`failures` report, the faulty application exits while returning the `EXIT_FAILURE`
value. The following symbols can be set to modify this value.

* ``NT2_WARNING_EXIT_CODE``
* ``NT2_ERROR_EXIT_CODE``
* ``NT2_FAILURE_EXIT_CODE``

.. _nt2_warning_as_error:
.. _nt2_warning_as_fatal:
.. _nt2_error_as_fatal:

Reports Upgrade
---------------

.. index::
  single: NT2_WARNING_AS_ERROR
  single: NT2_WARNING_AS_FAILURE
  single: NT2_ERROR_AS_FAILURE

Any reporting macro can be upgraded to the next level by using one of the following
symbol.

* ``NT2_WARNING_AS_ERROR``: If defined, all calls to :ref:`nt2_warning` will emit :ref:`errors`
* ``NT2_WARNING_AS_FAILURE``: If defined, all calls to :ref:`nt2_warning` will emit :ref:`failures`
* ``NT2_ERROR_AS_FAILURE``: If defined, all calls to :ref:`nt2_error` will emit :ref:`failures`

.. _nt2_error_as_warning:
.. _nt2_fatal_as_warning:
.. _nt2_fatal_as_error:

Reports Downgrade
-----------------

.. index::
  single: NT2_ERROR_AS_WARNING
  single: NT2_FAILURE_AS_WARNING
  single: NT2_FAILURE_AS_ERROR

Any reporting macro can be downgraded to the previous level by using one of the following
symbol.

* ``NT2_ERROR_AS_WARNING``: If defined, all calls to :ref:`nt2_error` will emit :ref:`warnings`
* ``NT2_FAILURE_AS_WARNING``: If defined, all calls to :ref:`nt2_failure` will emit :ref:`warnings`
* ``NT2_FAILURE_AS_ERROR``: If defined, all calls to :ref:`nt2_failure` will emit :ref:`errors`
