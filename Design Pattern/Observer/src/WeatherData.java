import java.util.ArrayList;

public class WeatherData implements Subject{
	private ArrayList observers;
	private float temp;
	private float humidity;
	private float pressure;

	public WeatherData() {
		observers = new ArrayList();
	}
	
	@Override
	public void registerObserver(Observer o) {
		// TODO Auto-generated method stub
		observers.add(o);
	}

	@Override
	public void removeObserver(Observer o) {
		// TODO Auto-generated method stub
		int i = observers.indexOf(o);
		if (i >= 0) {
			observers.remove(i);
		}
	}

	@Override
	public void notifyObserver() {
		// TODO Auto-generated method stub
		for (int i = 0; i < observers.size(); ++i) {
			Observer o = (Observer) observers.get(i);
			o.update(temp, humidity, pressure);
		}
	}
	
	public void measurementsChanged() {
		notifyObserver();
	}

	public void setMeasurements(float temp, float humidity, float pressure) {
		this.temp = temp;
		this.humidity = humidity;
		this.pressure -= pressure;
		measurementsChanged();
	}
}
