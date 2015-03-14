package org.sessionsapp.player;

public class SSP
{
    public static final int SSP_OK = 0;
    public static final int SSP_ERROR_UNKNOWN = 1;

    public static native int SSP_GetVersion();
    public static native int SSP_Init(String pathForPlugins);
    public static native int SSP_InitDevice(int device, int sampleRate, int bufferSize, int updatePeriod, boolean useFloatingPoint);
    public static native int SSP_FreeDevice();
    public static native int SSP_Free();
    
    public static native int SSP_GetState(); // TODO: is it possible to use the enum instead?

    public static native void SSP_GetDevice(SSP_DEVICE device);
    public static native void SSP_GetMixer(SSP_MIXER mixer);
    public static native int SSP_SetBufferSize(int bufferSize);
    public static native int SSP_SetUpdatePeriod(int updatePeriod);

    // EQ
    public static native void SSP_GetEQPreset(SSP_EQPRESET preset);
    public static native int SSP_SetEQPreset(SSP_EQPRESET preset);
    public static native int SSP_SetEQPresetBand(int band, float gain);
    public static native int SSP_ResetEQPreset(SSP_EQPRESET preset);

    public static native boolean SSP_GetEQEnabled();
    public static native int SSP_SetEQEnabled(boolean enabled);

    public static native int SSP_ResetEQ();
    public static native int SSP_NormalizeEQ();

    // Loops
    public static native int SSP_StartLoop(SSP_LOOP loop);
    public static native int SSP_UpdateLoop(SSP_LOOP loop);
    public static native int SSP_StopLoop();
    public static native void SSP_GetLoop(SSP_LOOP loop);

    // Playback
    public static native int SSP_Play();
    public static native int SSP_PlayWithOptions(int startIndex, long startPosition, boolean startPaused);
    public static native int SSP_Pause();
    public static native int SSP_Stop();
    public static native int SSP_Previous();
    public static native int SSP_Next();
    public static native int SSP_GoTo(int index);
    
    // Playhead
    public static native boolean SSP_GetIsShuffle();
    public static native int SSP_SetIsShuffle(boolean shuffle);

    public static native int SSP_GetRepeatType();  // TODO: is it possible to use the enum instead?
    public static native int SSP_SetRepeatType(int repeat);  // TODO: is it possible to use the enum instead?
    public static native int SSP_ToggleRepeatType();

    public static native float SSP_GetVolume();
    public static native int SSP_SetVolume(float volume);

    public static native float SSP_GetTimeShifting();
    public static native int SSP_SetTimeShifting(float timeShifting);

    public static native int SSP_GetPitchShifting();
    public static native int SSP_SetPitchShifting(int pitchShifting);

    public static native boolean SSP_GetIsSettingPosition();
    public static native boolean SSP_GetIsPlayingLoop();

    // Position
    public static native int SSP_GetPosition(SSP_POSITION position);
    public static native int SSP_SetPosition(long position);       
    public static native int SSP_SetPositionPercentage(float position);      
    public static native int SSP_GetPositionFromBytes(long bytes, SSP_POSITION position);
    public static native int SSP_GetPositionFromPercentage(float percentage, SSP_POSITION position);

    // Data
    public static native long SSP_GetBytesFromSecondsForCurrentChannel(float seconds);
    public static native int SSP_GetMixerData(float[] buffer, int length);
    public static native int SSP_GetMixerData(int[] buffer, int length);
    public static native long SSP_GetDataAvailable();

    // Encoder
    public static native int SSP_StartEncode(int encoder); // TODO: is it possible to use the enum instead?
    public static native int SSP_StopEncode();
    public static native int SSP_StartCast(SSP_CAST_SERVER server);
    public static native int SSP_StopCast();

    // Device detection
    public static native int SSP_GetOutputDeviceCount();
    public static native boolean SSP_GetOutputDevice(int index, SSP_DEVICE device);

    // Playlist
    public static native int SSP_Playlist_AddItem(String filePath);
    public static native int SSP_Playlist_InsertItemAt(String filePath, int index);
    public static native int SSP_Playlist_RemoveItemAt(int index);
    public static native int SSP_Playlist_Clear();
    public static native int SSP_Playlist_GetItemAt(int index, SSP_PLAYLISTITEM item);
    public static native int SSP_Playlist_GetItemFromId(int id, SSP_PLAYLISTITEM item);
    public static native int SSP_Playlist_GetIndexFromId(int id);
    public static native int SSP_Playlist_GetCount();
    public static native int SSP_Playlist_GetCurrentIndex();

    // Decoder
    public static native int SSP_Decoder_CreateStream(String filePath, boolean useFloatingPoint);
    public static native int SSP_Decoder_FreeStream(int handle);
    public static native int SSP_Decoder_GetLength(int handle);
    public static native int SSP_Decoder_GetData(int handle, float[] buffer, int length);
    public static native int SSP_Decoder_GetData(int handle, int[] buffer, int length);

    // Callbacks
    public static native void SSP_SetPlaylistIndexChangedCallback(PlaylistIndexChangedDelegate callback, String user);
    public static native void SSP_RemovePlaylistIndexChangedCallback();

    public static native void SSP_SetPlaylistEndedCallback(PlaylistEndedDelegate callback, String user);
    public static native void SSP_RemovePlaylistEndedCallback();

    public static native void SSP_SetStateChangedCallback(StateChangedDelegate callback, String user);
    public static native void SSP_RemoveStateChangedCallback();

    public static native void SSP_SetLogCallback(LogDelegate callback, String user);
    public static native void SSP_RemoveLogCallback();

    public static native void SSP_SetLoopPlaybackStartedCallback(LoopPlaybackStartedDelegate callback, String user);
    public static native void SSP_RemoveLoopPlaybackStartedCallback();

    public static native void SSP_SetLoopPlaybackStoppedCallback(LoopPlaybackStoppedDelegate callback, String user);
    public static native void SSP_RemoveLoopPlaybackStoppedCallback();

    public static native void SSP_SetAudioInterruptedCallback(AudioInterruptedDelegate callback, String user);
    public static native void SSP_RemoveAudioInterruptedCallback();

    public static native void SSP_SetBPMDetectedCallback(BPMDetectedDelegate callback, String user);
    public static native void SSP_RemoveBPMDetectedCallback();
    
    public enum SSPPlayerState
    {
        UNINITIALIZED,
        INITIALIZED,
        STOPPED,
        PLAYING,
        PAUSED
    };

    public enum SSPRepeatType
    {
        OFF,
        PLAYLIST,
        SONG
    };

    public enum SSPEncoderType
    {
        OGG,
        AAC,
        MP3
    };
    
	public interface PlaylistIndexChangedDelegate
	{
		void PlaylistIndexChangedDelegate(Object user);
	}

	public interface PlaylistEndedDelegate
	{
		void PlaylistEndedDelegate(Object user);
	}

	public interface StateChangedDelegate
	{
		void StateChangedDelegate(Object user, int state);  // TODO: is it possible to use the enum instead?
	}

	public interface LogDelegate
	{
		void LogDelegate(Object user, String str);
	}

	public interface LoopPlaybackStartedDelegate
	{
		void LoopPlaybackStartedDelegate(Object user);
	}

	public interface LoopPlaybackStoppedDelegate
	{
		void LoopPlaybackStoppedDelegate(Object user);
	}

	public interface AudioInterruptedDelegate
	{
		void AudioInterruptedDelegate(Object user, boolean ended);
	}

	public interface BPMDetectedDelegate
	{
		void BPMDetectedDelegate(Object user, float bpm);
	}

    public static class SSP_CAST_SERVER extends SSPBaseClass
    {
        public String name;
        public String url;
        public String password;
        public int bitrate;
    }

    public static class SSP_MIXER extends SSPBaseClass
    {
        public int sampleRate;
        public int bufferSize;
        public int updatePeriod;
        public boolean useFloatingPoint;
    }

    public static class SSP_EQPRESETBAND extends SSPBaseClass
    {
        public float center;
//        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 128)]
        public String label;
        public float bandwidth;
        public float gain;
        public float q;
    }

    public static class SSP_EQPRESET extends SSPBaseClass
    {
//        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 38)]
        public String id;
//        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 128)]
        public String name;
//        [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 18)]
        public SSP_EQPRESETBAND[] bands;
    }

    public static class SSP_LOOP extends SSPBaseClass
    {
        public long startPositionBytes;
        public long endPositionBytes;
    }

    public static class SSP_POSITION extends SSPBaseClass
    {
//        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 32)]
        public String str;
        public long bytes;
        public long ms;
        public long samples;
    }

    public static class SSP_DEVICE extends SSPBaseClass
    {
        public String name;
        public String driver;
        public int deviceId;
        public boolean isInitialized;
        public boolean isDefault;
    }

    public static class SSP_PLAYLISTITEM extends SSPBaseClass
    {
        public boolean isLoaded;
        public String filePath;
        public int id;
        public int sampleRate;
        public int numberOfChannels;
        public int bitsPerSample;
        public int channel;
        public long length;
    }
    
    public static class SSPBaseClass
    {
    	private long pointer;
    	
    	protected SSPBaseClass(long ptr) {
    		pointer = ptr;
    	}
    	
    	protected SSPBaseClass() {
    		pointer = 0;
    	}
    	
    	protected static long GetPointer(Object obj) {
    		if (obj == null)
    			return 0;
    		
    		SSPBaseClass cls = (SSPBaseClass)obj;
    	    return cls.pointer;
    	}
    }
	
    static {
    	System.loadLibrary("bass");
    	System.loadLibrary("bass_fx");
    	System.loadLibrary("bassmix");
    	System.loadLibrary("bassenc");
        System.loadLibrary("ssp_player");
    }
}