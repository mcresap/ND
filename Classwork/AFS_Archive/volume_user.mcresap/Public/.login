# @(#)Login 1.4 88/03/03 SMI
##################################################################
#
#         .login file
#
#         Read in after the .cshrc file when you log in.
#         Not read in for subsequent shells.  For setting up
#         terminal and global environment characteristics.
#
##################################################################
# 12/13/99 Modified to source /usr/local/Startup/Login only if it exists RKS
#
#         terminal characteristics for remote terminals:
#         Leave lines for all but your remote terminal commented
#         out (or add a new line if your terminal does not appear).
#
# Source the System Login
# DO NOT REMOVE THIS LINE
#
if ( -r /usr/local/Startup/Login ) then
	source /usr/local/Startup/Login
endif
#
if ($TERM != "sun") then
#eval `tset -sQ -m dialup:?925 -m switch:?925 -m dumb:?925 $TERM`
#eval `tset -sQ -m dialup:?h19 -m switch:?h19 -m dumb:?h19 $TERM`
#eval `tset -sQ -m dialup:?mac -m switch:?mac -m dumb:?mac $TERM`
#eval `tset -sQ -m dialup:?vt100 -m switch:?vt100 -m dumb:?vt100 $TERM`
#eval `tset -sQ -m dialup:?wyse-nk -m switch:?wyse-nk -m dumb:?wyse-nk $TERM`
#eval `tset -sQ -m dialup:?wyse-vp -m switch:?wyse-vp -m dumb:?wyse-vp $TERM`
endif

#         general terminal characteristics

#stty -crterase
#stty -tabs
#stty crt
#stty erase '^h'
#stty werase '^?'
#stty kill '^['
#stty new

#         environment variables

#setenv EXINIT 'set sh=/bin/csh sw=4 ai report=2'
#setenv MORE '-c'
#setenv PRINTER lw

#         commands to perform at login

#w         # see who is logged in

if ("`tty`" != "/dev/console") exit
echo -n "OpenWindows? (Control-C to interrupt) "
#echo -n "CDE? (Control-C to interrupt) "
sleep 5
openwin
#/usr/openwin/bin/xinit /usr/dt/bin/Xsession
