find_path(LUAJIT_INCLUDE_DIR luajit.h
	NAMES luajit.h
	PATH_SUFFIXES luajit-2.0)

if (LuaJIT_USE_STATIC)
	find_library(LUAJIT_LIBRARIES luajit.a
		NAMES libluajit-5.1.a)
else (LuaJIT_USE_STATIC)
	find_library(LUAJIT_LIBRARIES luajit
		NAMES luajit-5.1)
endif (LuaJIT_USE_STATIC)

mark_as_advanced(LUAJIT_INCLUDE_DIR)
mark_as_advanced(LUAJIT_LIBRARIES)

# handle the QUIETLY and REQUIRED arguments and set LUAJIT_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LuaJIT DEFAULT_MSG LUAJIT_LIBRARIES LUAJIT_INCLUDE_DIR)

