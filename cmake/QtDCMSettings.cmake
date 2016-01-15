## SETTING THE INCLUDE DIRS
set(QTDCM_INCLUDE_DIRS
  ## Modules include dirs
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_BINARY_DIR}
  ${PROJECT_BINARY_DIR}/src
)

include_directories(${QTDCM_INCLUDE_DIRS})

## SETTING QTDCM LIBS
set(QTDCM_LIBRARIES qtdcm)
