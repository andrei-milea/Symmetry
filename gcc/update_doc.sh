#!/bin/bash

#remove existent doc
svn rm lib/doc
svn rm engine/doc
svn rm interface/http_server/doc

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
svn add lib/doc
svn add engine/doc
svn add interface/http_server/doc

#commit changes
svn commit -m "added doc"
