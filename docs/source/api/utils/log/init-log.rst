.. _game_log_init:

game_log_init
==================================

Use this function to set the logging mode and logging file.

Syntax
------
.. c:function:: void game_log_init(GAME_LOG_MODE log_mode, FILE* log_file)

Function Parameters
-------------------

:log_mode:		log initialisation mode; see :ref:`Remarks` for details
:log_file:		output file; see :ref:`Remarks` for details


Code Examples
-------------

.. code-block:: c

	#include "utils/log.h"

	#include <stdio.h>

	int main(int argc, char** argv)
	{
	#ifdef GAME_BUILD_MODE_RELEASE
		FILE* log_file = fopen("log.txt", "a"); 
		game_log_init((GAME_LOG_MODE)LOG_RELEASE, log_file);
	#else
		game_log_init((GAME_LOG_MODE)LOG_DEBUG, NULL);
	#endif
		
		GAME_LOG_INFO("%s", "Hello there!\n");

	#ifdef GAME_BUILD_MODE_RELEASE
		if (log_file != NULL) fclose(log_file);
	#endif

		return 0;
	}

Remarks
-------

Logging is default initialised with **log_mode = LOG_DEBUG** and **log_file = NULL**.

A value of **NULL** for **log_file** means logging output is forwarded to **stderr**.

**log_mode** can be any of the following:

:LOG_DEBUG: enables all logging methods
:LOG_RELEASE: enables only GAME_LOG_FATAL

Related Functions
-----------------

