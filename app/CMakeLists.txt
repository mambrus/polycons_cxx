# Properties->C/C++->General->Additional Include Directories
include_directories ("${PROJECT_SOURCE_DIR}/math")

# Set Properties->General->Configuration Type to Application(.exe)
# Creates polygons_cxx.exe with the listed sources (main.cxx)
# Adds sources to the Solution Explorer
add_executable (polygons_cxx main.cxx)

# Properties->Linker->Input->Additional Dependencies
target_link_libraries (polygons_cxx  math)

# Creates a folder "executables" and adds target
# project (polygons_cxx.vcproj) under it
set_property(TARGET polygons_cxx PROPERTY FOLDER "executables")

# Adds logic to INSTALL.vcproj to copy polygons_cxx.exe to destination directory
install (TARGETS polygons_cxx
		 RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)
