
Pre-existing Configuration Mode
===============================

.. rubric:: Description

As a convenience, some recurrent combination of error handling configuration settings
are gathered as a single, easy to use preprocessor symbol. The following table sum up
the effect of these pre-defined settings.

  +---------------------+----------+----------+----------+-------+
  | Preprocessor Symbol | Warning  | Error    | Fatal    | Notes |
  +=====================+==========+==========+==========+=======+
  | ``NT2_SILENT``      | Disabled | Disabled | Disabled |       |
  +---------------------+----------+----------+----------+-------+
  | ``NT2_RELEASE``     | Disabled | Disabled | Disabled |       |
  +---------------------+----------+----------+----------+-------+
  | ``NT2_PARANOID``    | Fatal    | Fatal    | Enabled  |       |
  +---------------------+----------+----------+----------+-------+
