cmake_minimum_required(VERSION 3.28)

# A CMake function to download a specified library
# It's meant to be used when first time building the project.
# If it downloads the libraries again then something has gone horribly wrong,
#  meaning you probably deleted the libs folder or a library within it...
function(build_lib library url isPreBuilt)
    include(FetchContent)
    include(ExternalProject)

    message("FETCHING: ${library}")

    # Avoid trying to re-download it into the libs folder.
    if (EXISTS "${LIBS_DIR}/${library}")
        message("ALREADY EXISTS! EXITING NOW!")
        return()
    endif ()

    if (${isPreBuilt})
        message(STATUS "Starting to fetch the pre-built binary")

        file(DOWNLOAD ${url} "${LIBS_DIR}/${library}.zip")

        message(STATUS "Extracting library from zip")

        set(TEMP_DIR "${LIBS_DIR}/tmp")
        file(MAKE_DIRECTORY ${TEMP_DIR})

        execute_process(
                COMMAND ${CMAKE_COMMAND} -E tar xzf
                "${LIBS_DIR}/${library}.zip"
                WORKING_DIRECTORY ${TEMP_DIR}
        )

        #Get extracted folder from tmp
        file(GLOB EXTRACTED_FILES "${TEMP_DIR}/*")
        message(STATUS "Extracted files: ${EXTRACTED_FILES}")

        #Rename library to the lib name instead

        if (EXISTS ${EXTRACTED_FILES})
            #Get dir from list
            list(GET EXTRACTED_FILES 0 EXTRACTED_DIR)

            message(STATUS "Extracted dir: ${EXTRACTED_DIR}")

            file(RENAME ${EXTRACTED_DIR} "${LIBS_DIR}/${library}")
        else ()
            message(FATAL_ERROR "${EXTRACTED_FILES}")
        endif ()

        message(STATUS "Cleaning up")
        file(REMOVE "${LIBS_DIR}/${library}.zip")
        file(REMOVE_RECURSE "${TEMP_DIR}")

        message(STATUS "Appended to: ${LIBS_DIR}")
        message("Fetching done!")

    else ()
        # If it isn't prebuilt we will just download the git repo through FetchContent
        message(STATUS "Starting to fetch the git repository through the link")

        message(STATUS "Proceeding to use Fetchcontent on ${library}")
        FetchContent_Declare(
                ${library}
                URL ${url}
                OVERRIDE_FIND_PACKAGE
        )
        find_package(${library})
    endif ()

endfunction()