Eclipse Projects for OpenJDK Sources
====================================

This is a collection of Eclipse projects for OpenJDK:

**C/C++ Projects**

* **hotspot**: CDT project for hotspot sources. Platforms are modelled as CDT Build Configurations.
* **jd_native**: subset of native sources bisedes hotspot. E.g. java.base, jdk.jdwp.agent.

**Java Projects**

* **java.base**: sources of the java.base module
* **java.management**: sources of the java.management module
* **jdk.jdi**: sources of the java.jdi module
* **test.compiler.testlibrary**: hotspot jit compiler test library
* **test.jdk**: jdk regression tests (jdk jtreg tests)
* **test.lib**: jdk test library.


Setup
=====

1. Get Eclipse >= 4.6 and CDT >= 9.2

2. Change into the root of an OpenJDK work tree and clone this repository: `git clone https://github.com/reinrich/OpenJDKEclipseProjs.git`

3. CDT Projects / MS Windows only: replace UNIX symbolic links in the system header archive with NTFS symbolic links:
   * open Explorer in the project directory, e.g. hotspot
   * right-click the file `as_administrator_regen_symlinks_on_windows.cmd`
   * click "Run as administrator"
   
4. Open Eclipse

5. C++ indexer settings: Menu > Window > Preferences > C/C++ > Indexer
  * uncheck all checkboxes in "Indexer options"
  * check "Use active build configuration"
  
6. Menu > File > Import > Existing Projects into Workspace

7. Enter root directory of the cloned repo into "Select Root Directory"

8. Press TAB and select the projects you whish to import.

9. Press finish.

10. Select a build configuration: Menu > Project > Build Configurations > Set Active > CONFIG Currently
    `linux_x86_64`, `linux_ppc_64`, and `linux_s390_64` are the only supported build configurations.

Troubleshooting
===============

* OpenJDK build fails
  - This can happen if you use these projects in an mercurial (hg) OpenJDK work tree. The build collects scm version information,
  but fails when mixing git and hg. Try renaming the .git directories and refer to them with `--git-dir=<name>`
