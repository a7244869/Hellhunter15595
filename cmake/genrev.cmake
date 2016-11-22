# TER-Server_S
include(${CMAKE_SOURCE_DIR}/cmake/macros/EnsureVersion.cmake)

set(_REQUIRED_GIT_VERSION "1.7")

find_program(_GIT_EXEC
  NAMES
    git git.cmd
  HINTS
    ENV PATH
  DOC "git installation path"
)

if(_GIT_EXEC)
  execute_process(
    COMMAND "${_GIT_EXEC}" --version
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    OUTPUT_VARIABLE _GIT_VERSION
    ERROR_QUIET
  )

  # make sure we're using minimum the required version of git, so the "dirty-testing" will work properly
  ensure_version( "${_REQUIRED_GIT_VERSION}" "${_GIT_VERSION}" _GIT_VERSION_OK)
endif()

if(_GIT_VERSION_OK)
  execute_process(
    COMMAND "${_GIT_EXEC}" describe --match init --dirty=+ --abbrev=12
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    OUTPUT_VARIABLE rev_info
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )
  execute_process(
    COMMAND "${_GIT_EXEC}" show -s --format=%ci
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    OUTPUT_VARIABLE rev_date
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )
else()
  message("")
  message(STATUS "WARNING - Missing or outdated git - did you forget to install a recent version?")
  message(STATUS "WARNING - Observe that for revision hash/date to work you need at least version ${_REQUIRED_GIT_VERSION}")
endif()

# Last minute check - ensure that we have a proper revision
# If everything above fails (means the user has erased the git revision control directory or removed the origin/HEAD tag)
if(NOT rev_info)
  # No valid ways available to find/set the revision/hash, so let's force some defaults
  message(STATUS "WARNING - Missing repository tags - you may need to pull tags with git fetch -t")
  message(STATUS "WARNING - Continuing anyway - note that the versionstring will be set to 2007-2016 r400-r500 (Hellhunter)")
  set(rev_date "2015-2016 r100")
  set(rev_hash "Hellhunter-Server")
else()
  # Extract information required to build a proper versionstring 
  string(REGEX REPLACE init-|[0-9]+-g "" rev_hash ${rev_info})
endif()

# Its not set during initial run
if(NOT BUILDDIR)
  set(BUILDDIR ${CMAKE_BINARY_DIR})
endif()

# Create the actual revision.h file from the above params
if(NOT "${rev_hash_cached}" MATCHES "${rev_hash}")
  configure_file(
    "${CMAKE_SOURCE_DIR}/revision.h.in.cmake"
    "${BUILDDIR}/revision.h"
    @ONLY
  )
  set(rev_hash_cached "${rev_hash}" CACHE INTERNAL "Cached commit-hash")
endif()