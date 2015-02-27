package ch02;

public class Rectangle implements FigureGeometry
{

	protected float width;
	protected float length;
	protected int scale;
	
	public Rectangle(float width, float length){
		this.width = width;
		this.length = length;
	}
	
	@Override
	public float perimeter() {
		return 2 * (width + length);
	}

	@Override
	public float area() {
		// TODO Auto-generated method stub
		return width * length;
	}

	@Override
	public void setScale(int scale) {
		this.scale = scale;
		
	}

	@Override
	public float weight() {
		// TODO Auto-generated method stub
		return this.area() * scale;
	}

}
