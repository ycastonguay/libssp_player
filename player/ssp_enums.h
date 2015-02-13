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

#ifndef __player__ssp_enums__
#define __player__ssp_enums__

typedef enum {SSP_PLAYER_STATE_UNINITIALIZED, SSP_PLAYER_STATE_INITIALIZED, SSP_PLAYER_STATE_STOPPED, SSP_PLAYER_STATE_PLAYING, SSP_PLAYER_STATE_PAUSED} ssp_player_state_t;
typedef enum {SSP_PLAYER_REPEAT_OFF, SSP_PLAYER_REPEAT_PLAYLIST, SSP_PLAYER_REPEAT_SONG} ssp_player_repeat_t;
typedef enum {SSP_PLAYER_ENCODER_OGG, SSP_PLAYER_ENCODER_AAC, SSP_PLAYER_ENCODER_MP3} ssp_player_encoder_t;

#endif /* defined(__player__ssp_enums__) */
