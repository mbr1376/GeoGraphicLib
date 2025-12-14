cmake_minimum_required(VERSION 3.16)
option(COPY_SHARED_LIBS "Copy built shared libraries (*.so) to ${CMAKE_BINARY_DIR}/lib after build" ON)

if(COPY_SHARED_LIBS)
	set(SHARED_LIB_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
	file(MAKE_DIRECTORY "${SHARED_LIB_OUTPUT_DIR}")

	# Utility function to register a target for copying its built file(s) into
	# ${SHARED_LIB_OUTPUT_DIR}. This is preferred over a global find-and-copy
	# because it is precise and cross-platform (uses $<TARGET_FILE:...>).
	function(register_shared_lib_for_copy target)
		if(NOT TARGET ${target})
			message(WARNING "register_shared_lib_for_copy: target '${target}' does not exist yet")
			return()
		endif()
		get_target_property(_t ${target} TYPE)
		if(_t STREQUAL "SHARED_LIBRARY")
			add_custom_command(TARGET ${target} POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E make_directory "${SHARED_LIB_OUTPUT_DIR}"
				COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:${target}>" "${SHARED_LIB_OUTPUT_DIR}"
				COMMENT "Copying $<TARGET_FILE_NAME:${target}> to ${SHARED_LIB_OUTPUT_DIR}"
			)
		else()
			# No-op for non-shared targets; remains silent to avoid noisy output.
		endif()
	endfunction()
endif()

add_subdirectory(WFSLib)
add_subdirectory(GeographicWrapper)
