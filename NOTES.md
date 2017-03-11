# Overall

The overall project setup is templated from cognitivewayes from their
[blog](http://cognitivewaves.wordpress.com/cmake-and-visual-studio)
for reason being making this project portable between everything (CMake
provides) and with odd-bird Windows.

# Windows / Visual Studio 2015

In the source directory, create a build directory `mkdir BUILD; cd BUILD`
and from there `cmake ../`. No need for any other parameters.

Open *Visual Studio* and `File->Open->Project/Solution` and navigate to the
above directory to open the solution-file.

## Extra tweaks

* Set default project to polygons_cxx
* Set `Properties->Debugging->Environment` to
  `PATH=%PATH%;$(SolutionDir)\math\$(Configuration)`

# Linux / POSIX

Creating a build directory (`BUILD`) is optional but recommended. Note that
the build-directory is used somewhat differently and contains no further
project files.

* `cmake ${YOUR_SRC} -DCMAKE_BUILD_TYPE="Debug"`
* `make`

And you're done.

**Note :** that for non-Windows Visual Studio set-up´s, you need your
project constantly properly configured (hence the `-D` option above). Do
make a habit of using the `ccmake .` utility to reconfigure (no need to
re-generate the project, the makefile produced is smart enough to do this
for you if needed).
