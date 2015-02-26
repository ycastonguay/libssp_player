#!/bin/bash

javac -d jni player-java/src/org/sessionsapp/player/SSP.java
cd jni
rm -f ssp_java.h
javah -o ssp_java.h -jni org.sessionsapp.player.SSP
cd ..