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

#ifndef __player__check_playlist__
#define __player__check_playlist__

#include <stdio.h>
#include <check.h>
#include "ssp_public.h"

START_TEST(test_example_three) {
        ck_assert_int_eq(0, 0);
        ck_assert_int_eq(2, 2);

        SSP_ERROR error = SSP_Init();
        printf("hello error: %d\n", error);
        ck_assert_msg(error == SSP_OK, "Failed at SSP_Init; error code %d", error);
    }
END_TEST

#endif /* defined(__player__check_playlist__) */
