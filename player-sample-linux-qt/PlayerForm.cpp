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

#include "PlayerForm.h"
#include "../player/ssp_public.h"

PlayerForm::PlayerForm() {
    widget.setupUi(this);
    
    int version = SSP_GetVersion();
    printf("libssp_player version %d\n", version);
    widget.lblVersion->setText(QString("Version %1").arg(version));
    
    int error = CheckForError(SSP_Init(NULL));
    if(error != SSP_OK) {
        return;
    }
    
    error = CheckForError(SSP_InitDevice(-1, 44100, 1000, 100, true));
    if(error != SSP_OK) {
        return;
    }
    
}

PlayerForm::~PlayerForm() {
}

int PlayerForm::CheckForError(int error) {
    if(error != SSP_OK) {
        printf("libssp_player error %d\n", error);
    }
    
    return error;
}
