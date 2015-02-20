/*
 * File:   PlayerForm.cpp
 * Author: ycastonguay
 *
 * Created on February 8, 2015, 6:51 PM
 */

#include "PlayerForm.h"
#include "../player/ssp_public.h"

PlayerForm::PlayerForm() {
    widget.setupUi(this);
    
    SSP_Init(NULL);
    
}

PlayerForm::~PlayerForm() {
}
