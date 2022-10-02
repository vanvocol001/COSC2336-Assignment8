# source files in this project (for beautification)
VERSION=0.3
BASE_DIR := ../assg-base-$(VERSION)
PROJECT_NAME=assg

assg_src  = List.cpp \
	    ListIterator.cpp \
	    AList.cpp \
	    AListIterator.cpp \
	    LList.cpp \
	    LListIterator.cpp \
	    ListException.cpp

test_src  = test-AList.cpp \
	    test-LList.cpp \
	    ${assg_src}

debug_src = main.cpp \
	    ${assg_src}

# template files, list all files that define template classes
# or functions and should not be compiled separately (template
# is included where used)
template_files =

# assignment description documentation
assg_doc  = ${PROJECT_NAME}.pdf

# common targets and variables used for all assignments/projects
include $(BASE_DIR)/include/Makefile.inc
