package hotel;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import frame.loginframe.LoginFrame;
import sql.SqlStore;
import sql.SqlStore.Consumer;
import sql.SqlStore.Producer;
import sql.SqlStore.SqlQueue;

public class Main {
	
	public static SqlStore sqlstore = new SqlStore();
	public static SqlQueue sqlqueue = sqlstore.new SqlQueue();
	public static Producer producer = sqlstore.new Producer("生产者001", sqlqueue);
	Consumer consumer = sqlstore.new Consumer("消费者001", sqlqueue);
	
	public static Producer getProducer() {
		return producer;
	}

	public static SqlStore getSqlstore() {
		return sqlstore;
	}

	public static SqlQueue getSqlqueue() {
		return sqlqueue;
	}

	public static void main(String[] args) {
		new readywork.AddData();	
		ExecutorService service = Executors.newCachedThreadPool();
		Consumer consumer = sqlstore.new Consumer("消费者001", sqlqueue);
		service.submit(consumer);
		try {
			LoginFrame frame = new LoginFrame();
			frame.setVisible(true);
		}catch(Exception e) {
			e.printStackTrace();
		}
	}

}
