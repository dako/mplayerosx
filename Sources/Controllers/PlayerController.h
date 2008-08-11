/*
 *  PlayerCtrllr.h
 *  MPlayer OS X
 *
 *	Description:
 *		Controller for player controls, status box and statistics panel on side of UI
 *	and for MplayerInterface on side of data
 *
 *  Created by Jan Volf
 *	<javol@seznam.cz>
 *  Copyright (c) 2003 Jan Volf. All rights reserved.
 */

#import <Cocoa/Cocoa.h>

#import "MplayerInterface.h"
#import "VideoOpenGLView.h"

@interface PlayerController : NSObject
{
	// other controllers outlets
    IBOutlet id	playListController;
	IBOutlet id appController;
	IBOutlet id preferencesController;
	IBOutlet id settingsController;
	
	//Player Window
	IBOutlet id playerWindow;
	IBOutlet NSButton *playButton;
	IBOutlet NSButton *playButtonToolbar;
    IBOutlet id volumeSlider;
	IBOutlet id volumeSliderToolbar;
	IBOutlet id volumeIconImage;
	IBOutlet id volumeIconImageToolbar;
	IBOutlet id scrubbingBar;
	IBOutlet id scrubbingBarToolbar;
	IBOutlet id timeTextField;
	IBOutlet id timeTextFieldToolbar;
	IBOutlet id playListButton;
	IBOutlet VideoOpenGLView *videoOpenGLView;

	// statistics panel outlets
	IBOutlet id statsPanel;
    IBOutlet id statsAVsyncBox;
    IBOutlet id statsCacheUsageBox;
    IBOutlet id statsCPUUsageBox;
    IBOutlet id statsPostProcBox;
    IBOutlet id statsDroppedBox;
    IBOutlet id statsStatusBox;
	
	// stream menus
	IBOutlet id videoStreamMenu;
	IBOutlet id audioStreamMenu;
	IBOutlet id subtitleStreamMenu;
	
	// properties
	MplayerInterface *myPlayer;
	MplayerInterface *myPreflightPlayer;
	
	// actual movie parametters
	NSMutableDictionary *myPlayingItem;
	BOOL saveTime;
	int playerStatus;
	unsigned movieSeconds;		// stores actual movie seconds for further use
	BOOL  fullscreenStatus;
	BOOL isOntop;
	
	// images
	NSImage *playImageOff;
	NSImage *playImageOn;
	NSImage *pauseImageOff;
	NSImage *pauseImageOn;
	
	NSRect org_frame;
}

// interface
- (IBAction)displayWindow:(id)sender;
- (void) preflightItem:(NSMutableDictionary *)anItem;
- (void) playItem:(NSMutableDictionary *)anItem;
- (NSMutableDictionary *) playingItem;
- (BOOL) isRunning;
- (BOOL) isPlaying;
- (void) setOntop:(BOOL)aBool;
- (void) applyPrefs;
- (void) applySettings;
- (BOOL) changesRequireRestart;
- (void) applyChangesWithRestart:(BOOL)restart;

// misc
- (void) setMovieSize;
- (void) setSubtitlesEncoding;
- (void) setVideoEqualizer;
- (NSNumber *) gammaValue:(NSNumber *)input;
- (MplayerInterface *)playerInterface;
- (MplayerInterface *)preflightInterface;

// player control actions
- (IBAction)changeVolume:(id)sender;
- (IBAction)playPause:(id)sender;
- (IBAction)seekBack:(id)sender;
- (IBAction)seekFwd:(id)sender;
- (IBAction)seekBegin:(id)sender;
- (IBAction)seekEnd:(id)sender;
- (IBAction)stop:(id)sender;
- (IBAction)switchFullscreen:(id)sender;
- (IBAction)displayStats:(id)sender;
- (IBAction)takeScreenshot:(id)sender;
- (void)sendKeyEvent:(int)event;

- (void)clearStreamMenus;
- (void)fillStreamMenus;
- (void)videoMenuAction:(id)sender;
- (void)audioMenuAction:(id)sender;
- (void)subtitleMenuAction:(id)sender;
- (void)newVideoStreamId:(unsigned int)streamId;
- (void)newAudioStreamId:(unsigned int)streamId;
- (void)newSubtitleStreamId:(unsigned int)streamId forType:(SubtitleType)type;
- (void)disableMenuItemsInMenu:(NSMenu *)menu;

// notification observers
- (void) appFinishedLaunching;
- (void) appShouldTerminate;
- (void) appTerminating;
- (void) playbackStarted;
- (void) statsClosed;
- (void) statusUpdate:(NSNotification *)notification;
- (void) progresBarClicked:(NSNotification *)notification;

// window delegate methods
- (BOOL)windowShouldZoom:(NSWindow *)sender toFrame:(NSRect)newFrame;
- (BOOL)windowShouldClose:(id)sender;

@end
