#This will be used to fetch content from github and build it,
#if it hasn't been found yet through `find_package()`

# Cmake functions work as follows: function name, params[]
# Here we call the function `FetchIt` and pass a library, url and GIT_TAG along
# for this function to use.
function(fetchIt library url tag)

    if (NOT library)
        FetchContent_Declare(
                library
                URL url
                GIT_TAG tag
        )
        FetchContent_MakeAvailable(library)
    endif ()
endfunction()