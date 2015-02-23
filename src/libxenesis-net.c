#!@ENV@ bash

# @PACKAGE@-@VERSION@ (libxenesis-net.c) #

# Copyright (c) 2014-2015 Antonio Cao (@burzumishi) #

# This is free software;
# You have unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

# Xenesis NET Library #

# libxenesis-net.la: Basic Network functions and definitions #

num_host=0;
host_list_reset=0;

# check_ping($host): check host ping reply #
check_ping() {

	host="$1"; shift;

    # CHECK PING #
    $PING $host >/dev/null;

	if [[ $? -ne $true ]]; then		
		echolog "$WARNING! [$host] does not reply to \"ping\" requests.";
        	return $false;
    else
        	echolog "$OK! [$host] replies to \"ping\" requests.";
        	return $true;
    fi;
}

# check_dns($host): check host DNS reply #
check_dns() {

	host="$1"; shift;

    # CHECK DNS #
    $HOSTCMD $host >/dev/null;

	if [[ $? -ne $true ]]; then		
		echolog "$WARNING! [$host] does not reply to \"DNS\" requests.";
        	return $false;
    else
        	echolog "$OK! [$host] replies to \"DNS\" requests.";
        	return $true;
    fi;
}

# addto_host_list($error,$host): add verified hosts to $HOST_LIST # 
addto_host_list() {
	error=$1; shift;
	host="$1"; shift;

	# If there are no errors add host to list #
	if [[ $error -eq $true ]]; then
		# Check if $host is already on $HOST_LIST #
		TEST_HOST_LIST=$(echo $HOST_LIST | grep $host);
		if [ -z "$TEST_HOST_LIST" ]; then
			HOST_LIST="$host $HOST_LIST"
			echolog "$OK! [$host] added to \"host_list\"!";
		else
			# WARNING! Nothing to do! Skipping $host! #
			echolog_debug "$DEBUG: Nothing to do! [$host] already listed!";		
		fi;
	else
		# WARNING! Nothing to do! Skipping $host! #
		echolog "$WARNING! Nothing to do! Skipping [$host]!";
		# Skip this host $host #
		HOST_LIST=$($ECHO $HOST_LIST | $SED -e 's/'$host'//g');
	fi;
}

# load_host_list($HOSTS): check hosts and create a valid host_list -> $HOST_LIST # 

# At first check if it's a HOST_LIST file #
# Load all hosts from file, then check DNS and PING #
# If it's not a file, it's a real host, then check DNS and PING #

load_host_list() {
	# Params: $HOSTS #
	HOSTS="$1"; shift;

	# $HOSTS cannot be empty #
	if test ! -z "$HOSTS"; then
		# Host || Host List count #
		for h in $HOSTS; do
			# Count HOSTS -> num_host #
			num_host=$((num_host+1));
			# Fill $h -> HOST_LIST #
			HOST_LIST="$h $HOST_LIST";
		done;

		# Clean white spaces at end of the list #
		HOST_LIST=$($ECHO $HOST_LIST | $SED -e 's/ $//g');
		echolog_debug "$DEBUG: Loaded [#$num_host] hosts or \"host_list\" files: $HOST_LIST";

		# Check all host in $HOST_LIST #
		for host in $HOST_LIST; do
			# check host dns $hosts; #
			check_dns $host;
			if test $? -eq 0; then
				echolog_debug "$DEBUG: DNS discovered host name for [$host]!";

				# Single host or host_list #
				# check host ping $host #
				check_ping $host;

				# add to host list $error $host #
				addto_host_list $? $host;
			else
				# If host does NOT have DNS #
				# Maybe it's a 'hostslist' in '$HOSTSDIR' #
				# check host list $host; # (cat $HOSTSDIR/$hosts) #
				CHECK_HOST_LIST=$($FIND $HOSTSDIR -iname "$host" -exec $BASH {} \;);
				if test ! -z "$CHECK_HOST_LIST"; then
					echolog "$OK! Found [$host] \"host_list \" file with the following hosts: $CHECK_HOST_LIST";
					# Reset HOST_LIST #
					# Load list with hostnames instead of host_list #
					# First time loop runs, we need to reset host_list names from HOST_LIST #
					if test $host_list_reset -eq 0; then
						HOST_LIST="";
						host_list_reset=1;
					fi;
					# Reload HOST_LIST from current host_list file #
					for hf in $CHECK_HOST_LIST; do
						# check host dns $hf; #
						check_dns $hf;
						if test $? -eq 0; then
							echolog_debug "$DEBUG: DNS discovered host name for [$hf]!";

							# Ping $hf
							check_ping $hf;
							# add to host list $error $hf #
							addto_host_list $? $hf;
						else
							# WARNING! Host is in NOT DNS #
							# WARNING! Nothing to do! #
							echolog "$WARNING! [$hf] does not have a DNS name.";
							# Ping $hf
							check_ping $hf;

							# add to host list $error $hf #
							addto_host_list $? $hf;
						fi;
					done;
				else
					# Param is not a host or a host_list #
					echolog "$WARNING! [$host] is not a \"host_list\"!";

					# Ping $host
					check_ping $host;

					# add to host list $error $hf #
					addto_host_list $? $host;

					return $true;
				fi;
			fi;
		done;
	else
		$ECHO
		echolog "$ERROR! \"host\" or \"host_list\" is needed!";
		$ECHO
		help;
		return $false;
	fi;
}


# check_host_list(): checks avaliable hosts from $HOST_LIST created by load_host_list() #
check_host_list() {
	# Check $HOST_LIST #
	if test ! -z "$HOST_LIST"; then
		# Host count #
		avaliable_hosts=0;
		for h in $HOST_LIST; do
			# Count HOSTS -> avaliable_hosts #
			avaliable_hosts=$((avaliable_hosts+1));
		done;

		# Show avaliable $HOST_LIST #
		echolog "$OK! Found [#$avaliable_hosts] avaliable hosts: $HOST_LIST";
		return $true;
	else
		# There are any host avaliable #
		echolog "$ERROR! No hosts avaliable!";
		return $false;
	fi;
}

