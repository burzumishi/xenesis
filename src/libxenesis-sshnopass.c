#!@ENV@ perl

# @PACKAGE@-@VERSION@ (libxenesis-sshnopass.so) #

# This is free software;
# You have unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

# Xenesis SSH Library #

# libxenesis-sshnopass.so: SSH non interactive #

$^W = 1;  # enable warnings

use POSIX qw(:sys_wait_h setsid);
use Symbol;
use strict;

my $progname = $0;

sub start
{
  my $pid = fork;
  die "fork: $!" unless (defined $pid);
  if ($pid == 0) # child
    {
      # dissociate from controlling tty because openssh client will insist
      # on reading password from controlling tty if it has one.
      setsid ();
      local $^W = 0; # turn off duplicate warning from die
      exec (@_) || die "exec: $_[0]: $!\n\tDied";
    }
  return $pid;
}

sub exitstat
{
  my ($pid, $nowaitp) = @_;
  my $result = waitpid ($pid, ($nowaitp? WNOHANG : 0));
  return undef if (!defined $result || $result == -1);
  return WEXITSTATUS ($?) if WIFEXITED   ($?);
  return WTERMSIG    ($?) if WIFSIGNALED ($?);
  return WSTOPSIG    ($?) if WIFSTOPPED  ($?);
  return undef;
}

# These are not meant to be cryptographically secure; they are just meant
# to obfuscate sensitive data so they are not discovered accidentally.

sub scramble
{
  local $_ = shift;
  tr/[\x00-\x7f][\x80-\xff]/[\x80-\xff][\x00-\x7f]/; # rot128
  $_ = $_ ^ ("\xff" x length ($_));                  # invert bits
  s/(.)/sprintf "%02x", ord($1)/ego;                 # base16-encode
  return $_;
}

sub unscramble
{
  local $_ = shift;
  s/(..)/chr hex $1/ego;                             # base16-decode
  $_ = $_ ^ ("\xff" x length ($_));                  # invert bits
  tr/[\x00-\x7f][\x80-\xff]/[\x80-\xff][\x00-\x7f]/; # rot128
  return $_;
}

sub handle_subcall
{
  # We might be invoked to inquire whether or not to
  # connect to a host for which we have no stored key;
  # if that happens, inquire from user.
  if ($ARGV[0] =~ m|yes/no|o)
    {
      print STDERR $ARGV[0];
      my $ans = <STDIN>;
      print $ans;
      return;
    }

  print unscramble ($ENV{_ssp_data}), "\n";
}

sub pkill
{
  my ($sig, $pid) = @_;
  # subprocess is the session leader via setsid; signal whole session
  kill ($sig, -$pid);
}

sub main
{
  unless (@ARGV)
    {
      print STDERR "Usage: $0 [command {command args...}]\n";
      exit (1);
    }

  unless ($progname =~ m|^/|)
    {
      use Cwd;
      my $pwd = getcwd ();
      $progname =~ s|^|$pwd/|;
    }

  # In order to determine whether this script is being invoked by the user
  # or invoked recursively via ssh to fetch a password, we inspect several
  # conditions:
  #   * env var is set (containing password)
  #   * ssh_askpass env var is set to this program
  #   * 1 arg (a prompt) is passed from ssh client
  #   * output is not a tty
  #
  # If any of these conditions fail, we assume this is a primary invocation
  # and therefore query user for a password and launch a command.
  return handle_subcall ()
    if (exists $ENV{_ssp_data}
        && exists $ENV{SSH_ASKPASS}
        && $ENV{SSH_ASKPASS} eq $progname
        && @ARGV == 1
        && ! -t 1);

  # If display is not already set, we must set it now or ssh will not
  # invoke the askpass program.  Since we are performing a non-interactive
  # response we don't really need a display.  We use an invalid display
  # name to prevent any inadvertent grants of X access on remote hosts.
  $ENV{DISPLAY} = "none." unless exists $ENV{DISPLAY};
  $ENV{SSH_ASKPASS} = $progname;
  $ENV{_ssp_data} = scramble ("xxxxxxxxxx");

  my $pid = start (@ARGV);
  my $sighandler = sub { pkill ($_[0], $pid); };
  map { $SIG{$_} = $sighandler } qw(HUP INT QUIT TERM TSTP);
  exit (exitstat ($pid));
}

main ();

# ssh-pass ends here

