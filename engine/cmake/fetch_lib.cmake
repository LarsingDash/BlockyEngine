cmake_minimum_required(VERSION 3.28)

# A CMake function to download a specified library
# It's meant to be used when first time building the project.
# If it downloads the libraries again then something has gone horribly wrong,
#  meaning you probably deleted the dependencies folder or a library within it...
function(build_lib folder library url isPreBuilt)
    include(FetchContent)
    include(ExternalProject)

    if (NOT EXISTS "${folder}")
        message(STATUS "Creating dependencies folder")
        file(MAKE_DIRECTORY "dependencies")
    endif ()

    message("FETCHING: ${library}")

    # Avoid trying to re-download it into the dependencies folder.
    if (EXISTS "${folder}/${library}")
        message(STATUS "Library already")
        return()
    endif ()

    if (${isPreBuilt})
        message(STATUS "Starting to fetch the pre-built binary")

        # Downloads the file
        file(DOWNLOAD ${url} "${folder}/${library}.zip")

        message(STATUS "Extracting library from zip")

        # Creates a temp dir inside of engine/dependencies for extracting the libraries from .zip's
        set(TEMP_DIR "${folder}/tmp")
        file(MAKE_DIRECTORY ${TEMP_DIR})
        message(STATUS ${TEMP_DIR})

        # Unzips the library inside of temp
        execute_process(
                COMMAND ${CMAKE_COMMAND} -E tar xzf
                "${folder}/${library}.zip"
                WORKING_DIRECTORY ${TEMP_DIR}
        )

        #Get extracted folder from tmp
        file(GLOB EXTRACTED_FILES "${TEMP_DIR}/*")
        message(STATUS "Extracted files: ${EXTRACTED_FILES}")

        #Rename library to the lib name instead
        if (EXISTS ${EXTRACTED_FILES})
            #Get dir from list, and should always be index 0
            list(GET EXTRACTED_FILES 0 EXTRACTED_DIR)

            message(STATUS "Extracted dir: ${EXTRACTED_DIR}")

            file(RENAME ${EXTRACTED_DIR} "${folder}/${library}")
        else ()
            message(FATAL_ERROR "${EXTRACTED_FILES}")
        endif ()

        message(STATUS "Cleaning up")
        file(REMOVE "${folder}/${library}.zip")
        file(REMOVE_RECURSE "${TEMP_DIR}")

        message(STATUS "Appended to: ${folder}")
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