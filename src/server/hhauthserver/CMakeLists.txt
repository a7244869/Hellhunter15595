#Hellhunter

########### hhauthserver ###############

file(GLOB_RECURSE sources_authentication Authentication/*.cpp Authentication/*.h)
file(GLOB_RECURSE sources_realms Realms/*.cpp Realms/*.h)
file(GLOB_RECURSE sources_server Server/*.cpp Server/*.h)
file(GLOB sources_localdir *.cpp *.h)

if (USE_COREPCH)
  set(hhauthserver_PCH_HDR PrecompiledHeaders/authPCH.h)
  set(hhauthserver_PCH_SRC PrecompiledHeaders/authPCH.cpp)
endif()

set(hhauthserver_SRCS
  ${hhauthserver_SRCS}
  ${sources_authentication}
  ${sources_realms}
  ${sources_server}
  ${sources_localdir}
)

if( WIN32 )
if ( MSVC )
set(hhauthserver_SRCS
    ${hhauthserver_SRCS}
    ${sources_Debugging}
    hhauthserver.rc
 )
  else ( )
    set(hhauthserver_SRCS
      ${hhauthserver_SRCS}
      ${sources_Debugging}
    )
  endif ()
endif()

include_directories(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src/server/shared
  ${CMAKE_SOURCE_DIR}/src/server/shared/Database
  ${CMAKE_SOURCE_DIR}/src/server/shared/Debugging
  ${CMAKE_SOURCE_DIR}/src/server/shared/Packets
  ${CMAKE_SOURCE_DIR}/src/server/shared/Cryptography
  ${CMAKE_SOURCE_DIR}/src/server/shared/Cryptography/Authentication
  ${CMAKE_SOURCE_DIR}/src/server/shared/Logging
  ${CMAKE_SOURCE_DIR}/src/server/shared/Threading
  ${CMAKE_SOURCE_DIR}/src/server/shared/Utilities
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Authentication
  ${CMAKE_CURRENT_SOURCE_DIR}/Realms
  ${CMAKE_CURRENT_SOURCE_DIR}/Server
  ${ACE_INCLUDE_DIR}
  ${MYSQL_INCLUDE_DIR}
  ${OPENSSL_INCLUDE_DIR}
)

add_executable(hhauthserver
  ${hhauthserver_SRCS}
  ${hhauthserver_PCH_SRC}
)

add_dependencies(hhauthserver revision.h)

if( NOT WIN32 )
  set_target_properties(hhauthserver PROPERTIES
    COMPILE_DEFINITIONS _TRINITY_REALM_CONFIG="${CONF_DIR}/hhauthserver.conf"
  )
endif()

target_link_libraries(hhauthserver
  shared
  ${MYSQL_LIBRARY}
  ${OPENSSL_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
  ${ACE_LIBRARY}
)

if( WIN32 )
   if ( MSVC )
    add_custom_command(TARGET hhauthserver
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/hhauthserver.conf ${CMAKE_BINARY_DIR}/bin/$(ConfigurationName)/
    )
  elseif ( MINGW )
    add_custom_command(TARGET hhauthserver
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/hhauthserver.conf ${CMAKE_BINARY_DIR}/bin/
    )
  endif()
endif()

if( UNIX )
  install(TARGETS hhauthserver DESTINATION bin)
  install(FILES  hhauthserver.conf DESTINATION etc)
elseif( WIN32 )
  install(TARGETS hhauthserver DESTINATION "${CMAKE_INSTALL_PREFIX}")
  install(FILES hhauthserver.conf DESTINATION "${CMAKE_INSTALL_PREFIX}")
endif()

# Generate precompiled header
if (USE_COREPCH)
  add_cxx_pch(hhauthserver ${hhauthserver_PCH_HDR} ${hhauthserver_PCH_SRC})
endif()
