
public abstract class Duck {
	FlyBehavior flyBehavior;
	QuackBehavior quackBehavior;
	
	public Duck(){
		
	}
	public void performQuack() {
		quackBehavior.quack();
	}
	public void performFly() {
		flyBehavior.fly();
	}
	
	public void swim() {
		System.out.println("All ducks fleat.");
	}
	
	public void setFlyBehavior( FlyBehavior fb ) {
		flyBehavior = fb;
	}
	
	public void setQuackBehavior( QuackBehavior qb ) {
		quackBehavior = qb;
	}
	
	public abstract void display();
}
