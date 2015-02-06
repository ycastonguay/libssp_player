//
//  main.c
//  player-test
//
//  Created by Yanick Castonguay on 2015-01-21.
//  Copyright (c) 2015 Yanick Castonguay. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "../tests/check_playlist.h"

START_TEST(test_example) {
    ck_assert_int_eq(0, 0);
    ck_assert_int_eq(1, 1);
}
END_TEST

Suite* player_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Player");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_example);
    //tcase_add_test(tc_core, test_example_two);
    tcase_add_test(tc_core, test_example_three);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(int argc, const char * argv[]) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = player_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
