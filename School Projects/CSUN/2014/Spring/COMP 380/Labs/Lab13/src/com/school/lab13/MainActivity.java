package com.school.lab13;

import android.net.Uri;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.MediaController;
import android.widget.VideoView;

public class MainActivity extends Activity
{
	VideoView		ctrlVideoView;
	MediaController	ctrlMedia;
		
	@Override protected void onCreate(	Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		String			pathVideo	=	"android.resource://" + getPackageName() + "/" + R.raw.piano;
		Uri				video		=	Uri.parse(pathVideo);
		
		ctrlVideoView = (VideoView) findViewById(R.id.ctrlVideo);
		ctrlMedia = new MediaController(this);
		
		ctrlMedia.setAnchorView(ctrlVideoView);
		
		ctrlVideoView.setMediaController(ctrlMedia);
		ctrlVideoView.setVideoURI(video);
		ctrlVideoView.start();
	}
	
	@Override public boolean onCreateOptionsMenu(	Menu menu)
	{
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}	
}