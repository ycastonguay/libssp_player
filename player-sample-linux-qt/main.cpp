/*
 * File:   main.cpp
 * Author: ycastonguay
 *
 * Created on February 8, 2015, 3:29 PM
 */

#include <QApplication>
#include "PlayerForm.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    PlayerForm form;
    form.show();

    return app.exec();
}
