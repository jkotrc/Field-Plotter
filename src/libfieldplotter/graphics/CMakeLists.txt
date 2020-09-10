#CMakeLists for a subfolder

#Not adding the header file might break this
aux_source_directory(. SRC)
message("Found sources in ${WORKING_DIRECTORY}: ${SRC}")
target_sources(Field_Plotter PUBLIC ${SRC})