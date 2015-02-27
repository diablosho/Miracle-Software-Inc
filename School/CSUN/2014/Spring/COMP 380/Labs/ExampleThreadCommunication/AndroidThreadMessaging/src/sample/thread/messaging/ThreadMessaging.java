package sample.thread.messaging;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

/**
 * @author davidkuo
 *
 */
public class ThreadMessaging extends Activity {
	
	private static final String TAG = "ThreadMessaging";
	private TextView mTextView;
	private Handler mMainHandler, mChildHandler;
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        mTextView = (TextView)findViewById(R.id.text);
        
        /*
		 * Create the main handler on the main thread so it is bound to the main
		 * thread's message queue. 
		 */
        mMainHandler = new Handler() {
        	
        	public void handleMessage(Message msg) {
        		
        		Log.i(TAG, "Got an incoming message from the child thread - "  + (String)msg.obj);
        		
        		/*
        		 * Handle the message coming from the child thread.
        		 */
        		mTextView.setText(mTextView.getText() + (String)msg.obj + "\n");
        	}
        };
        
        /*
         * Start the child thread.
         */
        new ChildThread().start();
        
        Log.i(TAG, "Main handler is bound to - " + mMainHandler.getLooper().getThread().getName());
 
        Button button = (Button)findViewById(R.id.button);
        button.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				
				/*
				 * We cannot guarantee that the mChildHandler is created 
				 * in the child thread by the time the user clicks the button.
				 */
				if (mChildHandler != null) {
					
					/* 
					 * Send a message to the child thread.
					 */
					Message msg = mChildHandler.obtainMessage();
					msg.obj = mMainHandler.getLooper().getThread().getName() + " says Hello";
					mChildHandler.sendMessage(msg);
					Log.i(TAG, "Send a message to the child thread - " + (String)msg.obj);
				}
			}
        });
    }
    
    @Override
	protected void onDestroy() {
    	
    	Log.i(TAG, "Stop looping the child thread's message queue");
    	
    	/*
    	 * Remember to stop the looper
    	 */
    	mChildHandler.getLooper().quit();
    	
		super.onDestroy();
	}

	class ChildThread extends Thread {
    	
		private static final String INNER_TAG = "ChildThread";
		
    	public void run() {
    		
    		this.setName("child");
    		
    		/*
			 * You have to prepare the looper before creating the handler.
			 */
			Looper.prepare();
			
			/*
			 * Create the child handler on the child thread so it is bound to the
			 * child thread's message queue.
			 */
			mChildHandler = new Handler() {
    			
    			public void handleMessage(Message msg) {
    			
    				Log.i(INNER_TAG, "Got an incoming message from the main thread - " + (String)msg.obj);
    				
    				/*
					 * Do some expensive operation there. For example, you need
					 * to constantly send some data to the server.
					 */
    				try {
    					
    					/*
						 * Mocking an expensive operation. It takes 100 ms to
						 * complete.
						 */
						sleep(100);
						
						/*
						 * Send the processing result back to the main thread.
						 */
						Message toMain = mMainHandler.obtainMessage();
						toMain.obj = "This is " + this.getLooper().getThread().getName() + 
							".  Did you send me \"" + (String)msg.obj + "\"?";
						mMainHandler.sendMessage(toMain);
						Log.i(INNER_TAG, "Send a message to the main thread - " + (String)toMain.obj);
						
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
    			}
    		};
    		
    		Log.i(INNER_TAG, "Child handler is bound to - " + mChildHandler.getLooper().getThread().getName());
    		
    		/*
    		 * Start looping the message queue of this thread.
    		 */
    		Looper.loop();
    	}
    }
}