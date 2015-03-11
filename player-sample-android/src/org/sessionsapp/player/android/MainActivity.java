package org.sessionsapp.player.android;

import android.app.Activity;
import android.os.Bundle;
import org.sessionsapp.player.SSP;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main); 
		
		int version = SSP.SSP_GetVersion();
		
		String path = getApplicationInfo().nativeLibraryDir;
		int error = SSP.SSP_Init(path);
		if (error > 0) {
			return;
		}
		
		error = SSP.SSP_InitDevice(-1, 44100, 1000, 100, true);
		if(error != SSP.SSP_OK) {
		    // TODO: show message?
		    return;
		}
 	}
}
