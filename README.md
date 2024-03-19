Eclipse Projects for OpenJDK Sources
====================================

This is a collection of Eclipse projects for OpenJDK:

**C/C++ Projects**

* **hotspot**: CDT project for hotspot sources. Platforms are modelled as CDT Build Configurations.
* **jdk_native**: subset of native sources besides hotspot. E.g. java.base, jdk.jdwp.agent.

**Java Projects**

* **java.base**: sources of the java.base module
* **java.management**: sources of the java.management module
* **jdk.jdi**: sources of the java.jdi module
* **test.compiler.testlibrary**: hotspot jit compiler test library
* **test.jdk**: jdk regression tests (jdk jtreg tests)
* **test.lib**: jdk test library.


Setup
=====

1. Get Eclipse >= 2019-03 and CDT >= 9.2

2. Change into the root of an OpenJDK source tree and clone this repository: `git clone https://github.com/reinrich/OpenJDKEclipseProjs.git`

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

10. Git only: for revision information in Eclipse you have to change to the .git folder in your source tree root.
    * select all projects in the project explorer
    * Right-click selection > Team > Disconnect
    * Right-click selection > Team > Share Project > Git
    * Press "Next"
    * Check "Use or create repository in parent folder of project"
    * Select "../.."  for every project and click finish.
    * To check for success open for example jvm.cpp, then right click the line number column and select "Show Revision Information".

11. Select a build configuration: Menu > Project > Build Configurations > Set Active > CONFIG. Currently
    `linux_x86_64`, `linux_ppc_64`, `bsd_aarch64`, and `linux_s390_64` are the only supported build
    configurations.  You should be able to create hotspot build configurations for other platforms using
    `hotspot/projgenerator/cdt_gen_build_config.sh` yourself as I cannot redistribute the required
    system and C++ compiler header files as part of this repository.

12. Mac OS on AARCH64
    
    `bsd_aarch64` is the configuration for macOS on aarch64. It requires Xcode. I'd recommend to do the following:
    * Download Xcode 13.4.1 from https://developer.apple.com/xcode/.
      Alternatively you can also use a newer version or just install Xcode from the app store (see below for that).
    * Unpack the xip file to /opt/Xcode_13.4.1.app.  You can unpack also to a
      different location. In that case you should let the symbolic link
      `hotspot/hotspot_sys_headers_and_outputdir_src/bsd_aarch64_64/sys_headers/Xcode_13.4.1.app`
      point to that location.
    * I recommend stripping Xcode and keep only the following directories:
      ```
      Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr
      Contents/Developer/Toolchains/XcodeDefault.xctoolchain
      ```
      Otherwise importing and refreshing the hotspot project takes several minutes.
    * Using other Xcode versions
      - If you installed Xcode from the app store, you should change the
        symbolic link `hotspot/projgenerator/cdt_gen_build_config.sh` and let it
        point to `/Applications/Xcode.app`
      - Open `hotspot/.cproject` and change the version number `13.1.6` in all occurrences of `XcodeDefault.xctoolchain/usr/lib/clang/13.1.6/` to match your version.
    

Troubleshooting
===============

* OpenJDK build fails
  - This can happen if you use these projects in an mercurial (hg) OpenJDK work tree. The build collects VCS version information,
  but fails when mixing git and hg. You should position your clone of this repo outside the OpenJDK source tree.

* Git revision information for OpenJDK sources missing. This is because the projects themselves are kept in a git repository which hides the outer OpenJDK repository. Follow instructions in Setup step 11.
