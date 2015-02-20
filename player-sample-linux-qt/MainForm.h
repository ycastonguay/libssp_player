/* 
 * File:   MainForm.h
 * Author: ycastonguay
 *
 * Created on February 8, 2015, 3:30 PM
 */

#ifndef _MAINFORM_H
#define	_MAINFORM_H

#include "ui_MainForm.h"

class MainForm : public QMainWindow {
    Q_OBJECT
public:
    MainForm();
    virtual ~MainForm();
private:
    Ui::MainForm widget;
};

#endif	/* _MAINFORM_H */
