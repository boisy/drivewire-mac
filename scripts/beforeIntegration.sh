#!/bin/bash
# Before Integration Run Script
# Called by the Xcode Bot
export LANG=en_US.UTF-8
export PATH=/usr/local/opt/ruby/bin:/usr/local/bin:$PATH
cd ${XCS_SOURCE_DIR}
echo "Running POD INSTALL"
#pod update
pod install

