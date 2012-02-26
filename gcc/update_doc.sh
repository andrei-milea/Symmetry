#!/bin/bash

#remove existent doc
svn rm lib/doc --force
svn rm engine/doc --force
svn rm interface/http_server/doc --force

svn commit -m "removed doc"

#update doc
cd lib
doxygen Doxyfile
cd ../engine
doxygen Doxyfile
cd ../interface/http_server
doxygen Doxyfile
cd ../..

#add updated doc
svn add lib/doc --force
svn add engine/doc --force
svn add interface/http_server/doc --force

#commit changes
svn commit -m "added doc"
