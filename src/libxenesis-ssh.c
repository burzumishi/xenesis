#!@ENV@ bash

# @PACKAGE@-@VERSION@ (libxenesis-ssh.c) #

# Copyright (c) 2014-2015 Antonio Cao (@burzumishi) #

# This is free software;
# You have unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

# Xenesis SSH Library #

# libxenesis-ssh.la: SSH functions and definitions #

# check_rsa: Check for RSA key file #
check_rsa() {
	if test ! -f "$SSH_ID_RSA"; then
		# Generate a new RSA key #
		ssh-keygen -t rsa;
		errorcheck $?;
	else
		# $SSH_ID_RSA key file found #
       	echolog_debug "$OK Have a '$SSH_ID_RSA' key file."
		return $true;
	fi;
}

# check_ssh($host): Check SSH host reply #
check_ssh() {

	host="$1"; shift;

    # TEST_SSH on $host #
    TEST_SSH=$(@libdir@/libxenesis-sshnopass.la $BASH -c "$SSHCMD -o StrictHostKeyChecking=no $SSHUSER@${host} $LS 2>&1");

    if test ! -z "$($ECHO $TEST_SSH | $GREP disconnect)"; then
		# ERROR: Host cant be accesed with SSH and $SSHUSER.
	    echolog "$ERROR Error! '$host' can't be accessed with 'SSH' by '$SSHUSER'.";
		echolog "$WARNING Warning! Configure 'SSH' access for '${SSHUSER}@${host}' with '--sshconf' option.";

		# If a database file exists we should delete it.
		if test -f "$SSHHOSTSDIR/${host}_${SSHUSER}"; then $RM -f $SSHHOSTSDIR/${host}_${SSHUSER}; fi

		# Show Help
		$ECHO
		help;

	    return $false;
    else
		# Record host to database #
       	echolog "$OK Host '$host' has 'SSH' access for '$SSHUSER'."

		# Create file record $host_$SSHUSER #
		$TOUCH $SSHHOSTSDIR/${host}_${SSHUSER};

		return $true;
    fi;
}

# check_ssh($host): Configure SSH for hosts in $HOST_LIST #
configure_ssh() {

	hosts="$1"; shift;

	# Create a valid list of hosts: $HOST_LIST #
	load_host_list "$hosts";
	errorcheck $?;

	# Check $HOST_LIST #
	check_host_list;
	errorcheck $?;

	# Check for RSA key file #
	check_rsa;
	errorcheck $?;

	# Check SSH connection on all $host from $HOST_LIST #
	for host in $HOST_LIST; do 
		echolog "$OK Configure 'SSH' on '$host' ...";

	   	# Check user environment variables #
	    USER_ENV=$($SSHCMD ${SSHUSER}@${host} $ENV);
		USER_HOME=$(echo "$USER_ENV" | grep "^HOME=");
		errorcheck $?;

	   	# Check $USERHOME/$SSHDIR directory existence, if not create it #
	    $SSHCMD ${SSHUSER}@${host} "if test ! -d \"$USER_HOME/$SSHDIR\"; then $MKDIR -pv $USERHOME/$SSHDIR; fi";
		errorcheck $?;

	    # Change $USERHOME/$SSHDIR directory permissions #
	    $SSHCMD ${SSHUSER}@${host} "$CHMOD 700 $USERHOME/$SSHDIR";
		errorcheck $?;

		# Copy $SSH_ID_RSA key to $host #
	    $SCPCMD $SSH_ID_RSA ${SSHUSER}@${host}:$USERHOME/$SSHDIR/;
		errorcheck $?;

	    # Check for a valid $SSH_AUTH_KEYS file #
	    $SSHCMD ${SSHUSER}@${host} "if test ! -e \"$SSH_AUTH_KEYS\"; then $TOUCH $SSH_AUTH_KEYS; fi";
		errorcheck $?;

	    # Change $SSH_AUTH_KEYS file permissions #
	    $SSHCMD ${SSHUSER}@${host} "$CHMOD 600 $SSH_AUTH_KEYS";
		errorcheck $?;

		# Add $SSH_ID_RSA to $SSH_AUTH_KEYS #
	    $SSHCMD ${SSHUSER}@${host} "$CAT $SSH_ID_RSA >> $SSH_AUTH_KEYS";
		errorcheck $?;

		# Test $SSH_ID_RSA #
	    $SSHCMD ${SSHUSER}@${host} "$LS -l $SSH_ID_RSA";
		errorcheck $?;

	    echolog "$OK Setup SSH for '${SSHUSER}@${host}' finished.";
	done;

	# Check SSH access #
	check_ssh $host;
	errorcheck $?;

	return $true;
}

# exec_ssh_cmd($cmd, $hosts): Execute Command for $host in $HOST_LIST #
exec_ssh_cmd() {
	cmd="$1"; shift;
	hosts="$1"; shift;

	# Create a valid list of hosts: $HOST_LIST #
	load_host_list "$hosts";
	errorcheck $?;

	# Check $HOST_LIST #
	check_host_list;
	errorcheck $?;

	# Execute SSH Command on $host #
	for host in $HOST_LIST; do
		# Check SSH access #
		check_ssh $host;
		errorcheck $?;

		echolog "$OK Running: '$SSHCMD ${SSHUSER}@${host} $cmd'.";
		$SSHCMD ${SSHUSER}@${host} $cmd;
	done;
}
