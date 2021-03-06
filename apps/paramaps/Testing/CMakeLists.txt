set(BASELINE ${CMAKE_SOURCE_DIR}/data/paramaps/)
include_directories(${ITK_INCLUDE_DIRS})

set(MODULE_NAME itkimage2paramap)

add_executable(${MODULE_NAME}Test ${MODULE_NAME}Test.cxx )
target_link_libraries(${MODULE_NAME}Test ${${MODULE_NAME}_TARGET_LIBRARIES})
set_target_properties(${MODULE_NAME}Test PROPERTIES LABELS ${MODULE_NAME})
set_target_properties(${MODULE_NAME}Test PROPERTIES FOLDER ${${MODULE_NAME}_TARGETS_FOLDER})

add_test(NAME ${MODULE_NAME}_hello
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${MODULE_NAME} --help)
add_test(NAME ${MODULE_NAME}_makeParametricMap
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${MODULE_NAME}
        --metaDataFileName ${CMAKE_SOURCE_DIR}/doc/pm-example.json
        --inputFileName ${BASELINE}/pm-example.nrrd
        --outputParaMapFileName ${TEMP_DIR}/paramap.dcm
        --dicomImageFileName ${BASELINE}/pm-example-slice.dcm
       )

add_test(NAME ${MODULE_NAME}_makeParametricMapFP
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${MODULE_NAME}
        --metaDataFileName ${CMAKE_SOURCE_DIR}/doc/pm-example-float.json
        --inputFileName ${BASELINE}/pm-example-float.nrrd
        --outputParaMapFileName ${TEMP_DIR}/paramap-float.dcm
        --dicomImageFileName ${BASELINE}/pm-example-slice.dcm
       )

set_property(TEST ${testname} PROPERTY LABELS ${MODULE_NAME})

set(MODULE_NAME paramap2itkimage)

add_executable(${MODULE_NAME}Test ${MODULE_NAME}Test.cxx )
target_link_libraries(${MODULE_NAME}Test ${MODULE_NAME}Lib ${ITK_LIBRARIES})
set_target_properties(${MODULE_NAME}Test PROPERTIES LABELS ${MODULE_NAME})
set_target_properties(${MODULE_NAME}Test PROPERTIES FOLDER ${${MODULE_NAME}_TARGETS_FOLDER})

add_test(NAME ${MODULE_NAME}_hello
         COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${MODULE_NAME} --help)
add_test(NAME ${MODULE_NAME}_makeNRRDParametricMap
         COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${MODULE_NAME}Test>
         --compare ${BASELINE}/pm-example.nrrd
         ${TEMP_DIR}/pmap.nrrd
         ${MODULE_NAME}Test
         --inputFileName ${TEMP_DIR}/paramap.dcm
         --outputDirName ${TEMP_DIR})

       add_test(NAME ${MODULE_NAME}_makeNRRDParametricMapFP
         COMMAND ${SEM_LAUNCH_COMMAND} $<TARGET_FILE:${MODULE_NAME}Test>
         --compare ${BASELINE}/pm-example-float.nrrd
         ${TEMP_DIR}/pmap.nrrd
         ${MODULE_NAME}Test
         --inputFileName ${TEMP_DIR}/paramap-float.dcm
         --outputDirName ${TEMP_DIR})

set_property(TEST ${testname} PROPERTY LABELS ${MODULE_NAME})
