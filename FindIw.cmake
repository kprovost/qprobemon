FIND_PATH(IW_INCLUDE_DIR iwlib.h ${_IW_PATHS} PATH_SUFFIXES include)

IF (NOT IW_LIBRARIES)
    FIND_LIBRARY(IW_LIBRARIES NAMES iw ${_IW_PATHS} PATH_SUFFIXES lib)
ENDIF (NOT IW_LIBRARIES)

# handle the QUIETLY and REQUIRED arguments and set IW_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(IW REQUIRED_VARS IW_LIBRARIES IW_INCLUDE_DIR)

MARK_AS_ADVANCED(IW_INCLUDE_DIR)
