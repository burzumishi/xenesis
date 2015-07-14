#!@ENV@ bash

# @PACKAGE@-@VERSION@ (libxenesis.c) #

# Copyright (c) 2014-2015 Antonio Cao (@burzumishi) #

# This is free software;
# You have unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

# Genetic Core Library #

# libxenesis.la: Core functions and definitions #

### --- Define '@PACKAGE@' Core functions --- ###

### -- '@PACKAGE@' main function -- ###

# main($@): Start @PACKAGE@ #
main() {

	# Load '@PACKAGE@' core variables #
	load_core_variables;

	# Trap '@PACKAGE@' process 'SIGINT' 'SIGQUIT' 'SIGTERM' 'SIGKILL' will call _manage_system_int()_ function and exit '@PACKAGE@' instance safely #
	trap_system_int;

	# Start '@PACKAGE@' process main loop #
	while :
	do
		# Read '@PACKAGE@' user keyboard input (wait for 'SIGINT', 'SIGKILL', 'SIGQUIT' & 'SIGTERM') #
		read user_keyboard_input &

		echolog_debug "$DEBUG ================== %%% @PACKAGE@ %%% ==================";
		echolog_debug "$DEBUG Start trapping '@PACKAGE@' process user keyboard input.";
		echolog_debug "$DEBUG =====================================================";

		# Check @PACKAGE@ directory structure. These dirs are needed for @PACKAGE@ to work properly #
		check_directory_structure "$LOCKDIR $TMPDIR $PLUGINSDIR $HOSTSDIR $SSHHOSTSDIR";

		# Lock @PACKAGE@ instance #
		lock_instance;

		# Check @PACKAGE@ Operating System #
		check_os;

		# Setup @PACKAGE@ Terminal #
		setup_term_environment;

		# Display @PACKAGE@ $STARTMSG_PACK #
		startmsg;

		# Check current user (@PACKAGE@ needs superuser privileges) #
		check_user;

		# Debug @PACKAGE@ environment #
		environment_debug;

		### Get and parse @PACKAGE@ Command Line Actions & Options ###

		# Empty Command Line parameter displays help #
		if test -z "$*"; then
			help;
		else
			# Define $ACTION_OPTIONS #
			ACTION_OPTIONS=$($GETOPT -o hvU:H:O:p:T:c: \
				 -l "help,version,verbose,force,color,sshconf,user:,hosts:,plugopts:,plugin:,test:,command:" \
				 -n "$0" -- "$@");

			eval set -- "$ACTION_OPTIONS"

			# Case $ACTION_OPTIONS #
			while :
			do
				case "$1" in
					--color) # Switch @PACKAGE@ output <color>, already in config files #
						if test "$ENABLE_COLOR" == "yes"; then
							ENABLE_COLOR="no";
						else
							ENABLE_COLOR="yes";
						fi;
						load_terminal_color_support;
						shift;
					;;

					-h|--help) # <help> @PACKAGE@ help #
						help; shift; break;
					;;

					-v|--version) # Show @PACKAGE@ version #
						if test "$ENABLE_VERSION" == "yes"; then
							ENABLE_VERSION="yes";
						else
							ENABLE_VERSION="yes";
							startmsg;
						fi;
						shift; break;
					;;

					--verbose) # <verbose> @PACKAGE@ output #
						ENABLE_VERBOSE="yes"; shift;
					;;

					--force) # <force> @PACKAGE@ action #
						ENABLE_FORCE="yes"; shift;
					;;

					# libxenesis-ral.so -- options -- #
					-U|--user) # Working SSH User #
						SSHUSER="$2"; shift 2;
					;;

					-H|--hosts) # Working <$HOST_LIST> file or servers #
						HOST_LIST="$2"; shift 2;
					;;

					-O|--plugopts) # Loaded <$PLUGIN_OPTIONS> # 
						PLUGIN_OPTIONS="$2"; shift 2;
					;;

					# libxenesis-ral.so -- actions -- #
					-p|--plugin) # start_ral: "$2 == $PLUGINS", "$3 == $HOST_LIST", "$4 == $PLUGIN_OPTIONS" #
						RALPLUGIN="$2"; shift 2;
						start_ral "$RALPLUGIN" "$HOST_LIST" "$PLUGIN_OPTIONS";
					;;

					-T|--test) # start_ral_test: "$2 == $PLUGINS", "$3 == $HOST_LIST", "$4 == $PLUGIN_OPTIONS" #
						RALPLUGIN="$2"; shift 2;
						start_ral_test "$RALPLUGIN" "$HOST_LIST" "$PLUGIN_OPTIONS";
					;;

					# libxenesis-ssh.so -- actions -- #
					-c|--command) # exec_ssh_cmd: "$2 == $cmd", "$3 == $HOST_LIST" #
						cmd="$2"; shift 2;
						exec_ssh_cmd "$cmd" "$HOST_LIST";
					;;
					
					--sshconf) # configure_ssh: "$2 == $HOST_LIST" #
						configure_ssh "$HOST_LIST"; shift; break;
					;;

				 	--) shift; break;
					;;

					-*) # Unknown option (show '@PACKAGE@' help) #
						help; shift; break;
					;;

					*) # Unknown option (show '@PACKAGE@' help) #
						help; shift; break;
					;;
				esac;
			done;
		fi;

		# Close @PACKAGE@ instance #
		exit_instance $true;
	done;

	# End '@PACKAGE' program main loop #
}

### -- '@PACKAGE@' OS funtions ###

# trap_system_int(): Trap '@PACKAGE@' process 'SIGINT' 'SIGQUIT' 'SIGTERM' 'SIGKILL' will call _manage_system_int()_ function and exit '@PACKAGE@' instance safely #
trap_system_int() {
	$TRAP "manage_system_int" SIGINT SIGQUIT SIGTERM SIGKILL
}

# manage_system_int(): Manage '@PACKAGE@' process trapped system interruptions #
manage_system_int() {
	# Manage '@PACKAGE@' process system INTs #
  echolog "$ERROR Error! Process '@PACKAGE@' (PID: $$) received an interrupt!";
	echolog "$ERROR Closing '@PACKAGE@' now! Goodbye!";

	echolog_debug "$DEBUG ================= %%% @PACKAGE@ %%% ================";
	echolog_debug "$DEBUG Error! Process (PID: $$) received an interrupt!";
	echolog_debug "$DEBUG ==================================================";

	# Close @PACKAGE@ instance #
	exit_instance $false;
}

# lock_instance(): Lock @PACKAGE@ instance #
lock_instance() {
	# Create $LOCKDIR if not found #
	if test ! -d "$LOCKDIR"; then $MKDIR -p $LOCKDIR &>/dev/null; fi;

	# Check '@PACKAGE@' instance locks #
	if test ! -f "$LOCKFILE"; then
		# '@PACKAGE@' $LOCKFILE not found #
		echolog_debug "$DEBUG Process '@PACKAGE@' (PID: $$) unlocked, creating '$LOCKFILE'!";

		# Create '@PACKAGE@' $LOCKFILE #
		$TOUCH $LOCKFILE;

		echolog_debug "$DEBUG Process '@PACKAGE@' (PID: $$) locked!";

		return $true;
	else
		# '@PACKAGE@' $LOCKFILE found #
		echolog_debug "$DEBUG Process '@PACKAGE@' '$LOCKFILE' found!"
		echolog "$WARNING Warning! Process '@PACKAGE@' '$LOCKFILE' found!"

		instance_PID=$($PIDOF @PACKAGE@);

		if test -z "$instance_PID"; then
			echolog_debug "$DEBUG Error! A '@PACKAGE@' process instance (PID: $instance_PID) is already running!";

			echolog "$ERROR Error! A '@PACKAGE@' process instance (PID: $instance_PID) is already running!";

			# Close '@PACKAGE@' instance #
			exit_instance $false;
		fi;
	fi;

	return $true;
}

# unlock_instance(): Unlock @PACKAGE@ instance #
unlock_instance() {
	# Create $LOCKDIR if not found #
	if test ! -d "$LOCKDIR"; then $MKDIR -p $LOCKDIR &>/dev/null; fi;

	if test -f "$LOCKFILE"; then
		# '@PACKAGE@' $LOCKFILE found #
		echolog_debug "$DEBUG Process '@PACKAGE@' (PID: $$) locked, deleting '$LOCKFILE'!";

		# Delete '@PACKAGE@' $LOCKFILE #
		$RM -f $LOCKFILE;

		echolog_debug "$DEBUG Process '@PACKAGE@' (PID: $$) unlocked!";
	else
		# '@PACKAGE@' $LOCKFILE not found #
		echolog_debug "$DEBUG Process '@PACKAGE@' (PID: $$) not locked!";
	fi;
}

# exit_instance($exit_val): Close @PACKAGE@ instance #
exit_instance() {
	# Params: $exit_val #
	exit_val=$1; shift;

	# Unlock '@PACKAGE@' instance #
	unlock_instance;

	# Reset terminal environment #
	reset_term_environment;

	if test -z "$!"; then
		echolog_debug "$DEBUG Process '@PACKAGE@' function _(exit_instance)_ detected subprocess (PID: $!)!"
	else
		echolog_debug "$DEBUG No '@PACKAGE@' subprocess (PID) detected!"
	fi

	if test $exit_val -ne 0; then
		echolog "$ERROR Error! Process '@PACKAGE@' (PID: $$) terminated _(Err: $exit_val)_ check errors!";
		exit $exit_val ;
	else
		echolog_debug "$DEBUG Process '@PACKAGE@' (PID: $$) terminated _(Err: $exit_val)_ Goodbye!";
		exit $true;
	fi;
}

# check_os(): Check Operating System (GNU/Linux | BSD | CygWin). #
# NOTE: If you plan to port @PACKAGE@ to other OS different than Linux, you will need to modify this function. #
check_os() {
	case "$HOST_SYSTEM" in
		Linux|LINUX|linux) HOST_SYSTEM="linux";
			# Import Linux config files #
			source @sysconfdir@/@PACKAGE@/os/linux.conf;
			source @sysconfdir@/@PACKAGE@/os/commands/linux.conf;
			return $true;
		;;

		*BSD|*bsd) HOST_SYSTEM="bsd";
			# Import BSD config files #
			source @sysconfdir@/@PACKAGE@/os/freebsd.conf;
			source @sysconfdir@/@PACKAGE@/os/commands/freebsd.conf;
			return $true;
		;;

		*hp-ux*|*HP-UX*) HOST_SYSTEM="hpux";
			# Import HP-UX config files #
			source @sysconfdir@/@PACKAGE@/os/hpux.conf; # TODO TODO TODO #
			source @sysconfdir@/@PACKAGE@/os/commands/hpux.conf; # TODO TODO TODO #
			return $true;
		;;

		cygwin*|CygWin*|CYGWIN*|Cygwin*) HOST_SYSTEM="cygwin";
			# Import CygWin config files #
			source @sysconfdir@/@PACKAGE@/os/cygwin.conf; # TODO TODO TODO #
			source @sysconfdir@/@PACKAGE@/os/commands/cygwin.conf; # TODO TODO TODO #
			return $true;
		;;

		*) # '$HOST_SYSTEM' not supported #
			echolog "$ERROR Error! '@PACKAGE@' cannot run on '$HOST_SYSTEM'!";

			# Close @PACKAGE@ instance #
			exit_instance $false;
		;;
	esac;

	echolog_debug_verbose "$DEBUG '@PACKAGE@' running on '$HOST_SYSTEM'!";
	return true;
}

# setup_term_environment(): Setting up terminal environment #
setup_term_environment() {
	if test "$HOST_SYSTEM" != "cygwin"; then
		echolog_debug_verbose "$DEBUG Setting up ($HOST_OS) terminal environment.";

		# Terminal Cursor off
		$SETTERM -cursor off;
	else
		echolog_debug_verbose "$DEBUG Warning! Running on '$HOST_SYSTEM' can't use '$SETTERM'!";
	fi;

	return $true;
}

# reset_term_environment(): Resetting up terminal environment #
reset_term_environment() {
  if test "$HOST_SYSTEM" != "cygwin"; then
		echolog_debug_verbose "$DEBUG Resetting up ($HOST_OS) terminal environment.";

		# Terminal Cursor on
		$SETTERM -cursor on;

		# Terminal Default Settings
		$SETTERM -default;

		# unset CFLAGS & CXXFLAGS #
		unset CFLAGS CXXFLAGS;
  else
    echolog_debug_verbose "$DEBUG Warning! Running on '$HOST_SYSTEM' can't use '$SETTERM'!";
  fi;

	return $true;
}

# check_user(): check superuser #
check_user() {
	if test "$HOST_SYSTEM" != "cygwin"; then
		if test "$USER" != "root"; then
			$ECHO;
			echolog "$WARNING Warning! You are not superuser ($USER)!";
			echolog "$ERROR Error! That's not good! '@PACKAGE@' needs to be run as (root)!";
			$ECHO;

			# Close @PACKAGE@ instance #
			exit_instance $false;
		else
			echolog_debug_verbose "$DEBUG Good! Process '@PACKAGE@' with (PID: $$) is running as superuser ($USER)."
		fi;
  else
    echolog_debug_verbose "$DEBUG Warning! Running on '$HOST_SYSTEM' can't be 'root'!";
  fi;

	return $true;
}

# errorcheck($error, $function): check for errors, if $false will exit (1) #
errorcheck() {
	# Params: $error, $function #
  error=$1; shift;
	function=$1; shift;

  if test $error -ne $true; then
		# Check if $function is defined else define 'unknown' #
		if test -z "$function"; then function="unknown"; fi;

      echolog_debug "$ERROR Error! '@PACKAGE@' function _($function)_ exited _(Err: $error)_!";
      echolog "$ERROR Error! '@PACKAGE@' function _($function)_ exited _(Err: $error)_!";

		if test "$ENABLE_FORCE" == "yes"; then
      echolog_debug "$ERROR Error! Override error because user is using '-f' or '--force' enabled option!";
      echolog "$ERROR Error! Override error because user is using '-f' or '--force' enabled option!";

			return $true;
		else
			# Close @PACKAGE@ instance #
			exit_instance $false;
		fi;
  else
    return $true;
  fi;
}

# check_file($FILE,$FILECMD): check if $FILE exists, if $true execute $FILECMD if requested #
check_file() {
	# Params: $FILE $FILECMD #
	FILE="$1"; shift;
	FILECMD="$1"; shift; # (optional) #

	# Test $FILE #
  if test ! -f "$FILE"; then
    echolog_debug "$DEBUG Warning! Requested file '$FILE' was not found!";

		# Define $XENESIS_LAST_ERROR to be displayed in _(errorcheck)_ #
		XENESIS_LAST_ERROR="$WARNING Warning! Requested file '$FILE' was not found!";

		return $false;
	else
		echolog_debug "$DEBUG Requested file '$FILE' exists.";

		# If $FILECMD is passed, then execute $FILECMD #
		if test ! -z "$FILECMD"; then
			echolog_debug "$DEBUG Function _(check_file)_ executing: '$FILECMD'";
			$FILECMD &>/dev/null;
		fi;

		return $true;
  fi;
}

# check_dir($DIR,$DIRCMD): check if $DIR exists, if $true execute $DIRCMD if requested #
check_dir() {
	# Params: $DIR $DIRCMD #
	DIR="$1"; shift;
	DIRCMD="$1"; shift; # (optional) #

	# Test $DIR #
        if test ! -d "$DIR"; then
                echolog_debug "$DEBUG Warning! Requested directory '$DIR' was not found!";

		# Define $XENESIS_LAST_ERROR to be displayed in _(errorcheck)_ #
		XENESIS_LAST_ERROR="$WARNING Warning! Requested directory '$DIR' was not found!";

		return $false;
	else
		echolog_debug "$DEBUG Requested directory '$DIR' exists.";

		# If $DIRCMD is passed, then execute $DIRCMD #
		if test ! -z "$DIRCMD"; then
			echolog_debug "$DEBUG Function _(check_dir)_ executing: '$DIRCMD'";
			$DIRCMD &>/dev/null;
		fi;
		return $true;
        fi;
}

# check_link($LINK,$LINKCMD): check if file $LINK exists, if $true execute $LINKCMD if requested #
check_link() {
	# Params: $LINK $LINKCMD #
	LINK="$1"; shift;
	LINKCMD="$1"; shift; # (optional) #

	# Test $LINK #
  if test ! -L "$LINK"; then
    echolog_debug "$DEBUG Warning! Requested file link '$LINK' was not found!";

		# Define $XENESIS_LAST_ERROR to be displayed in _(errorcheck)_ #
		XENESIS_LAST_ERROR="$WARNING Warning! Requested file link '$LINK' was not found!";

		return $false;
	else
		echolog_debug "$DEBUG Requested file link '$LINK' exists.";

		# If $LINKCMD is passed, then execute $FILECMD #
		if test ! -z "$LINKCMD"; then
			echolog_debug "$DEBUG Function _(check_link)_executing: '$LINKCMD'";
			$LINKCMD &>/dev/null;
		fi;

		return $true;
  fi;
}

# check_directory_structure($directories): check and create directory #
check_directory_structure() {
	# Params: $directories #
	directories="$1"; shift;

	echolog_debug "$DEBUG ================== %%% @PACKAGE@ %%% ==================";
	echolog_debug "$DEBUG Starting 'check_directory_structure($directories)'!";
	echolog_debug "$DEBUG =====================================================";

	# Create required '@PACKAGE' directories #
	for dir in $directories; do
		# Create $dir if not found #
	  	if test ! -d "$dir"; then
	    	echolog_debug_verbose "$DEBUG Warning! Requested directory '$dir' was not found!";
			
			$MKDIR -p $dir $>/dev/null;

			echolog_debug_verbose "$DEBUG Warning! Requested directory '$dir' has been created!";
		else
			echolog_debug_verbose "$DEBUG Requested directory '$dir' was found!";
		fi;
	done;
	
	return $true;
}

# new_work_spinner($SPINNER_CMD,$SPINNER_MSG|$SPINNER_EXIT_STATUS,$new_work_spinner_pid): Working spinner #
new_work_spinner() {
	# $1 start/stop
	#
	# on start: $2 display message
	# on stop : $2 process exit status
	#           $3 spinner function pid (supplied from stop_spinner)

	case $1 in
		start)
			new_spinner_count=1;
			SPINNER_DELAY=0.15;

			# Display SPINNER #
			echolog_debug "$DEBUG ================ %%% '@PACKAGE@' work_spinner %%% ===============";
			echolog_debug "$DEBUG Start: '$SPINNER_MSG'.";

			while :
			do
				case $new_spinner_count in
					1) $ECHO -ne "\\r$SPIN1 $SPINNER_MSG     ";
		       	 new_spinner_count=$((new_spinner_count+1));
					;;
					2) $ECHO -ne "\\r$SPIN2 $SPINNER_MSG .   ";
				     new_spinner_count=$((new_spinner_count+1));
				  ;;
					3) $ECHO -ne "\\r$SPIN3 $SPINNER_MSG ..  ";
				     new_spinner_count=$((new_spinner_count+1));
				  ;;
					4) $ECHO -ne "\\r$SPIN4 $SPINNER_MSG ... ";
				     new_spinner_count=1;
				  ;;
			  esac;

				$SLEEP $SPINNER_DELAY;
		  done

			return $true;
		;;
		stop)
			if test -z $new_work_spinner_pid; then
				echolog_debug "$DEBUG Stop: was requested, but it's not running!";
				return $true;
			else
				echologn_debug "$DEBUG Stop: (PID: $new_work_spinner_pid) stopping ...";
				$KILL $new_work_spinner_pid &> /dev/null;

				# inform the user uppon success or failure
				if test $SPINNER_EXIT_STATUS -eq 0; then
					echolog_debug_nodate "$FINISHED";
					echolog_debug "$DEBUG =====================================================";

					$ECHO -e "$FINISHED";
					return $true;
				else
					echolog_debug_nodate "$FAILED";
					echolog_debug "$DEBUG =====================================================";

					$ECHO -e "$FAILED";
					exit_instance $false;
				fi;
			fi;
		;;
		*)  echolog_debug "$DEBUG Called 'new_work_spinner' with an invalid argument, try {start_spinner|stop_spinner}!";
		    exit_instance $false;
		;;
	esac;

	return $true;
}

# new_work_spinner($SPINNER_MSG): Starts working spinner #
start_spinner() {
	SPINNER_MSG="$1"; shift;

	# Load spinner #
	new_work_spinner "start" "$SPINNER_MSG" &

	# set global work_spinner pid #
	new_work_spinner_pid=$!;

	disown;

	# Prevent running actions before spinner #
	sleep 0.5;
}

# new_work_spinner($SPINNER_EXIT_STATUS): Stops working spinner #
stop_spinner() {
	SPINNER_EXIT_STATUS=$1; shift;

	# Prevent finishing actions before spinner #
	sleep 0.5;

	# If force is used set SPINNER_EXIT_STATUS to $true #
	if test "$ENABLE_FORCE" == "yes"; then
		SPINNER_EXIT_STATUS=$true;
	fi;

	# Load spinner #
  new_work_spinner "stop" $SPINNER_EXIT_STATUS $new_work_spinner_pid;

	# unset global work_spinner vars #
	unset new_work_spinner_pid;
	unset SPINNER_EXIT_STATUS;
	unset SPINNER_MSG;
}


### -- '@PACKAGE@' screen display and input functions -- ###
 
# continue_promt: Ask user to continue or not #
continue_promt() {
	echolog_debug "$DEBUG [ Continue? (y/n) ] Display user input prompt and wait for an answer!";

	# Display Continue Question #
	echolog "$QUESTION Do you want to continue? (y/n): ";

	# Read user input (y/n) #
	read input
	case $input in
	     [Yy]*) ;;                      # "Yes", let's go! Continue! #
	     [Nn]*) exit_instance $false ;; # "No" Call _(exit_instance)_ and exit '@PACKAGE' now! #
	     *) echolog "$QUESTION Do you want to continue? (y/n): " ;; # "Retry!" _(y/n)_ Retry again!? #
	esac;

	return $true;
}

# show_version(): display '@PACKAGE@' version #
show_version() {
	$ECHO "$@PACKAGE@_VERSION";
}

# startmsg(): display start message to user #
startmsg() {

	# Debug always displays $starmsg #
	echolog_debug "$DEBUG ================== %%% @PACKAGE@ %%% ==================";
	echolog_debug "$DEBUG $@PACKAGE@_VERSION";
	echolog_debug "$DEBUG =====================================================";

	if test "$ENABLE_VERSION" == "yes"; then
		# Display '@PACKAGE@' start message '$@PACKAGE@_VERSION' #
		echolog_debug "$DEBUG Display '@PACKAGE@' start message.";

		# Show '@PACKAGE@' version #
		show_version;
	else
		# Display '@PACKAGE@' start message '$@PACKAGE@_VERSION' is disabled #
		echolog_debug "$DEBUG Display '@PACKAGE@' start message is disabled!";
	fi;

	# Warn user about --force or -f #
	if test "$ENABLE_FORCE" == "yes"; then
		echolog "$WARNING! Warning! Running '@PACKAGE@' with '-f' or '--force' option enabled!!!"
		echolog "$WARNING! Warning! Forcing all 'errorcheck' and 'spinner' functions to end always with an exit '$true' status!";
	fi;

	return $true;
}

# help(): command line help #
help() {
	$ECHO;
	$ECHO "$HELP";
	$ECHO;

	# Close @PACKAGE@ instance #
	exit_instance $true;
}

