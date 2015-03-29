// Copyright © 2011-2015 Yanick Castonguay
//
// This file is part of Sessions, a music player for musicians.
//
// Sessions is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Sessions is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Sessions. If not, see <http://www.gnu.org/licenses/>.

#ifndef player_errors_h
#define player_errors_h

#define SSP_ERROR int

// General
#define SSP_OK                                            0
#define SSP_ERROR_UNKNOWN		                          1
#define SSP_ERROR_BASS_VERSION                            2

// Initialization
#define SSP_ERROR_SAMPLERATE_INVALID                     10
#define SSP_ERROR_BUFFERSIZE_INVALID                     11
#define SSP_ERROR_UPDATEPERIOD_INVALID                   12

// Playlist
#define SSP_ERROR_NOCHANNELSTOPLAY                       20
#define SSP_ERROR_CURRENTPLAYLISTITEMISNULL              21

// Position
#define SSP_ERROR_FAILEDTOGETPOSITION                    30
#define SSP_ERROR_FAILEDTOSETPOSITION                    31
#define SSP_ERROR_FAILEDTOGETLENGTH                      32
#define SSP_ERROR_FAILEDTOFLUSHBUFFER                    33

// Channels
#define SSP_ERROR_FAILEDTOPLAYCHANNEL                    40
#define SSP_ERROR_FAILEDTOSTOPCHANNEL                    41
#define SSP_ERROR_FAILEDTOLOCKCHANNEL                    42
#define SSP_ERROR_FAILEDTODISPOSECHANNELS                43
#define SSP_ERROR_FAILEDTOGETCHANNELINFO                 44

// Streams
#define SSP_ERROR_FAILEDTOCREATEDECODESTREAM             50
#define SSP_ERROR_FAILEDTOCREATEMEMORYSTREAM             51
#define SSP_ERROR_FAILEDTOCREATEFXCHANNEL                52
#define SSP_ERROR_FAILEDTOCREATEMIXERCHANNEL             53
#define SSP_ERROR_FAILEDTOADDSTREAMTOMIXER               54
#define SSP_ERROR_FAILEDTOFREESTREAM                     55

// Playback
#define SSP_ERROR_FAILEDTOSTART                          60
#define SSP_ERROR_FAILEDTOSTARTPAUSED                    61
#define SSP_ERROR_FAILEDTOPAUSE                          62
#define SSP_ERROR_FAILEDTOSTOP                           63

// Syncs
#define SSP_ERROR_FAILEDTOSETSYNC                        70
#define SSP_ERROR_FAILEDTOSETSYNCCALLBACK                71
#define SSP_ERROR_FAILEDTOREMOVESYNC                     72
#define SSP_ERROR_FAILEDTOREMOVESYNCCALLBACKS            73
#define SSP_ERROR_FAILEDTOREMOVEBPMCALLBACKS             74

// Playhead
#define SSP_ERROR_FAILEDTOSETREPEATTYPE                  80 
#define SSP_ERROR_FAILEDTOSETBUFFERSIZE                  81
#define SSP_ERROR_FAILEDTOSETUPDATEPERIOD                82
#define SSP_ERROR_FAILEDTOSETVOLUME                      83
#define SSP_ERROR_FAILEDTOSETTIMESHIFTING                84
#define SSP_ERROR_FAILEDTOSETPITCHSHIFTING               85

// Plugins
#define SSP_ERROR_PLUGIN_APE_FAILEDTOLOAD              1000
#define SSP_ERROR_PLUGIN_AAC_FAILEDTOLOAD              1001
#define SSP_ERROR_PLUGIN_ALAC_FAILEDTOLOAD             1002
#define SSP_ERROR_PLUGIN_FLAC_FAILEDTOLOAD             1003
#define SSP_ERROR_PLUGIN_MPC_FAILEDTOLOAD              1004
#define SSP_ERROR_PLUGIN_TTA_FAILEDTOLOAD              1005
#define SSP_ERROR_PLUGIN_WMA_FAILEDTOLOAD              1006
#define SSP_ERROR_PLUGIN_WV_FAILEDTOLOAD               1007

#define SSP_ERROR_PLUGIN_APE_FAILEDTOFREE              1010
#define SSP_ERROR_PLUGIN_AAC_FAILEDTOFREE              1011
#define SSP_ERROR_PLUGIN_ALAC_FAILEDTOFREE             1012
#define SSP_ERROR_PLUGIN_FLAC_FAILEDTOFREE             1013
#define SSP_ERROR_PLUGIN_MPC_FAILEDTOFREE              1014
#define SSP_ERROR_PLUGIN_TTA_FAILEDTOFREE              1015
#define SSP_ERROR_PLUGIN_WMA_FAILEDTOFREE              1016
#define SSP_ERROR_PLUGIN_WV_FAILEDTOFREE               1017

// Devices
#define SSP_ERROR_DEVICE_FAILEDTOLOAD                  1100
#define SSP_ERROR_DEVICE_FAILEDTOFREE                  1101

// EQ
#define SSP_ERROR_EQ_STAGE_ALREADYEXISTS		       2000
#define SSP_ERROR_EQ_STAGE_DOESNOTEXIST     	       2001
#define SSP_ERROR_EQ_STAGE_FAILEDTOCREATE     	       2002
#define SSP_ERROR_EQ_STAGE_FAILEDTOREMOVE     	       2003

// Loops
#define SSP_ERROR_LOOP_INVALID                         3000

// Encoder
#define SSP_ERROR_ENCODER_FAILEDTOSTART                4000
#define SSP_ERROR_ENCODER_FAILEDTOSTOP                 4001

// Cast server
#define SSP_ERROR_CAST_ENCODERNOTFOUND                 5100
#define SSP_ERROR_CAST_FAILEDTOINIT                    5101

#endif
