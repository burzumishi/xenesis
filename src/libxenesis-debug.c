#!@ENV@ bash

# @PACKAGE@-@VERSION@ (libxenesis-debug.c) #

# Copyright (c) 2014-2015 Antonio Cao (@burzumishi) #

# This is free software;
# You have unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

# Genetic Debug Library #

# libxenesis-debug.la: Core functions and definitions #

### -- '@PACKAGE@' environment debug -- ###

# debug_setup(): Debug @PACKAGE@ environment #
environment_debug() {
	# If @PACKAGE@ $ENABLEDEBUG && $ENABLEDEBUG_ENVIRONMENT are enabled, then show some setups #
	if test "$ENABLEDEBUG" == "yes" && test "$ENABLEDEBUG_ENVIRONMENT" == "yes"; then
		# Show @PACKAGE@ #
		echolog_debug "$DEBUG ================== %%% @PACKAGE@ %%% ==================";
		echolog_debug "$DEBUG This is '@PACKAGE@' with 'Environment Debug' enabled.";
		echolog_debug "$DEBUG Running on a '$HOST_OS' ($HOST_OS_VERSION) host platform '$HOST_PLATFORM/$HOST_CPU' and using '$BASH' ($BASH_VERSION) as interpreter with arguments: '$BASH_ARGV'.";
		echolog_debug "$DEBUG =====================================================";

		# Show COLOR values #
		if test "$COLOR" == "yes"; then
			echolog_debug "$DEBUG Color Support enabled!"
		else
			echolog_debug "$DEBUG Color Support disabled!"
		fi;

		# Show $ENABLELOG values: yes|no #
		if test "$ENABLELOG" == "yes"; then
			echolog_debug "$DEBUG Main '@PACKAGE@' log file is enabled: '$LOGFILE'.";
		else
			echolog_debug "$DEBUG Main '@PACKAGE@' log file is disabled!";
		fi;

		# Show $ENABLEDEBUG value: yes|no #
		if test "$ENABLEDEBUG" == "yes"; then
			echolog_debug "$DEBUG Debug '@PACKAGE@' log file is enabled: '$DEBUGLOGFILE'.";
		else
			echolog_debug "$DEBUG Debug '@PACKAGE@' log file is disabled!";
		fi;

		# Show $ENABLE_VERBOSE value: yes|no #
		echolog_debug "$DEBUG Verbose '@PACKAGE@' screen output: '$ENABLE_VERBOSE'.";

		# Show $ENABLE_Force value: yes|no #
		if test "$ENABLE_FORCE" == "yes"; then
			echolog_debug "$DEBUG Running '@PACKAGE@' with '-f' or '--force' option enabled!!!"
			echolog_debug "$DEBUG Forcing all 'errorcheck' and 'spinner' functions to end always with an exit '$true' status!";
		else
			echolog_debug "$DEBUG Disabled forcing all 'errorcheck' and 'spinner' functions to end always with an exit '$true' status.";
		fi;
 
		# Show $DATEFORMAT $LOGDATE #
		echolog_debug "$DEBUG All '@PACKAGE@' log files are using '[$DATEFORMAT]'.";

		echolog_debug "$DEBUG =====================================================";
	fi;
}
