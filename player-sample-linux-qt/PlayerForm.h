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

#ifndef _PLAYERFORM_H
#define	_PLAYERFORM_H

#include "ui_PlayerForm.h"

class PlayerForm : public QDialog {
    Q_OBJECT
public:
    PlayerForm();
    virtual ~PlayerForm();
    int CheckForError(int error);
private:
    Ui::PlayerForm widget;
};

#endif	/* _PLAYERFORM_H */
