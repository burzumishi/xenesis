#!@ENV@ bash

# @PACKAGE@-@VERSION@ (libxenesis-ral.c) #

# Copyright (c) 2014 Antonio Cao (@burzumishi) #

# This is free software;
# You have unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

# Xenesis RAL Library #

# libxenesis-ral.la: Remote Administration Layer functions and definitions #

ralfile_list_reset=0;

# ral_plugin_notfound($plugin): Send error message if a plugin was not found, always returns $false #
ral_plugin_notfound() {
    # Params: $plugin #
    plugin="$1"; shift;

    # If $plugin does not exist set it to "none" #
    if test -z "$plugin"; then plugin="none"; fi

	# RAL Plugin NOT found (create new ralfile??) #
	echolog "$ERROR Error! Plugin not fount: '$plugin'!";
	echolog "$ERROR Error! Perhaps you should check your spelling.";

	# If $plugin is "none" define a dummy plugin name, if not, show current param value #
	if test "$plugin" == "none"; then plugin="yournewplugin"; fi

	# Ask user for plugin creation #
	echolog "$WARNING Warning! Plugin does not exist! You can create a new one!";
	echolog "$WARNING Warning! Use: $EDITOR $PLUGINSDIR/${plugin}.ral"
	$ECHO;
	usage;

	return $false;
}

# check_ral_plugin($PLUGINS): check for an existent plugin #
check_ral_plugin() {
	# Params: $PLUGINS #
	PLUGINS="$1"; shift;

	if test ! -z "$PLUGINS"; then
		for plugin in $PLUGINS; do
			ralfile=$($FIND $PLUGINSDIR -iname "${plugin}.ral");

			if test ! -z "$ralfile"; then
				# RAL Plugin found (ralfile) #
				echolog "$OK Plugin found: '$ralfile'.";

				# Count RALFILES -> num_ralfile #
				num_ralfile=$((num_ralfile+1));

				# Fill $ralfile -> RALFILE_LIST #
				RALFILE_LIST="$ralfile $RALFILE_LIST";
			else
				# ERROR Forced: Plugin not found #
				ral_plugin_notfound "$plugin"; # returns $false #
				errorcheck $?;
			fi;	
		done

		# DEBUG $RALFILE_LIST #
		RALFILE_LIST=$($ECHO $RALFILE_LIST | sed -e 's/ $//g');
		echolog_debug "$DEBUG: Loaded #$num_ralfile ralfiles: '$RALFILE_LIST'";

		return $true;
	else
		# ERROR Forced: Plugin not found #
		ral_plugin_notfound "$PLUGINS"; # returns $false #
		errorcheck $?;
	fi;

}

# load_ral_plugin($ralfile_list,$host): Execute ralfile on host # TODO TODO TODO #
load_ral_plugin() {
	# Params: $ralfile_list, $host #
	ralfile_list="$1"; shift;
	host="$1"; shift;

	for ralfile in $ralfile_list; do
		# TODO TODO TODO #
		echolog "$OK Deploying '$ralfile' to '$host' ...";
		echolog "$OK Running '$ralfile' on '$host' ...";
		echolog "$OK Plugin status '$ralfile' on '$host': Finished!";
	done

	return $true;
}

# ral($ralfile_list,$hosts): Execute all remote administration scripts on hosts and get stdout #
ral() {
	# Params: $ralfile_list, $hosts #
	ralfile_list="$1"; shift;
	hosts="$1"; shift;

	# Create a valid list of hosts: $HOST_LIST #
	load_host_list "$hosts";
	errorcheck $?;

	# Check $HOST_LIST #
	check_host_list;
	errorcheck $?;

	# Load ralplugin on host_list #
	for h in $HOST_LIST; do
		load_ral_plugin "$ralfile_list" $h;
		errorcheck $?;
	done;
}

# start_ral($plugins,$hosts): Execute remote administration scripts on hosts and get stdout #
start_ral() {
	# Start Remote Admin Layer (RAL) Support # libxenesis-ral.so #

	# [option] PLUGIN: must be an existent "plugin name" #
	PLUGINS="$1"; shift;

	# [option] HOSTS: must be a valid "host" or "host_list" #
	HOSTS="$1"; shift;

	# [option] PLUGIN_PARAMS: should be a "plugin params list" # (OPTIONAL) #
	PLUGIN_PARAMS="$1"; shift;

	# Check for Remote Admin Layer (RAL) Plugin File #
	# PLUGIN -> export $RALFILE #
	check_ral_plugin "$PLUGINS";

	# If have Remote Admin Layer (RAL) Plugin file #
	# Load RAL Plugin on each host: "ral $RALFILE_LIST $HOSTS)" #
	ral "$RALFILE_LIST" "$HOSTS";
	errorcheck $?;
}
