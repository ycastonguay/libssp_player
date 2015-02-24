#!/bin/bash

javac -d player-java player-java/SSP.java
cd player-java
javah -o ssp_java.h -jni org.sessionsapp.player.SSP
cd ..