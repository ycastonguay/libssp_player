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

#define SSP_OK                                            0
#define SSP_ERROR_UNKNOWN		                          1
#define SSP_ERROR_BASS_VERSION                            2

#define SSP_ERROR_SAMPLERATE_INVALID                     10
#define SSP_ERROR_BUFFERSIZE_INVALID                     11
#define SSP_ERROR_UPDATEPERIOD_INVALID                   12

#define SSP_ERROR_CURRENTPLAYLISTITEMISNULL             100
#define SSP_ERROR_FAILEDTOGETPOSITION                   101
#define SSP_ERROR_FAILEDTOSETPOSITION                   102
#define SSP_ERROR_FAILEDTOLOCKCHANNEL                   103
#define SSP_ERROR_FAILEDTOSETSYNC                       104
#define SSP_ERROR_FAILEDTOREMOVESYNC                    105
#define SSP_ERROR_FAILEDTOCREATEDECODESTREAM            106
#define SSP_ERROR_FAILEDTOGETLENGTH                     107
#define SSP_ERROR_FAILEDTOFREESTREAM                    108

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

#define SSP_ERROR_DEVICE_FAILEDTOLOAD                  1100
#define SSP_ERROR_DEVICE_FAILEDTOFREE                  1101

#define SSP_ERROR_EQ_STAGE_ALREADYEXISTS		       2000
#define SSP_ERROR_EQ_STAGE_DOESNOTEXIST     	       2001
#define SSP_ERROR_EQ_STAGE_FAILEDTOCREATE     	       2002
#define SSP_ERROR_EQ_STAGE_FAILEDTOREMOVE     	       2003

#define SSP_ERROR_PLAYBACK_PLAY_NOCHANNELSTOPLAY                3000
#define SSP_ERROR_PLAYBACK_PLAY_FAILEDTOCREATEMEMORYSTREAM      3001
#define SSP_ERROR_PLAYBACK_PLAY_FAILEDTOCREATEFXCHANNEL         3002
#define SSP_ERROR_PLAYBACK_PLAY_FAILEDTOCREATEMIXERCHANNEL      3003
#define SSP_ERROR_PLAYBACK_PLAY_FAILEDTOADDSTREAMTOMIXER        3004
#define SSP_ERROR_PLAYBACK_PLAY_FAILEDTOSETSYNCCALLBACK         3005
#define SSP_ERROR_PLAYBACK_PLAY_FAILEDTOSTART                   3006
#define SSP_ERROR_PLAYBACK_PLAY_FAILEDTOPLAYCHANNEL             3007
#define SSP_ERROR_PLAYBACK_PLAY_FAILEDTOSETREPEATTYPE           3008
#define SSP_ERROR_PLAYBACK_PLAY_FAILEDTOSTARTPAUSED             3009

#define SSP_ERROR_PLAYBACK_PAUSE_FAILEDTOSTART                  3100
#define SSP_ERROR_PLAYBACK_PAUSE_FAILEDTOPAUSE                  3101

#define SSP_ERROR_PLAYBACK_STOP_FAILEDTOSTOPCHANNEL             3200
#define SSP_ERROR_PLAYBACK_STOP_FAILEDTOFREESTREAM              3201
#define SSP_ERROR_PLAYBACK_STOP_FAILEDTODISPOSECHANNELS         3202
#define SSP_ERROR_PLAYBACK_STOP_FAILEDTOREMOVESYNCCALLBACKS     3203
#define SSP_ERROR_PLAYBACK_STOP_FAILEDTOREMOVEBPMCALLBACKS      3204

#define SSP_ERROR_PLAYLISTITEM_DISPOSE_FAILEDTOSTOPCHANNEL      4200
#define SSP_ERROR_PLAYLISTITEM_DISPOSE_FAILEDTOFREESTREAM       4201

#define SSP_ERROR_SETPOSITION_FAILEDTOLOCKCHANNEL               5000
#define SSP_ERROR_SETPOSITION_FAILEDTOSTOPCHANNEL               5001
#define SSP_ERROR_SETPOSITION_FAILEDTOPLAYCHANNEL               5002
#define SSP_ERROR_SETPOSITION_FAILEDTOFLUSHBUFFER               5003
#define SSP_ERROR_SETPOSITION_FAILEDTOSETPOSITION               5004

#define SSP_ERROR_LOOP_INVALID                                  6000

#define SSP_ERROR_PLAYHEAD_FAILEDTOSETBUFFERSIZE                7000
#define SSP_ERROR_PLAYHEAD_FAILEDTOSETUPDATEPERIOD              7001
#define SSP_ERROR_PLAYHEAD_FAILEDTOSETVOLUME                    7002
#define SSP_ERROR_PLAYHEAD_FAILEDTOSETTIMESHIFTING              7003
#define SSP_ERROR_PLAYHEAD_FAILEDTOSETPITCHSHIFTING             7004

#define SSP_ERROR_ENCODER_FAILEDTOSTART                         8000
#define SSP_ERROR_ENCODER_FAILEDTOSTOP                          8001
#define SSP_ERROR_CAST_ENCODERNOTFOUND                          8100
#define SSP_ERROR_CAST_FAILEDTOINIT                             8101

// TODO: Consider merging FAILEDTOSTOPCHANNEL, FAILEDTOFREESTREAM, etc.

#endif
