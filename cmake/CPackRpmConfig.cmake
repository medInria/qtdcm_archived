set(BUILD_SHARED_LIBS CACHE FORCE "Build QtDCM with shared libraries." OFF)
set(CPACK_GENERATOR ${CPACK_GENERATOR};RPM)
set(CPACK_RPM ON)
set(CPACK_PACKAGE_NAME "qtdcm-dev")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "QtDCM")
set(CPACK_RPM_PACKAGE_DESCRIPTION "QtDCM")
