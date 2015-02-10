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

#include <stdlib.h>
#include <check.h>
#include "../tests/check_playlist.h"

Suite* player_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Player");
    tc_core = tcase_create("Core");

    tcase_add_checked_fixture(tc_core, check_playlist_setup, check_playlist_teardown);
    tcase_add_test(tc_core, test_playlist_add);
    tcase_add_test(tc_core, test_playlist_remove);
    tcase_add_test(tc_core, test_playlist_remove_partial);
    tcase_add_test(tc_core, test_playlist_insert);
    tcase_add_test(tc_core, test_playlist_insert2);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(int argc, const char * argv[]) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = player_suite();
    sr = srunner_create(s);

    // Keep this line to allow debugging test cases
    srunner_set_fork_status(sr, CK_NOFORK);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
