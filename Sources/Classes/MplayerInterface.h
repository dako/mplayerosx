/*
 *  MplayerInterface.h
 *  MPlayer OS X
 *
 *	version 1.1
 *
 *	Description:
 *		Interface to MPlayer binary application that is supposed to simplify the access
 *	to the application controlls and state values while handling inconsistent states of
 *	player
 *
 *  Created by Jan Volf
 *	<javol@seznam.cz>
 
 *  Copyright (c) 2003 Jan Volf. All rights reserved.
 */


#import <Cocoa/Cocoa.h>
#import "MovieInfo.h"

// Notifications posted by MplayerInterface
	// 	@"MIPlayerTerminatedNotification"	mplayer has been terminated
	// 	@"MIInfoReadyNotification"			notification has been updated
	// 	@"MIStateUpdatedNotification"		status updated

// status update notification info keys
	//	@"PlayerStatus"				NSNumber - int (player status constants)
	//	@"MovieSeconds"				NSNumber - float
	//	@"SyncDifference"			NSNumber - float
	//	@"DroppedFrames"			NSNumber - int
	//	@"PostProcessingLevel"		NSNumber - int
	//	@"CPUUsage"					NSNumber - float percents
	//	@"CacheUsage"				NSNumber - float percents

// keys to mplayer info dictionary (all represents NSString objects)
	//	@"ID_FILENAME"				file path
	//	@"ID_FILE_FORMAT"			media format (AVI,MOV....)
	//	@"ID_VIDEO_FORMAT"			video codec
	//	@"ID_VIDEO_BITRATE"
	//	@"ID_VIDEO_WIDTH"
	//	@"ID_VIDEO_HEIGHT"
	//	@"ID_VIDEO_FPS"
	//	@"ID_VIDEO_ASPECT"
	//	@"ID_AUDIO_CODEC"
	//	@"ID_AUDIO_FORMAT"
	//	@"ID_AUDIO_BITRATE"			Bits per second
	//	@"ID_AUDIO_RATE"			kHz
	//	@"ID_AUDIO_NCH"				number of channels
	//	@"ID_LENGTH"				length in seconds

// player status constants
#define kFinished					-1	// terminated by reaching end-of-file
#define kStopped					0	// terminated by not reaching EOF
#define kPlaying					1
#define kPaused						2
#define kOpening					3
#define kBuffering					4
#define kIndexing					5

// seeking modes
#define	MIRelativeSeekingMode		0	// relative seeking in seconds 
#define	MIPercentSeekingMode		1	// absolute seeking in percents
#define	MIAbsoluteSeekingMode		2	// absolute seeking in seconds

// default constants
#define kDefaultMovieSize 			NSMakeSize(0,0)

@interface MplayerInterface : NSObject
{
// Properties
	// file paths
	NSString *myPathToPlayer;
	NSString *myMovieFile;
	NSString *mySubtitlesFile;
	NSString *myAudioFile;
	NSString *myAudioExportFile;
	NSString *myFontFile;
	
	// playback
	NSString *audioLanguages;
	NSString *subtitleLanguages;
	
	BOOL correctPTS;
	
	unsigned int cacheSize;
	
	// display
	unsigned int displayType;
	
	BOOL flipVertical;
	BOOL flipHorizontal;
	NSSize movieSize;
	double aspectRatio;
	double monitorAspect;
	
	unsigned int deviceId;
	unsigned int voModule;
	unsigned int screenshotPath;
	
	// video
	BOOL enableVideo;
	NSString *videoCodecs;
	
	unsigned int framedrop;
	BOOL fastLibavcodec;
	
	BOOL deinterlace;
	unsigned int postprocessing;
	
	BOOL assSubtitles;
	BOOL embeddedFonts;
	NSString *subEncoding;
	unsigned int subScale;
	BOOL assPreFilter;
	
	// audio
	BOOL enableAudio;
	NSString *audioCodecs;
	
	BOOL hrtfFilter;
	BOOL karaokeFilter;
	
	// advanced
	BOOL equalizerEnabled;
	NSArray *equalizerValues;
	BOOL videoEqualizerEnabled;
	NSArray *videoEqualizerValues;
	NSArray *addParams;
	
	// properties
	BOOL myRebuildIndex;
	
	// state variables
	int	myState;				// player state
	unsigned int myVolume;		// volume 0-100
	
	//beta
	unsigned int myadvolume;
	float mySeconds;			// actual/saved seconds
	
	// statistics
	BOOL myUpdateStatistics;		// if set the following properties are periodicaly updated
	float mySyncDifference;		// difference in secconds between audion and video
	int myCPUUsage;			// overal player CPU usage
	int myCacheUsage;			// cache usage
	int	myDroppedFrames;		// number of dropped frames since last key frame
	int myPostProcLevel;		// actual level of postprocessing
	
	// internal use
	NSTask *myMplayerTask;
	double myLastUpdate;			// date when last update notificationa was sent
	BOOL settingsChanged;			// changed settings that requires player restart
	BOOL takeEffectImediately;		// changes have to take effect even in paused mode
	BOOL restartingPlayer;			// set when player is teminated to be restarted
	BOOL pausedOnRestart;			// set when paused during attemp to restart player
	BOOL isRunning;					// set off after recieving termination notification
	BOOL useIdentifyForPlayback;	// sets whether -identify is sent on starting playback
	BOOL windowedVO;
	int myOutputReadMode;				// defines playback output form 
	NSMutableArray *myCommandsBuffer;	// store cmds that cannot be send immediatelly
	NSString *lastUnparsedLine;
	//NSMutableDictionary *myInfo;	// dict filled by -identify command
	BOOL isFullscreen;				// currently playing fullscreen
	
	MovieInfo *info;
}
// interface
// init and uninit
- (id) init;										// init
- (id) initWithPathToPlayer:(NSString *)aPath;		// init with movie file path

// playback controls (take effect imediately)
- (void) play;										// play item from saved time
- (void) stop;										// stops playback
- (void) pause;										// pause / unpause playback
- (void) seek:(float)seconds mode:(int)aMode;		// seek in movie
- (void) performCommand:(NSString *)aCommand;

// settings (take effect by using applySettingsWithRestart: message)
// setting files
- (void) setMovieFile:(NSString *)aFile;
- (void) setSubtitlesFile:(NSString *)aFile;
- (void) setAudioFile:(NSString *)aFile;
//beta
- (void) setAudioExportFile:(NSString *)aFile;
- (void) setFontFile:(NSString *)aFile;

// playback
- (void) setAduioLanguages:(NSString *)langString;
- (void) setSubtitleLanguages:(NSString *)langString;
- (void) setCorrectPTS:(BOOL)aBool;
- (void) setCacheSize:(unsigned int)kilobytes;

// display
- (void) setDisplayType:(unsigned int)mode;
- (void) setFlipVertical:(BOOL)aBool;
- (void) setFlipHorizontal:(BOOL)aBool;
- (void) setMovieSize:(NSSize)aSize;				// set height to 0 to keep aspect ratio)
- (NSSize) movieSize;
- (void) setAspectRatio:(double)ratio;
- (void) setMonitorAspectRatio:(double)ratio;
- (void) setDeviceId:(unsigned int)dId;
- (void) setVideoOutModule:(int)module;
- (void) setScreenshotPath:(int)mode;

// video
- (void) setVideoEnabled:(BOOL)aBool;
- (void) setVideoCodecs:(NSString *)codecString;
- (void) setFramedrop:(unsigned int)mode;
- (void) setFastLibavcodec:(BOOL)aBool;
- (void) setDeinterlace:(unsigned int)mode;
- (void) setPostprocessing:(unsigned int)mode;
- (void) setAssSubtitles:(BOOL)aBool;
- (void) setEmbeddedFonts:(BOOL)aBool;
// subtitles settings (don't work during playback)
- (void) setSubtitlesEncoding:(NSString *)aEncoding;// sets subtitles file encoding
- (void) setSubtitlesScale:(unsigned int)aScale;	// sets subtitle scale in % (see man mplayer)
- (void) setAssPreFilter:(BOOL)aBool;

// audio
- (void) setAudioEnabled:(BOOL)aBool;
- (void) setAudioCodecs:(NSString *)codecString;
- (void) setHRTFFilter:(BOOL)aBool;
- (void) setKaraokeFilter:(BOOL)aBool;

// advanced
- (void) setEqualizerEnabled:(BOOL)aBool;
- (void) setEqualizer:(NSArray *)freqs;
- (void) setVideoEqualizerEnabled:(BOOL)aBool;
- (void) setVideoEqualizer:(NSArray *)values;
- (void) setAdditionalParams:(NSArray *)params;


//- (void) setVIDEO_TS:(BOOL)aBool;					// dvd folder

- (void) setRebuildIndex:(BOOL)aBool;				// take effect after restarting playback
- (void) setFullscreen:(BOOL)aBool;
- (BOOL) fullscreen;

// misc settings (don't work during playback)
- (void) setVolume:(unsigned int)percents;			// set audio volume

// other methods
- (void) applySettingsWithRestart:(BOOL)restartIt;	// applyes settings that require restart
- (void) waitUntilExit;
- (void) takeScreenshot;

// info
- (void) loadInfoBeforePlayback:(BOOL)aBool;		// enables using of -identify param for playback
- (MovieInfo *) loadInfo;						// gets info returned by -identify (don't work during playback)
- (MovieInfo *) info;							// returns the content of info dictionary 
- (int) status;
- (float) seconds;									// returns number of seconds, elapsed
- (BOOL) changesNeedsRestart;						// retuns YES if changes needs restart
- (BOOL) isRunning;
- (BOOL) isWindowed;

// statistics
- (void) setUpdateStatistics:(BOOL)aBool;			// sets whether to update stats
- (float) syncDifference;
- (int) cpuUsage;
- (int) cacheUsage;
- (int) droppedFrames;
- (int) postProcLevel;

// advenced
- (void)sendCommand:(NSString *)aCommand;
- (void)sendCommands:(NSArray *)aCommands;
- (void)runMplayerWithParams:(NSArray *)aParams;
- (void)sendToMplayersInput:(NSString *)aCommand;
- (void)terminateMplayer;

// notification handlers
- (void) mplayerTerminated;
- (void) readOutputC:(NSNotification *)notification;

// helper
-(NSString *)parseDefine:(NSString *)searchFor inLine:(NSString *)line;
-(NSArray *)splitString:(NSString *)string byCharactersInSet:(NSCharacterSet *)set;

@end
