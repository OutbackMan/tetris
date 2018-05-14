.. _init-log:

init_log
==================================

breif description

Syntax
------
GAME_STATUS game_log_init_logging(GAME_LOG_MODE log_mode, FILE* log_file)

Function Parameters
-------------------

==== ====
log_mode log initialisation mode; see Remarks for details
log_file output file
==== ====

Code Examples
-------------

Remarks
-------

==== ====
LOG_RELEASE release mode. will ignore GAME_LOG_INFO()
LOG_DEBUG debug mode (default).
==== ====

Related Functions
-----------------

