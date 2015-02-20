/* 
 * File:   PlayerForm.h
 * Author: ycastonguay
 *
 * Created on February 8, 2015, 6:51 PM
 */

#ifndef _PLAYERFORM_H
#define	_PLAYERFORM_H

#include "ui_PlayerForm.h"

class PlayerForm : public QDialog {
    Q_OBJECT
public:
    PlayerForm();
    virtual ~PlayerForm();
private:
    Ui::PlayerForm widget;
};

#endif	/* _PLAYERFORM_H */
