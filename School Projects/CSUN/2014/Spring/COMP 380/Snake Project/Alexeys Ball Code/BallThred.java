public class BallThread extends Thread{
private SurfaceHolder sh;
private Ball ball;
private Canvas canvas;
private boolean run=false;
public BallThread(SurfaceHolder s_holder,Ball ball)
{
this.sh=s_holder;
this.ball=ball;
}
public void setRunnable(boolean run)
{
this.run=run;
}
public void run()
{
super.run();
while (run) {
canvas = null;
try {
canvas = sh.lockCanvas(null);
synchronized (sh) {
ball.onDraw(canvas);
Thread.sleep(300);
}
} catch(Exception e)
{
}
finally {
if (canvas != null) {
sh.unlockCanvasAndPost(canvas);
}
}
}
}
}