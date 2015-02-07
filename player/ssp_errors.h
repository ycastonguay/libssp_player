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

#define SSP_OK                  0
#define SSP_ERROR_UNKNOWN		1
#define SSP_ERROR_PLUGIN		2
#define SSP_ERROR_BASS_VERSION  3

#define SSP_ERROR_PLUGIN_APE_FAILEDTOLOAD       1000
#define SSP_ERROR_PLUGIN_FLAC_FAILEDTOLOAD      1001
#define SSP_ERROR_PLUGIN_MPC_FAILEDTOLOAD       1002
#define SSP_ERROR_PLUGIN_TTA_FAILEDTOLOAD       1003
#define SSP_ERROR_PLUGIN_WV_FAILEDTOLOAD        1004

#define SSP_ERROR_EQ_STAGE_ALREADYEXISTS		2000
#define SSP_ERROR_EQ_STAGE_DOESNOTEXIST     	2001

#define SSP_ERROR int

#endif
