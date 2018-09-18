NodeHealthMonitor (NHM) README
==============================

About 
-----

This is the official source of the NodeHealthMonitor (NHM). The NHM is a system 
software component that observes the system health and initiates configurable 
actions, if issues are identified. An overview about the architecture and how 
the component interacts with the other GENIVI components is available at: 

http://wiki.projects.genivi.org/index.php/Lifecycle_cluster 

Source repository
-----------------

The offical git repository of the NHM is located at:
http://git.projects.genivi.org/lifecycle/node-health-monitor.git

Mailing list
------------

The mailing list for the NHM and other GENIVI Lifecycle components is:  
https://lists.genivi.org/mailman/listinfo/genivi-lifecycle

Bug reports
------------

NHM bugs can be reported at: 
http://bugs.genivi.org/

License
-------

For licensing info see the COPYING file, distributed along with this project.

Authors
-------

Please see the AUTHORS file, distributed with the project. 

Coding style
------------

Please see the CODING_STYLE document, distributed with the project.

Requirements
------------

For compilation the NHM needs development versions of the following packages 
installed:

  - automotive-dlt             >= 2.2.0
  - glib-2.0                   >= 2.30.0
  - node-state-manager         >= 1.2.0.0
  - persistence_client_library >= 7.0.0
  - dbus                       >= 1.6.4
  - systemd                    >= 187

Include and library paths for the packages are obtained via "pkg-config". 

Build instructions
------------------

The NHM is a GNU Build system (autotools) project. An own version of the NHM can 
be set up, configured, compiled, checked and installed by using the following 
commands:

autoreconf -vfi
./configure <configure-flags>
make
make check
make install

An overview of the possible configuration parameters (especially needed for 
cross compilation) can be retrieved by calling "./configure --help".  
The generated Makefiles will support all "standard targets for users" defined 
by the GNU makefile conventions.  

Quality
-------

The NHM is delivered with a unit test that is executed when "make check" is 
called. The code coverage of the unit test can be measured with tools like 
"gcov". The coverage currently is > 80 % and shall always stay at this level. 
The unit test can be executed using "valgrind" to detect memory leaks. The 
source code of the NHM should be checked with Klocwork when it is available.

