public class MainActivity extends Activity {
private Ball ball;

@Override
protected void onCreate(Bundle savedInstanceState) {
super.onCreate(savedInstanceState);
requestWindowFeature(Window.FEATURE_NO_TITLE);

setContentView(new Ball(this));

}