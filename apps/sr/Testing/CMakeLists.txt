set(MODULE_NAME tid1500)

set(WRITER_MODULE_NAME tid1500writer)

add_test(NAME ${WRITER_MODULE_NAME}_hello
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${WRITER_MODULE_NAME} --help)
set_property(TEST ${WRITER_MODULE_NAME}_hello PROPERTY LABELS ${MODULE_NAME})

add_test(NAME ${WRITER_MODULE_NAME}_example
COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${WRITER_MODULE_NAME}
  --metaDataFileName ${CMAKE_SOURCE_DIR}/doc/sr-tid1500-example.json
  --outputFileName ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sr-tid1500-example.dcm
  --imageLibraryDataDir ${CMAKE_SOURCE_DIR}/data/ct-3slice
  --compositeContextDataDir ${CMAKE_SOURCE_DIR}/data/sr-example
  )
set_property(TEST ${WRITER_MODULE_NAME}_example PROPERTY LABELS ${MODULE_NAME})

add_test(NAME ${WRITER_MODULE_NAME}_ct-liver
COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${WRITER_MODULE_NAME}
  --metaDataFileName ${CMAKE_SOURCE_DIR}/doc/sr-tid1500-ct-liver-example.json
  --outputFileName ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sr-tid1500-ct-liver-example.dcm
  --imageLibraryDataDir ${CMAKE_SOURCE_DIR}/data/ct-3slice
  --compositeContextDataDir ${CMAKE_SOURCE_DIR}/data/ct-3slice
  )
set_property(TEST ${WRITER_MODULE_NAME}_ct-liver PROPERTY LABELS ${MODULE_NAME})


set(READER_MODULE_NAME tid1500reader)

add_test(NAME ${READER_MODULE_NAME}_hello
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${READER_MODULE_NAME} --help)
set_property(TEST ${READER_MODULE_NAME}_hello PROPERTY LABELS ${MODULE_NAME})

#add_test(NAME ${READER_MODULE_NAME}_example
#  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${READER_MODULE_NAME}
#  --inputSRFileName ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sr-tid1500-example.dcm
#  --metaDataFileName ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sr-tid1500-example.json
#  )
#set_property(TEST ${READER_MODULE_NAME}_example PROPERTY LABELS ${MODULE_NAME})
#set_tests_properties(${READER_MODULE_NAME}_example PROPERTIES DEPENDS ${WRITER_MODULE_NAME}_example)

add_test(NAME ${READER_MODULE_NAME}_ct-liver
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${READER_MODULE_NAME}
  --inputSRFileName ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sr-tid1500-ct-liver-example.dcm
  --metaDataFileName ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sr-tid1500-ct-liver-example.json
  )
set_property(TEST ${READER_MODULE_NAME}_ct-liver PROPERTY LABELS ${MODULE_NAME})
set_tests_properties(${READER_MODULE_NAME}_ct-liver PROPERTIES DEPENDS ${WRITER_MODULE_NAME}_ct-liver)

add_test(NAME ${MODULE_NAME}_meta_roundtrip
  COMMAND python ${CMAKE_SOURCE_DIR}/util/comparejson.py
  ${CMAKE_SOURCE_DIR}/doc/sr-tid1500-ct-liver-example.json
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sr-tid1500-ct-liver-example.json
  "['activitySession', 'timePoint', 'imageLibrary', 'compositeContext']")
set_tests_properties(${MODULE_NAME}_meta_roundtrip PROPERTIES DEPENDS ${READER_MODULE_NAME}_ct-liver)
set_property(TEST ${MODULE_NAME}_meta_roundtrip PROPERTY LABELS ${MODULE_NAME})
