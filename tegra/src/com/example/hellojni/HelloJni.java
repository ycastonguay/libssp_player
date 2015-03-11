/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
//package com.example.hellojni;
package org.sessionsapp.player.android;

import android.app.Activity;
import android.widget.TextView;
import android.os.Bundle;
import android.util.Log;
import org.sessionsapp.player.SSP;

public class HelloJni extends Activity
{
	private TextView tv;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        /* Create a TextView and set its content.
         * the text is retrieved by calling a native
         * function.
         */
		
        tv = new TextView(this);
        tv.setText("Starting...");
        setContentView(tv);

		//String hello = stringFromJNI();

		int version = SSP.SSP_GetVersion();

		String path = getApplicationInfo().nativeLibraryDir;
		Log.e("org.sessionsapp.player.android", String.format("---->>> nativeLibraryDir: %s", path));
		tv.setText("Initializing libssp_player...");
		int error = SSP.SSP_Init(path);
		if (error > 0) {
			return;
		}
		
		tv.setText("Initializing device...");
		error = SSP.SSP_InitDevice(-1, 44100, 1000, 100, true);
		if(error != SSP.SSP_OK) {
		    // TODO: show message?
		    return;		
		}

		tv.setText("Incredible but true, this sample app has survived Android");

		/*
		Thread updateThread = new Thread(new Runnable() {
			public void run() {
				while (true) {
					tv.post(new Runnable() {
						public void run() {
							//tv.setText( stringFromJNI() );
							tv.setText("hello there");
						}
					});
					try { Thread.sleep(1000); } catch (Exception e) { }
					tv.post(new Runnable() {
						public void run() {
							tv.setText("");
						}
					});
					try { Thread.sleep(1000); } catch (Exception e) { }
				}
			}
		});
		updateThread.start();
		*/
    }

    /* A native method that is implemented by the
     * 'libssp_player_tegra' native library, which is packaged
     * with this application.
     */
    //public native String  stringFromJNI();

    /* This is another native method declaration that is *not*
     * implemented by 'libssp_player_tegra'. This is simply to show that
     * you can declare as many native methods in your Java code
     * as you want, their implementation is searched in the
     * currently loaded native libraries only the first time
     * you call them.
     *
     * Trying to call this function will result in a
     * java.lang.UnsatisfiedLinkError exception !
     */
    //public native String  unimplementedStringFromJNI();

    /* this is used to load the 'libssp_player_tegra' library on application
     * startup. The library has already been unpacked into
     * /data/data/com.example.HelloJni/lib/liblibssp_player_tegra.so at
     * installation time by the package manager.
     */
    static {
        System.loadLibrary("libssp_player_tegra");
    }
}
