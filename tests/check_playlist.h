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
#include "ssp_privatestructs.h"
#include "ssp_structs.h"

void check_playlist_setup(void) {
    //printf("[check_playlist_setup]\n");
    SSP_ERROR error = SSP_Init(NULL);
    if(error != SSP_OK) {
        printf("[check_playlist_setup] FAILED to call SSP_Init: %d", error);
    }
}

void check_playlist_teardown(void) {
    //printf("[check_playlist_teardown]\n");
    SSP_ERROR error = SSP_Free();
    if(error != SSP_OK) {
        printf("[check_playlist_setup] FAILED to call SSP_Free: %d", error);
    }
}

void printPlaylistItems() {
//    SSP_PLAYLISTITEM item;
//    for(int a = 0; a < SSP_Playlist_GetCount(); a++) {
//        SSP_Playlist_GetItemAt(a, &item);
//        printf("item %d = %s\n", a, item.filePath);
//    }
}

START_TEST(test_playlist_add) {
        SSP_ERROR error = SSP_Playlist_Clear();
        ck_assert_msg(error == SSP_OK, "Failed to clear playlist - error: %d", error);

        error = SSP_Playlist_AddItem("/test/file/path");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        int count = SSP_Playlist_GetCount();
        ck_assert_int_eq(count, 1);
    }
END_TEST

START_TEST(test_playlist_clear) {
        SSP_ERROR error = SSP_Playlist_Clear();
        ck_assert_msg(error == SSP_OK, "Failed to clear playlist - error: %d", error);

        error = SSP_Playlist_AddItem("item1");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        error = SSP_Playlist_AddItem("item2");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        error = SSP_Playlist_AddItem("item3");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        error = SSP_Playlist_Clear();
        ck_assert_msg(error == SSP_OK, "Failed to clear playlist - error: %d", error);

        int count = SSP_Playlist_GetCount();
        ck_assert_int_eq(count, 0);
    }
END_TEST

START_TEST(test_playlist_remove_first) {
        SSP_ERROR error = SSP_Playlist_Clear();
        ck_assert_msg(error == SSP_OK, "Failed to clear playlist - error: %d", error);

        error = SSP_Playlist_AddItem("item1");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        error = SSP_Playlist_AddItem("item2");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        error = SSP_Playlist_AddItem("item3");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        error = SSP_Playlist_RemoveItemAt(0);
        ck_assert_msg(error == SSP_OK, "Failed to remove playlist item - error: %d", error);

        printPlaylistItems();

        int count = SSP_Playlist_GetCount();
        ck_assert_int_eq(count, 2);

        SSP_PLAYLISTITEM item;
        SSP_Playlist_GetItemAt(0, &item);
        ck_assert_str_eq(item.filePath, "item2");

        SSP_Playlist_GetItemAt(1, &item);
        ck_assert_str_eq(item.filePath, "item3");
    }
END_TEST

START_TEST(test_playlist_remove_middle) {
        SSP_ERROR error = SSP_Playlist_Clear();
        ck_assert_msg(error == SSP_OK, "Failed to clear playlist - error: %d", error);

        error = SSP_Playlist_AddItem("item1");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        error = SSP_Playlist_AddItem("item2");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        error = SSP_Playlist_AddItem("item3");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        printPlaylistItems();

        error = SSP_Playlist_RemoveItemAt(1);
        ck_assert_msg(error == SSP_OK, "Failed to remove playlist item - error: %d", error);

        printPlaylistItems();

        int count = SSP_Playlist_GetCount();
        ck_assert_int_eq(count, 2);

        SSP_PLAYLISTITEM item;
        SSP_Playlist_GetItemAt(0, &item);
        ck_assert_str_eq(item.filePath, "item1");

        SSP_Playlist_GetItemAt(1, &item);
        ck_assert_str_eq(item.filePath, "item3");
    }
END_TEST

START_TEST(test_playlist_remove_last) {
        SSP_ERROR error = SSP_Playlist_Clear();
        ck_assert_msg(error == SSP_OK, "Failed to clear playlist - error: %d", error);

        error = SSP_Playlist_AddItem("item1");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        error = SSP_Playlist_AddItem("item2");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        error = SSP_Playlist_AddItem("item3");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        printPlaylistItems();

        error = SSP_Playlist_RemoveItemAt(2);
        ck_assert_msg(error == SSP_OK, "Failed to remove playlist item - error: %d", error);

        printPlaylistItems();

        int count = SSP_Playlist_GetCount();
        ck_assert_int_eq(count, 2);

        SSP_PLAYLISTITEM item;
        SSP_Playlist_GetItemAt(0, &item);
        ck_assert_str_eq(item.filePath, "item1");

        SSP_Playlist_GetItemAt(1, &item);
        ck_assert_str_eq(item.filePath, "item2");
    }
END_TEST

START_TEST(test_playlist_insert_first) {
        SSP_ERROR error = SSP_Playlist_Clear();
        ck_assert_msg(error == SSP_OK, "Failed to clear playlist - error: %d", error);

        error = SSP_Playlist_AddItem("item1");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        error = SSP_Playlist_AddItem("item2");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        error = SSP_Playlist_AddItem("item3");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        printPlaylistItems();

        error = SSP_Playlist_InsertItemAt("item4", 0);
        ck_assert_msg(error == SSP_OK, "Failed to remove playlist item - error: %d", error);

        printPlaylistItems();

        int count = SSP_Playlist_GetCount();
        ck_assert_int_eq(count, 4);

        SSP_PLAYLISTITEM item;
        SSP_Playlist_GetItemAt(0, &item);
        ck_assert_str_eq(item.filePath, "item4");

        SSP_Playlist_GetItemAt(1, &item);
        ck_assert_str_eq(item.filePath, "item1");
    }
END_TEST

START_TEST(test_playlist_insert_middle) {
        SSP_ERROR error = SSP_Playlist_Clear();
        ck_assert_msg(error == SSP_OK, "Failed to clear playlist - error: %d", error);

        error = SSP_Playlist_AddItem("item1");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        error = SSP_Playlist_AddItem("item2");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        error = SSP_Playlist_AddItem("item3");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        printPlaylistItems();

        error = SSP_Playlist_InsertItemAt("item4", 1);
        ck_assert_msg(error == SSP_OK, "Failed to remove playlist item - error: %d", error);

        printPlaylistItems();

        int count = SSP_Playlist_GetCount();
        ck_assert_int_eq(count, 4);

        SSP_PLAYLISTITEM item;
        SSP_Playlist_GetItemAt(0, &item);
        ck_assert_str_eq(item.filePath, "item1");

        SSP_Playlist_GetItemAt(1, &item);
        ck_assert_str_eq(item.filePath, "item4");
    }
END_TEST

START_TEST(test_playlist_insert_last) {
        SSP_ERROR error = SSP_Playlist_Clear();
        ck_assert_msg(error == SSP_OK, "Failed to clear playlist - error: %d", error);

        error = SSP_Playlist_AddItem("item1");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        error = SSP_Playlist_AddItem("item2");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        error = SSP_Playlist_AddItem("item3");
        ck_assert_msg(error == SSP_OK, "Failed to add playlist item - error: %d", error);

        printPlaylistItems();

        error = SSP_Playlist_InsertItemAt("item4", 2);
        ck_assert_msg(error == SSP_OK, "Failed to remove playlist item - error: %d", error);

        printPlaylistItems();

        int count = SSP_Playlist_GetCount();
        ck_assert_int_eq(count, 4);

        SSP_PLAYLISTITEM item;
        SSP_Playlist_GetItemAt(0, &item);
        ck_assert_str_eq(item.filePath, "item1");

        SSP_Playlist_GetItemAt(2, &item);
        ck_assert_str_eq(item.filePath, "item4");
    }
END_TEST

#endif /* defined(__player__check_playlist__) */
