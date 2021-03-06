FIND_PATH(PCAP_INCLUDE_DIR pcap.h ${_PCAP_PATHS} PATH_SUFFIXES include)

IF (NOT PCAP_LIBRARIES)
    FIND_LIBRARY(PCAP_LIBRARIES NAMES pcap ${_PCAP_PATHS} PATH_SUFFIXES lib)
ENDIF (NOT PCAP_LIBRARIES)

# handle the QUIETLY and REQUIRED arguments and set PCAP_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(PCAP REQUIRED_VARS PCAP_LIBRARIES PCAP_INCLUDE_DIR)

MARK_AS_ADVANCED(PCAP_INCLUDE_DIR)
