public class Ball extends SurfaceView implements SurfaceHolder.Callback {
private BallThread ballThread = null;
private Bitmap bitmap;
private float x, y;
public Ball(Context context) {
super(context);
bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.ic_launcher);
x = 50;
y = 50;
getHolder().addCallback(this);
ballThread = new BallThread(getHolder(), this);
}
@Override
public void surfaceChanged(SurfaceHolder holder, int format, int width,
int height) {
}
@Override
public void surfaceCreated(SurfaceHolder holder) {
ballThread.setRunnable(true);
ballThread.start();
}
@Override
public void surfaceDestroyed(SurfaceHolder holder) {
boolean retry = true;
ballThread.setRunnable(false);
while(retry) {
try {
ballThread.join();
retry = false;
} catch(InterruptedException ie) {
}
break;
}
ballThread = null;
}
public void onDraw(Canvas canvas)
{
canvas.drawColor(Color.WHITE);
canvas.drawBitmap(bitmap, x,y,null);